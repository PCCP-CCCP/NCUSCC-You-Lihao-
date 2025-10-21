#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<random>
#include<iterator>
#include<algorithm>
#include<map>
using namespace std;
const int N=1e6+10;
int n,nlim_l,nlim_r,a[N],flag;//0 is int, 1 is float;
int l,r;//data value limit
double b[N];
int main(){
    mt19937 rng(time(nullptr));
    random_device rd;
    map<int, int> hist;
    freopen("datarequirement.txt","r",stdin);
    freopen("testdata.txt","w",stdout);
    scanf("%d%d%d%d%d",&flag,&nlim_l,&nlim_r,&l,&r);
    uniform_int_distribution<int> dist(nlim_l,nlim_r);
    n=dist(rd);
    printf("%d\n%d\n",flag,n);
    if(!flag){//produce int
        for(int i=1;i<=n;i++){
            //shuffle(a+1,a+i,rng);
            a[i]=l+int(1.0*rng()/RAND_MAX*(r-l)+0.5);
            printf("%d\n",a[i]);
        }
    }
    else{//produce float
        for(int i=1;i<=n;i++){
            //shuffle(b+1,b+i,rng);
            b[i]=l+((double)rng()/RAND_MAX)*(r-l);
            printf("%.3lf\n",b[i]);
        }
    }
}