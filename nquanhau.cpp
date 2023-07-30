#include<stdio.h>
int a[100][100],n;
void inkq(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
bool check(int row,int col){
    for(int i=0;i<n;i++){
        if(a[row][i]==1) return false;
        if(a[i][col]==1) return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (a[i][j] == 1) return false;
    }

    // Kiểm tra đường chéo dưới bên trái
    for (int i = row, j = col; i >=0 && j <n; i--, j++) {
        if (a[i][j] == 1) return false;
    }
    return true;
} 
void Try(int row){
    if(row==n){
        inkq();
    }else{
        for(int i=0;i<n;i++){
            if(check(row,i)){
                a[row][i]=1;
                Try(row+1);
                a[row][i]=0;
            }
        }
    }
}
int main(){
    scanf("%d",&n);
    Try(0);
    return 0;
}