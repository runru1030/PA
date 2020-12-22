
#include <cmath>
#include<iostream>
using namespace std;

class point{
public:
        double x;
        double y;
        point();
        point(const point &p);
};

class closest{
private:
        point* pnt;
        int num;
        double min;
     
public:
        closest();
        ~closest();

        void setPoints(point* p, int n);
        double getMinDist(void);
        void getmin(point* p, int s, int e);
        void Q_sort(int s, int e);
        int partition(point* p, int s, int e);
};

closest::closest(void){
        this->pnt = NULL;
        this->num = 0;
        return;
}

closest::~closest(void){
        if(this->pnt)   delete this->pnt;
        return;
}

void closest::setPoints(point* p, int n){
        int i=0;
        if(this->pnt)   delete this->pnt;
        this->pnt = new point[n];
        this->num = n;
        for(i=0;i<n;i++)        this->pnt[i] = p[i];
        return;
}

double closest::getMinDist(void){
        this->min=1.79769e+308;
        this->Q_sort(0, this->num-1);
        this->getmin(this->pnt, 0, this->num-1);
        return this->min;

}
void closest::getmin(point* p, int s, int e){

        int mid=(e+s)/2;
        if(e-s>2){
                getmin(p, s, mid);
                getmin(p, mid+1, e);
                int h=mid;
                while(p[h].x>p[mid+1].x-this->min&&h>=s){
                        int k=mid+1;
                        while (p[k].x - p[h].x < this->min&&k<=e) {

                                double m1 = sqrt(pow(p[k].x - p[h].x, 2) + pow(p[k].y - p[h].y, 2));
                                if (this->min > m1)this->min = m1;
                                k++;

                        }
                        h--;
                }
        }
        else{
               if(e-s==2){

                        double d1=sqrt(pow(p[e].x-p[e-1].x,2)+pow(p[e].y-p[e-1].y,2));
                        if(this->min>d1)this->min=d1;

                        double d2=sqrt(pow(p[e-1].x-p[s].x,2)+pow(p[e-1].y-p[s].y,2));
                        if(this->min>d2)this->min=d2;

                }
                double d3=sqrt(pow(p[e].x-p[s].x,2)+pow(p[e].y-p[s].y,2));
                if(this->min>d3)this->min=d3;

        }





}
void closest::Q_sort(int s, int e){
        if(s<e){
                int q=partition(this->pnt, s, e);
                Q_sort(s, q-1);
                Q_sort(q+1, e);
        }

}

int closest::partition(point* p, int s, int e){
        double X=p[e].x;
        int i=s-1;
        for(int j=s;j<e;j++){
                if(p[j].x<=X){
                        i++;
                        double temp_x=p[i].x;
                        double temp_y=p[i].y;
                        p[i].x=p[j].x;
                        p[i].y=p[j].y;
                        p[j].x=temp_x;
                        p[j].y=temp_y;
                }
        }
        double temp_x=p[i+1].x;
        double temp_y=p[i+1].y;
        p[i+1].x=p[e].x;
        p[i+1].y=p[e].y;
        p[e].x=temp_x;
        p[e].y=temp_y;

        return i+1;
}



int main(void){
        int i=0;
        int x[10] = {4, 10, 5, -2, -1, 6, 3, 6, -9, 5};
        int y[10] = {9, 3, 10, 5, -9, -3, 10, -10, 4, 2};
        closest *clo = new closest();
        point *p = new point[10];
        for(i=0;i<10;i++){
                (p+i)->x = x[i];
                (p+i)->y = y[i];
        }
        clo->setPoints(p, 10);
        cout<<"Minimum distance: "<<clo->getMinDist()<<endl;
        delete clo, p;
        return 0;
}

point::point(void){
        this->x = this->y = 0.0;
        return;
}

point::point(const point& p){
        this->x = p.x;
        this->y = p.y;
}


