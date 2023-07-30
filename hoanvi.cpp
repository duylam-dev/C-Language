#include<stdio.h>
int a[100],n;
void inkq(){
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
bool check(int value){
    for(int i=0;i<n;i++){
        if(a[i]==value) return false;
    }
    return true;
}
void Try(int k){
    if(k<n){
        for(int v=1;v<=n;v++){
            if(check(v)){
                a[k]=v;
                Try(k+1);
                a[k]=0;
            }
        }
    }else{
        inkq();
    }
}
int main(){
    scanf("%d",&n);
    Try(0);
    return 0;
}