#include <iostream>
using namespace std;

class grid{
private:
        int n;
        unsigned long long result;
		int **m;
		int cnt=0;

public:
        grid(int n){
                this->n = n;
                this->result = 0;
        }
        unsigned long long numOfWays(void);
		void search(int a, int b);
};


unsigned long long grid::numOfWays(void){
        result = 0;
        m=new int *[n+1];
        for(int i=0;i<=n;i++)   m[i]=new int [n+1]{};
        search(0,0);
        result=cnt;

        for(int i=0;i<=n;i++)   delete[] m[i];
        delete[] m;

        return result;
}
void grid::search(int a, int b){
        m[a][b]=1;
        int x[4]={0, 0, 1, -1};
        int y[4]={1, -1, 0, 0};
        if(a==n&&b==n){
                cnt++;
                return;
        }
        for(int i=0;i<4;i++){

                if(a+x[i]>=0&&a+x[i]<=n&&b+y[i]>=0&&b+y[i]<=n&&!m[a+x[i]][b+y[i]]){

                        search(a+x[i],b+y[i]);
                        m[a+x[i]][b+y[i]]=0;

                }
        }
}

int main(int argc, char* argv[]){

        grid* G = NULL;
        if(argc == 1){
                cout<<"Error..\nUsage: ./run [number]"<<endl;
                return 0;
        }
        G = new grid(atoi(argv[1]));
        cout<<G->numOfWays()<<" patterns"<<endl;
        delete G;
        return 0;
}


