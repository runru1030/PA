#include <iostream>
#include <cstring>
using namespace std;

class pri{
public:
        int pr;
        char *word;

        pri();
        pri(int p, char* w);
        ~pri();

        void operator= (pri &pair);
        void setPair(int p, char* w);
        void printPair(void);
};

pri::pri(){
        this->pr = 0x7FFFFFFF;
        this->word = 0;
        return;
}

pri::pri(int p, char *w){
        this->word = 0;
        this->setPair(p, w);
        return;
}

pri::~pri(){
        if(this->word)  delete[] this->word;
        return;
}

void pri::operator= (pri& pair){
        this->pr = pair.pr;
        if(pair.word){
                this->word = new char[strlen(pair.word)+1];
                strcpy(this->word, pair.word);
        }
        else    this->word = 0;
        return;
}

void pri::setPair(int p, char* w){
        if(this->word)  delete[] this->word;
        this->pr = p;
        if(w){
                this->word = new char[strlen(w)+1];
                strcpy(this->word, w);
        }
        else{
                this->word = 0;
        }
}

void pri::printPair(void){
        cout<<"["<<this->pr<<", "<<this->word<<"]\n";
        return;
}
class concat{
private:
        int num;
        pri **pa;


public:
        concat(void);
        concat(int* priority, char **words, int n);
        ~concat(void);

        char* concatenate(void);

};

concat::concat(void){
        this->num = 0;
        this->pa = 0;
        return;
}

concat::concat(int* priority, char **words, int n){
        int i=0;
        this->num = n;
        this->pa = new pri* [n];
        for(i=0;i<n;i++)        this->pa[i] = new pri(priority[i], words[i]);
        return;
}

concat::~concat(void){
        if(this->pa){
                int i=0, n = this->num;
                for(i=0;i<n;i++)        if(this->pa[i])         delete this->pa[                                                                             i];
                delete[] this->pa;
        }
        return;
}

char* concat::concatenate(void){
        char **w=new char*[num];
        int k=-1, size=0, j=-1;

        for(int i=0;i<num;i++)  if(pa[i][0].pr>k)k=pa[i][0].pr;

        char h[2]="-";
        int c[k+1]={0};

        for(int i=0;i<num;i++)  c[pa[i][0].pr]++;

        for(int i=1;i<=k;i++)   c[i]+=c[i-1];

        for(int i=num-1;i>=0;i--){
                if(i<num/2)     w[--c[pa[i][0].pr]]=h;

                else    w[--c[pa[i][0].pr]]=pa[i][0].word;

                size+=(strlen(w[c[pa[i][0].pr]])+1);
        };

        char *result = new char[size];
        for(int i=0;i<num;i++){
                int h=0;
                while(w[i][h])result[++j]=w[i][h++];

                if(i+1<num)result[++j]=' ';
                else result[++j]='\0';
        }
        delete[] w;


        return result;
        delete result;
}


const char *testSet[] = {"Hello", "World", "interesting", "algorithm", "Sookmyung", "Women\'s", "University", "a", "a", "I", "am", "boy", "are", "you", "girl"};
int priority[15] = {11, 10, 9, 0, 0, 4, 1, 8, 2, 1, 1, 8, 6, 4, 2};

int main(void){
        int  i=0;
        char **word = new char*[15];
        char *result = 0;

        for(i=0;i<15;i++){
                word[i] = new char[strlen(testSet[i])+1];
                strcpy(word[i], testSet[i]);
        }

        concat *con = new concat(priority, word, 15);
        cout<<(result = con->concatenate())<<endl;

        for(i=0;i<15;i++)       delete[] *(word+i);
        delete[] word;
        delete con;
        delete[] result;
        return 0;
}


