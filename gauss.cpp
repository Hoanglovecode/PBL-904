#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
#include <cctype>//them de dung tolower()
using namespace std;
const int MAXN=10;
const double EPS=1e-9;
bool isValidNumber(const string &s){
    if(s.empty()) return false;
    stringstream ss(s);
    double x;
    char extra;
    if(!(ss>>x)) return false;
    if(ss>>extra) return false;
    if(isnan(x)||isinf(x)) return false;
    return true;
}
bool splitLine(const string &line,vector<string> &tokens){
    tokens.clear();
    stringstream ss(line);
    string temp;
    while(ss>>temp){
        tokens.push_back(temp);
    }
    return !tokens.empty();
}
bool readMatrix(ifstream &inp,ofstream &out,double a[][MAXN+1],int n){
    if(n<=0||n>MAXN){
        cout<<"Loi: So phuong trinh phai nam trong khoang 1 -> "<<MAXN<<endl;
        out<<"Loi: So phuong trinh phai nam trong khoang 1 -> "<<MAXN<<endl;
        return false;
    }
    string line;
    vector<string> tokens;
    for(int i=0;i<n;i++){
        if(!getline(inp,line)){
            cout<<"Loi: Thieu dong du lieu tai dong "<<i+1<<endl;
            out<<"Loi: Thieu dong du lieu tai dong "<<i+1<<endl;
            return false;
        }
        while(line.empty()){
            if(!getline(inp,line)){
                return false;
            }
        }
        splitLine(line,tokens);
        if(tokens.size()!=n+1){
            cout<<"Loi: Dong "<<i+1<<" phai co "<<n+1<<" gia tri"<<endl;
            out<<"Loi: Dong "<<i+1<<" phai co "<<n+1<<" gia tri"<<endl;
            for(int skip=i+1;skip<n;skip++){
                getline(inp,line);
            }
            return false;
        }
        for(int j=0;j<=n;j++){
            if(!isValidNumber(tokens[j])){
                cout<<"Loi: '"<<tokens[j]<<"' khong phai so hop le tai dong "<<i+1<<", cot "<<j+1<<endl;
                out<<"Loi: '"<<tokens[j]<<"' khong phai so hop le tai dong "<<i+1<<", cot "<<j+1<<endl;
                for(int skip=i+1;skip<n;skip++){
                    getline(inp,line);
                }
                return false;
            }
            a[i][j]=stod(tokens[j]);
        }
    }
    return true;
}
void doidong(double a[][MAXN+1],int n,int r1,int r2){
    for(int j=0;j<=n;j++){
        swap(a[r1][j],a[r2][j]);
    }
}
void inmatran(double a[][MAXN+1],int n){
    cout<<"\nMa tran hien tai:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++){
            cout<<setw(12)<<fixed<<setprecision(3)<<a[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
void gauss(double a[][MAXN+1],int n){
    for(int i=0;i<n-1;i++){
        int pivot=i;
        for(int k=i+1;k<n;k++){
            if(fabs(a[k][i])>fabs(a[pivot][i])){
                pivot=k;
            }
        }
        if(fabs(a[pivot][i])<EPS) continue;
        if(pivot!=i){
            doidong(a,n,i,pivot);
            cout<<"Da doi dong "<<i+1<<" voi dong "<<pivot+1<<endl;
        }
        for(int j=i+1;j<n;j++){
            double factor=a[j][i]/a[i][i];
            for(int k=i;k<=n;k++){
                a[j][k]-=factor*a[i][k];
            }
        }
        inmatran(a,n);
    }
}
int check(double a[][MAXN+1],int n){
    int rankA=0;
    int rankAug=0;
    for(int i=0;i<n;i++){
        bool all0A=true;
        for(int j=0;j<n;j++){
            if(fabs(a[i][j])>EPS){
                all0A=false;
                break;
            }
        }
        if(!all0A) rankA++;
        bool all0Aug=true;
        for(int j=0;j<=n;j++){
            if(fabs(a[i][j])>EPS){
                all0Aug=false;
                break;
            }
        }
        if(!all0Aug) rankAug++;
    }
    if(rankA<rankAug) return -1;
    if(rankA<n) return 0;
    return 1;
}
void thenguoc(double a[][MAXN+1],double x[],int n){
    for(int i=n-1;i>=0;i--){
        if(fabs(a[i][i])<EPS){
            x[i]=0;
            continue;
        }
        double sum=a[i][n];
        for(int j=i+1;j<n;j++){
            sum-=a[i][j]*x[j];
        }
        x[i]=sum/a[i][i];
    }
}
void xuat(ofstream &out,double x[],int n){
    out<<fixed<<setprecision(6);
    for(int i=0;i<n;i++){
        out<<"x"<<i+1<<" = "<<x[i]<<endl;
    }
    out<<endl;
}
void giaiHe(double a[][MAXN+1],int n,ofstream &out){
    double x[MAXN];
    inmatran(a,n);
    gauss(a,n);
    int result=check(a,n);
    if(result==-1){
        cout<<"He vo nghiem\n";
        out<<"He vo nghiem\n";
    }
    else if(result==0){
        cout<<"He vo so nghiem\n";
        out<<"He vo so nghiem\n";
    }
    else{
        thenguoc(a,x,n);
        cout<<"He co nghiem duy nhat\n";
        out<<"Nghiem cua he:\n";
        //
        for(int i=0;i<n;i++){
            cout<<"x"<<i+1<<" = "<<fixed<<setprecision(6)<<x[i]<<endl;
        }
        //
        xuat(out,x,n);
    }
}

void giaiTuBanPhim(){
    ofstream out("GAUSS.OUT");
    int n;
    double a[MAXN][MAXN+1];
    cout<<"Nhap n = ";
    cin>>n;
    cout<<"Nhap ma tran mo rong:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++){
            cin>>a[i][j];
        }
    }
    giaiHe(a,n,out);
    out.close();
}

void giaiTuFile(){
    ifstream inp("GAUSS.INP");
    ofstream out("GAUSS.OUT");
    if(!inp){
        cout<<"Khong mo duoc file input!\n";
        return;
    }
    string line;
    int test=1;
    while(getline(inp,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        int n;
        ss>>n;
        cout<<"\n========== TEST "<<test<<" ==========\n";
        double a[MAXN][MAXN+1];
        bool ok=readMatrix(inp,out,a,n);
        if(ok){
            giaiHe(a,n,out);
        }
        test++;
    }
    inp.close();
    out.close();
}

int main() {
    char choice;
    do {
        cout << "====================================="<<endl;
        cout << "    CHUONG TRINH GIAI HE GAUSS\n";
        cout << "=====================================\n";
        cout << "Ban muon nhap du lieu tu dau?\n";
        cout << "  a. Nhap thu cong tu ban phim\n";
        cout << "  b. Doc tu file (GAUSS.INP)\n";
        cout << "  q. Thoat\n";
        cout << "=====================================\n";
        cout << "Lua chon cua ban (a/b/q): ";
        cin >> choice;
        choice = tolower(choice); // chap nhan ca chu hoa A/B/Q
 
        switch (choice) {
            case 'a':
                giaiTuBanPhim();
                break;
            case 'b':
                giaiTuFile();
                break;
            case 'q':
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long nhap a, b hoac q.\n";
        }
 
        if (choice != 'q') {
            system("pause");
        }
    } while (choice != 'q');
 
    return 0;
}
/*

2
1 1 2
2 2 5



4
1 2 3 4 10
2 3 4 5 14
3 4 5 6 18
4 5 6 7 22

3
0 2 3 7
1 -1 2 4
3 1 -1 2

3
1.5 2.2 -3.1 4.8
2.7 -1.4 5.5 3.2
-4.1 2.8 1.9 -6.7

3
1 0 0 5
0 1 0 -3
0 0 1 2

3
0 0 0 0
0 0 0 0
0 0 0 0

3
1 2 3 4
2 4 6 8
1 1 1 5

3
1 . 3 4
0 0 0 0
0 0 0 0

3
1 2 a 4
0 0 0 5
0 0 0 0

3
1 2 3 4
5 # 7 8
9 10 11 12

3
1 ++ 3 4
0 0 0 0
0 0 0 0

3
1 2 5..2 4
0 0 0 0
0 0 0 0

-3

100

3
1 2
4 5 6
7 8 9 10

2
1e309 2 3
4 5 6

3
1 2 3 4
5 6 7 8
9 10 11 12

*/