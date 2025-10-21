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
void msint(int arr[],int len,int tmp[],int dep){
    if(len<=1){
        return;
    }
    int mid=len/2;
    if(dep<3){
        #pragma omp task shared(arr,tmp) firstprivate(mid,dep)
        {
            //printf("递归分配线程：%d\n", omp_get_thread_num());
            msint(arr, mid, tmp, dep + 1);
        }
        #pragma omp task shared(arr,tmp) firstprivate(mid,len,dep)
        {
            //printf("递归分配线程：%d\n", omp_get_thread_num());
            msint(arr + mid, len - mid, tmp + mid, dep + 1);
        }
        #pragma omp taskwait
        int i=0,j=mid;
        mergeint(arr,mid,arr+mid,len-mid,tmp);
        //#pragma omp parallel for schedule(static) num_threads(16)
        for(int i=0;i<len;i++){
            //printf("循环分配线程：%d\n",omp_get_thread_num());
            arr[i]=tmp[i];
        }
    }
    else{
        msint(arr,mid,tmp,dep+1);
        msint(arr+mid,len-mid,tmp+mid,dep+1);
        int i=0,j=mid;
        mergeint(arr,mid,arr+mid,len-mid,tmp);
        //#pragma omp parallel for schedule(static) num_threads(16)
        for(int i=0;i<len;i++){
            arr[i]=tmp[i];
        }
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
void msfloat(double arr[],int len,double tmp[],int dep){
    if(len<=1){
        return;
    }
    int mid=len/2;
    if(dep<3){
        #pragma omp task shared(arr,tmp) firstprivate(mid,dep)
        {
            //printf("递归分配线程：%d\n", omp_get_thread_num());
            msfloat(arr,mid,tmp,dep+1);
        }
        #pragma omp task shared(arr,tmp) firstprivate(mid,len,dep)
        {
            //printf("递归分配线程：%d\n", omp_get_thread_num());
            msfloat(arr+mid,len-mid,tmp+mid,dep+1);
        }
        #pragma omp taskwait
        int i=0,j=mid;
        mergefloat(arr,mid,arr+mid,len-mid,tmp);
        //#pragma omp parallel for schedule(static) num_threads(16)
        for(int i=0;i<len;i++){
            //printf("循环分配线程：%d\n",omp_get_thread_num());
            arr[i]=tmp[i];
        }
    }
    else{
        msfloat(arr,mid,tmp,dep+1);
        msfloat(arr+mid,len-mid,tmp+mid,dep+1);
        int i=0,j=mid;
        mergefloat(arr,mid,arr+mid,len-mid,tmp);
        //#pragma omp parallel for schedule(static) num_threads(16)
        for(int i=0;i<len;i++){
            arr[i]=tmp[i];
        }
    }
}
// 性能监控函数
void print_omp_info() {
    #ifdef _OPENMP
    printf("OpenMP 已启用\n");
    printf("最大线程数: %d\n", omp_get_max_threads());
    printf("处理器数量: %d\n", omp_get_num_procs());
    #else
    printf("OpenMP 未启用\n");
    #endif
}
void parallel_msint(int arr[],int len,int tmp[]) {
    #pragma omp parallel
    {
        #pragma omp single
        msint(arr,len,tmp,0);
    }
}
void parallel_msfloat(double arr[],int len,double tmp[]) {
    #pragma omp parallel
    {
        #pragma omp single
        msfloat(arr,len,tmp,0);
    }
}
int main(){
    const int N=1e6+10;
    int flag,n;
    freopen("testdata.txt","r",stdin);
    freopen("result(mspl).txt","w",stdout);
    scanf("%d%d",&flag,&n);
    printf("%d %d\n",flag,n);
    omp_set_num_threads(16);
    //print_omp_info();
    if(!flag){
        int a[N];
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int tmp[N];
        parallel_msint(a+1,n,tmp);
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
        parallel_msfloat(b+1,n,tmp);
        for(int i=1;i<=n;i++){
            printf("%lf\n",b[i]);
        }
    }
}