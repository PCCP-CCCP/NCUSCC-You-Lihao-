#include<stdio.h>
#include<math.h>
void swapi(int* pa,int* pb){
    int temp=*pa;
    *pa=*pb;
    *pb=temp;
}
void swapf(double* pa,double* pb){
    double temp=*pa;
    *pa=*pb;
    *pb=temp;
}
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
void qsint(int a[],int len){
    if(len<=1){
        return;
    }
    int pivot=maxi(mini(a[0],a[(len-1)/2]),mini(maxi(a[0],a[(len-1)/2]),a[len-1]));
    int i=0,j=0,k=len;
    while(i<k){
        if(a[i]<pivot){
            swapi(&a[i++],&a[j++]);
        }
        else if(pivot<a[i]){
            swapi(&a[i],&a[--k]);
        }
        else{
            ++i;
        }
    }
    qsint(a,j);
    qsint(a+k,len-k);
}
void qsfloat(double b[],int len){
    if(len<=1){
        return;
    }
    double pivot=maxf(minf(b[0],b[(len-1)/2]),minf(maxf(b[0],b[(len-1)/2]),b[len-1]));
    int i=0,j=0,k=len;
    while(i<k){
        if(b[i]<pivot){
            swapf(&b[i++],&b[j++]);
        }
        else if(pivot<b[i]){
            swapf(&b[i],&b[--k]);
        }
        else{
            ++i;
        }
    }
    qsfloat(b,j);
    qsfloat(b+k,len-k);
}
int main(){
    const int N=5e5+10;
    int flag,n;
    freopen("testdata.txt","r",stdin);
    freopen("result(rc).txt","w",stdout);
    scanf("%d%d",&flag,&n);
    printf("%d %d\n",flag,n);
    if(!flag){
        int a[N];
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        qsint(a+1,n);
        for(int i=1;i<=n;i++){
            printf("%d\n",a[i]);
        }
    }
    else{
        double b[N];
        for(int i=1;i<=n;i++){
            scanf("%lf",&b[i]);
        }
        qsfloat(b+1,n);
        for(int i=1;i<=n;i++){
            printf("%lf\n",b[i]);
        }
    }
}