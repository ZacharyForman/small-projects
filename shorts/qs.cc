#include <cstdio>
void s(int&a,int&b){int t=a;a=b;b=t;}
void q(int*a,int l,int u){for(int i=l+1,p=l;(u>=l)&&((i<=u)||((s(a[l],a[p]),1)&&(q(a,l,p-1),1)&&(q(a,p+1,u),0)));a[i]<a[l]?s(a[i++],a[++p]),0:i++);}

int main(){
    int x[] = {1,4,121,3,1,4,124,14,44,4,24,124,14};
    q(x,0,12);
    for(int i = 0; i < 13; i++)
        printf("%d ", x[i]);
    printf("\n");
}