#include<stdio.h>
#include<stdlib.h>
int maxi(int pa,int pb){
    if(pa>pb){
        return pa;
    }
    return pb;
}
double maxf(double pa,double pb){
    if(pa>pb){
        return pa;
    }
    return pb;
}
int mini(int pa,int pb){
    if(pa>pb){
        return pb;
    }
    return pa;
}
double minf(double pa,double pb){
    if(pa>pb){
        return pb;
    }
    return pa;
}
int sint(int* arr,int l,int r){
    int i=l,j=r,tmp=maxi(mini(arr[l],arr[(l+r)/2]),mini(maxi(arr[l],arr[(l+r)/2]),arr[r]));
    while (i!=j){
        while(tmp<=arr[j]&&i<j){
            j--;
        }
        while(tmp>=arr[i]&&i<j){
            i++;
        }
        if(i<j){
           int t=arr[i];
           arr[i]=arr[j];
           arr[j]=t;
        }
    }
    arr[l]=arr[i];
    arr[i]=tmp;
    return i;
}
void qsint(int* arr,int l,int r) {
    int *stack=(int *)malloc(sizeof(int)*r);
    for(int i=0;i<r;i++){
        stack[i]=-1;
    }
    int cnt=0;
    if(l<r){
        stack[cnt++]=l;
        stack[cnt++]=r;
    }
    while(cnt){
        int r_pop=stack[cnt-1],l_pop=stack[cnt-2];
        stack[cnt-1]=stack[cnt-2]=-1;
        cnt-=2;
        int i=sint(arr,l_pop,r_pop);
        if(l_pop<i-1){
            stack[cnt++]=l_pop;
            stack[cnt++]=i-1;
        }
        if(r_pop>i+1){
            stack[cnt++]=i+1;
            stack[cnt++]=r_pop;
        }
    }
    free(stack);
    stack=NULL;
}
int sfloat(double* arr,int l,int r){
    int i=l,j=r;
    double tmp=maxi(mini(arr[l],arr[(l+r)/2]),mini(maxi(arr[l],arr[(l+r)/2]),arr[r]));
    while (i!=j){
        while(tmp<=arr[j]&&i<j){
            j--;
        }
        while(tmp>=arr[i]&&i<j){
            i++;
        }
        if(i<j){
           int t=arr[i];
           arr[i]=arr[j];
           arr[j]=t;
        }
    }
    arr[l]=arr[i];
    arr[i]=tmp;
    return i;
}
void qsfloat(double* arr,int l,int r) {
    int *stack=(int *)malloc(sizeof(int)*r);
    for(int i=0;i<r;i++){
        stack[i]=-1;
    }
    int cnt=0;
    if(l<r){
        stack[cnt++]=l;
        stack[cnt++]=r;
    }
    while(cnt){
        int r_pop=stack[cnt-1],l_pop=stack[cnt-2];
        stack[cnt-1]=stack[cnt-2]=-1;
        cnt-=2;
        int i=sfloat(arr,l_pop,r_pop);
        if(l_pop<i-1){
            stack[cnt++]=l_pop;
            stack[cnt++]=i-1;
        }
        if(r_pop>i+1){
            stack[cnt++]=i+1;
            stack[cnt++]=r_pop;
        }
    }
    free(stack);
    stack=NULL;
}
int main() {
    const int N=1e6+10;
    int flag,n;
    freopen("testdata.txt","r",stdin);
    freopen("result(nc).txt","w",stdout);
    scanf("%d%d",&flag,&n);
    printf("%d %d\n",flag,n);
    if(!flag){
        int a[N];
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        qsint(a,0,n-1);
        for(int i=0;i<n;i++){
            printf("%d\n",a[i]);
        }
    }
    else{
        double b[N];
        for(int i=0;i<n;i++){
            scanf("%lf",&b[i]);
        }
        qsfloat(b,0,n-1);
        for(int i=0;i<n;i++){
            printf("%lf\n",b[i]);
        }
    }
    
}