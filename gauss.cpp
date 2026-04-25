#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
const double eps=1e-6;
void nhap(ifstream &inp,double a[][100],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++)inp>>a[i][j];
    }
}
void doidong(double a[][100],int n,int r1,int r2){
    for(int j=0;j<=n;j++){
        double t=a[r1][j];
        a[r1][j]=a[r2][j];
        a[r2][j]=t;
    }
}
void gauss(double a[][100],int n){
    for(int i=0;i<n-1;i++){
        if(fabs(a[i][i])<eps){
            for(int k=i+1;k<n;k++){
                if(fabs(a[k][i])>eps){
                    doidong(a,n,i,k);
                    break;
                }
            }
        }
        if(fabs(a[i][i])<eps)continue;
        for(int j=i+1;j<n;j++){
            double m=-a[j][i]/a[i][i];
            for(int k=i;k<=n;k++){
                a[j][k]=a[j][k]+m*a[i][k];
            }
        }
    }
}
int check(double a[][100],int n){
    bool vonghiem=false,vosonghiem=false;
    for(int i=0;i<n;i++){
        bool all0=true;
        for(int j=0;j<n;j++){
            if(fabs(a[i][j])>eps) all0=false;
        }
        if(all0==true){
            if(fabs(a[i][n])>eps) vonghiem=true;
            else vosonghiem=true;
        }
    }
    if(vonghiem)return -1;
    if(vosonghiem)return 0;
    return 1;
}
void thenguoc(double a[][100],double x[],int n){
    for(int i=n-1;i>=0;i--){
        if(fabs(a[i][i])<eps){
            x[i]=0;
            continue;
        }
        double s=a[i][n];
        for(int j=i+1;j<n;j++)s=s-a[i][j]*x[j];
        x[i]=s/a[i][i];
    }
}
void xuat(ofstream &out,double x[],int n){
    for(int i=0;i<n;i++){
        out<<"x"<<i+1<<"= "<<fixed<<setprecision(3)<<x[i]<<endl;
    }
    out<<endl;
}
int main(){
    ifstream inp("GAUSS.INP");
    ofstream out("GAUSS.OUT");
    if(!inp || !out){
        cout<<"Lỗi mở file"<<endl;
        return 0;
    }
    double a[10][100],x[10];
    int n;
    while(inp>>n){
        nhap(inp,a,n);
        gauss(a,n);
        int t=check(a,n);
        if(t==-1){
            out<<"Hệ vô nghiệm\n"<<endl;
            continue;
        }
        if(t==0){
            out<<"Hệ có vô số nghiệm\n"<<endl;
            continue;
        }
        thenguoc(a,x,n);
        xuat(out,x,n);
    }
}
/*
3
2 1 -1 8
-3 -1 2 -11
-2 1 2 -3

2
1 1 2
2 2 5

3
1 1 1 3
2 -1 1 0
3 1 -1 2

4
1 2 3 4 10
2 3 4 5 14
3 4 5 6 18
4 5 6 7 22

3
1 2 3 4
0 0 0 0
0 0 0 0

3
1 2 3 4
0 0 0 5
0 0 0 0
*/