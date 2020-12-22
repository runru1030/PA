#include <iostream>

using namespace std;

class maxSum{
private:
        int num;
        int* money;
        int* m;

public:
        maxSum(int n, int *m);
        ~maxSum();
        int max(void);
        int partMaxSum(int a);
};

maxSum::maxSum(int n, int* m){
        int i=0;
        if(!m)  return;

        num = n;
        money = new int[n];

        for(i=0;i<n;i++){
                money[i] = m[i];
        }
        return;
}

maxSum::~maxSum(){
        if(money){
                delete[] money;
        }
        return;
}

int maxSum::max(void){
        int r=0;
        int a[num]={0};
        m=a;
        m[0]=money[0];
        m[1]=m[0]+money[1];

        r=partMaxSum(num-1);
        return r;

}
int maxSum::partMaxSum(int a){
        int M0, M1, M2;

        if(a<2)return m[a];
        else{
                partMaxSum(a-1);
                M0=m[a-1];
                M1=m[a-2]+money[a];
                if(a==2)M2=money[a-1]+money[a];
                else M2=m[a-3]+money[a-1]+money[a];

        }
        int M=M0;
        if(M<=M1)M=M1;
        if(M<=M2)M=M2;
        m[a]=M;
        return M;

}

int main(void){
        int i=0;
        int money[7] = {23, 10, 5, 3, 11, 32, 9};
        maxSum* ms = new maxSum(7, money);

        cout<<"Maximum = "<<ms->max()<<endl;

        if(ms)  delete ms;
        return 0;
}

