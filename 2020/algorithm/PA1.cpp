#include <iostream>
#define MODE 0

using namespace std;
class inv{
private:
        int* array;
        int size;
        int cnt=0;

public:
        inv(void);
        ~inv();
        void reset(int* a, int s);
        void printArray(void);
        int numOfInv(void);
        void msort(int *list, int l, int r);
        void merge(int *list, int l, int q, int r);
};

inv::inv(){
        this->array = NULL;
        this->size = 0;
}
inv::~inv(){
        if(this->array) delete this->array;
        return;
}
void inv::reset(int *a, int s){
        int i=0;
        if(this->array) delete this->array;

        this->array = new int[s];
        this->size = s;
        for(i=0;i<s;i++)        *(this->array+i) = *(a+i);
        return;
}
void inv::printArray(void){
        int i = 0;
        for(i=0;i<size;i++)     cout<<*(this->array+i)<<" ";
        cout<<endl;
}
int inv::numOfInv(void){
     
        this->cnt=0;
        msort(this-> array, 0, size);
        return cnt;
}
void inv::msort(int *list, int start, int end){
        int mid=(start+end)/2;
		if(start<mid){
                msort(list, start, mid);
                msort(list, mid,end);
                merge(list, start, mid, end);
        }
}
void inv::merge(int *list, int start, int mid, int end){
        int n1=mid-start;
        int n2=end-mid;
        int L[n1],R[n2];
        int i=0, j=0;
        for(i=0;i<n1;i++)       L[i]=list[start+i];
        for(j=0;j<n2;j++)       R[j]=list[mid+j];
        i=0;
        j=0;
        while(i<n1&&j<n2){
                if(L[i]<=R[j]){
                        list[start+i+j]=L[i];
                        i++;
                }
                else{
                        list[start+i+j]=R[j];
                        j++;
                        this->cnt+=mid-(start+i);
                    
                }
        }
        while (i < n1) { 
			list[start+i+j]=L[i];
            i++; 
		} 
		while (j < n2) { 
			list[start+i+j]=R[j];
            j++; 
		}


}
using namespace std;
int main(void){
        inv *inversion = new inv();
        int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        inversion->reset(arr, 10);
        cout<<"Number of Inversions: "<<inversion->numOfInv()<<endl;
        delete inversion;
        return 0;
}


