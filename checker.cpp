#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<random>
#include<iterator>
#include<algorithm>
using namespace std;
const int N=1e6+10;
int n,a[N],flag;//0 is int, 1 is float;
double b[N];
bool yet=true;
int main(){
    freopen("result(mspl).txt","r",stdin);
    freopen("checkres.txt","w",stdout);
    scanf("%d%d",&flag,&n);
    if(!flag){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]<a[i-1]){
                yet=false;
            }
        }
    }
    else{
        for(int i=1;i<=n;i++){
            scanf("%lf",&b[i]);
            if(b[i]<b[i-1]){
                yet=false;
            }
        }
    }
    if(yet){
        printf("yes\n");
    }
    else{
        printf("no\n");
    }
}