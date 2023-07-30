#include<stdio.h>
int a[8][8];
void init(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            a[i][j]=0;
        }
    }
}
void inkq(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}
bool check(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(a[i][j]!=0) return false;
        } 
    }
    return true;
}

int main(){

    return 0;
}