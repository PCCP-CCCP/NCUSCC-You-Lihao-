#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
const int N=1e6+10;
void mergeint(int a[],int alen,int b[],int blen,int tmp[]){
    int i=0,j=0,k=0;
    while (i<alen&&j<blen){
        if(b[j]<a[i]){
            tmp[k]=b[j];
            ++j;
        }
        else{
            tmp[k]=a[i];
            ++i;
        }
        ++k;
    }
    for(int x=i;x<alen;++x,++k){
        tmp[k]=a[x];
    }
    for(int x=j;x<blen;++x,++k){
        tmp[k]=b[x];
    }
}
void msint(int arr[],int len,int tmp[]){
    if(len<=1){
        return;
    }
    int mid=len/2;
    msint(arr,mid,tmp);
    msint(arr+mid,len-mid,tmp+mid);
    int i=0,j=mid;
    mergeint(arr,mid,arr+mid,len-mid,tmp);
    for(int i=0;i<len;i++){
        arr[i]=tmp[i];
    }
}
void mergefloat(double a[],int alen,double b[],int blen,double tmp[]){
    int i=0,j=0,k=0;
    while (i<alen&&j<blen){
        if(b[j]<a[i]){
            tmp[k]=b[j];
            ++j;
        }
        else{
            tmp[k]=a[i];
            ++i;
        }
        ++k;
    }
    for(int x=i;x<alen;++x,++k){
        tmp[k]=a[x];
    }
    for(int x=j;x<blen;++x,++k){
        tmp[k]=b[x];
    }
}
void msfloat(double arr[],int len,double tmp[]){
    if(len<=1){
        return;
    }
    int mid=len/2;
    msfloat(arr,mid,tmp);
    msfloat(arr+mid,len-mid,tmp+mid);
    int i=0,j=mid;
    mergefloat(arr,mid,arr+mid,len-mid,tmp);
    for(int i=0;i<len;i++){
        arr[i]=tmp[i];
    }
}
int main(){
    int flag,n;
    freopen("testdata.txt","r",stdin);
    freopen("result(msnp).txt","w",stdout);
    scanf("%d%d",&flag,&n);
    printf("%d %d\n",flag,n);
    if(!flag){
        int a[N];
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int tmp[N];
        msint(a+1,n,tmp);
        for(int i=1;i<=n;i++){
            printf("%d\n",a[i]);
        }
    }
    else{
        double b[N];
        for(int i=1;i<=n;i++){
            scanf("%lf",&b[i]);
        }
        double tmp[N];
        msfloat(b+1,n,tmp);
        for(int i=1;i<=n;i++){
            printf("%lf\n",b[i]);
        }
    }
}