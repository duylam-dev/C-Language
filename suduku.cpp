#include<stdio.h>
int a[9][9];
void khoitao(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            scanf("%d",&a[i][j]);
        }
    }
}
// 5 3 0 0 7 0 0 0 0
// 6 0 0 1 9 5 0 0 0
// 0 9 8 0 0 0 0 6 0
// 8 0 0 0 6 0 0 0 3
// 4 0 0 8 0 3 0 0 1
// 7 0 0 0 2 0 0 0 6
// 0 6 0 0 0 0 2 8 0
// 0 0 0 4 1 9 0 0 5
// 0 0 0 0 8 0 0 7 9
void inkq(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}
bool check(int row,int col,int value){
    //check hang va cot
    for(int i=0;i<9;i++){
        if(a[row][i]==value||a[i][col]==value) return false;
    }
    //check o 3x3
    int srow=row-row%3;
    int scol=col-col%3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(a[srow+i][scol+j]==value) return false;
        }
    }
    return true;
}
void Try(int row,int col){
    if(row<9&&col<9){
        if(a[row][col]==0){
            for(int v=1;v<=9;v++){
                if(check(row,col,v)){
                    a[row][col]=v;
                    Try(row,col+1);
                    a[row][col]=0;
                } 
            }
        }else{
            Try(row,col+1);
        }
                   
    }else if(col>=9){
        Try(row+1,0);
    }else{
        inkq();
    }
}

int main(){
    khoitao();
    printf("\nket qua:\n");
    Try(0,0);
    return 0;
}