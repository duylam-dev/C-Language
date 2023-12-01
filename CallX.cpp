#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_SIZE 200
typedef struct Tree{
    char* data;
    Tree* left;
    Tree* right;
} Tree;
typedef struct stack{
    float data;
    stack* next;
} stack;
stack* makeNode(float x){
    stack* newNode = (stack *)malloc(sizeof(stack));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}
bool isEmptyStack(stack* head){
    if(head == NULL) return true; 
    return false;
}
void push(stack** head, float x){
    stack* newNode = makeNode(x);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    newNode->next = *head;
    *head = newNode;
}
float pop(stack** head){
    float data = (*head)->data;
    
    *head = (*head)->next;
    return data;
}

bool isOperator(char* c){
    if(strcmp(c,"+") == 0 || strcmp(c,"-") == 0 || strcmp(c,"*") == 0 || strcmp(c,"/") == 0){
        return true;
    }
    return false;
}
float Caculator(char* bieuThuc[], int size){
    stack* head = NULL;
    for(int i = 0; i < size; i++){
        if(strcmp(bieuThuc[i],"\0") != 0){
            if(!isOperator(bieuThuc[i])){
                float num = atof(bieuThuc[i]);
                push(&head, num);
            }else{
                float operand2 = pop(&head);
                float operand1 = pop(&head);
                if(strcmp(bieuThuc[i],"+") == 0){
                    push(&head,operand1 + operand2);
                }else if(strcmp(bieuThuc[i],"-") == 0){
                    push(&head,operand1 - operand2);
                }else if(strcmp(bieuThuc[i],"*") == 0){
                    push(&head,operand1 * operand2);
                }else if(strcmp(bieuThuc[i],"/") == 0){
                    push(&head,operand1 / operand2);
                }
            }
        }
    }
    return pop(&head);
}
Tree* makeLeaf(char *c){
    Tree* newLeaf = (Tree *)malloc(sizeof(Tree));
    newLeaf->data = c;
    newLeaf->left = NULL;
    newLeaf->right = NULL;
    return newLeaf;
}


void setPostfix(Tree* root, char* bieuThuc){
   
    if(root == NULL) return;
    setPostfix(root->left, bieuThuc);
    setPostfix(root->right, bieuThuc);
    strcat(bieuThuc, strcat(root->data, ","));
 
}

Tree* addTree(char *c[], int start, int end){
    Tree* root = NULL;
    int k = 0;
    int parentCount = 0;
    int minPrecedence = 999;
    int countOperatorOut = 0;
    int countOperatorOutLeft = 0;
    int countOperatorOutRight = 0;
    //find root
    for(int i = start; i <= end; i++){
        if(strcmp(c[i], "(") == 0){
            parentCount++;
        }else if(strcmp(c[i], ")") == 0){
            parentCount--;
        }else{
            if(parentCount == 0 && isOperator(c[i])){
                countOperatorOut++;
                int currentPrecedence = 0;
                if(strcmp(c[i], "+") == 0 || strcmp(c[i], "-") == 0){
                    currentPrecedence = 1;
                }else if(strcmp(c[i], "*") == 0 || strcmp(c[i], "/") == 0){
                    currentPrecedence = 2;
                }
                if(currentPrecedence <= minPrecedence){
                    minPrecedence = currentPrecedence;
                    root = makeLeaf(c[i]);
                    k = i;
                    countOperatorOutRight = 0;
                    countOperatorOutLeft = countOperatorOut - 1;
                }else if(i > k) countOperatorOutRight++;
            }
        } 
    }
    //create leaf
    //left
    if(k != 0){
        if(countOperatorOutLeft > 0){
            root->left = addTree(c,start,k-1);
            countOperatorOutLeft--;
        }else{
            if(strcmp(c[start], "(") == 0 && strcmp(c[k-1], ")") == 0){
                root->left = addTree(c,start + 1, k-2);
            }else{
                root->left = addTree(c,start , k-1);
            }
        }

        //right
        if(countOperatorOutRight > 0){
            root->right = addTree(c,k+1,end);
            countOperatorOutRight--;
        }else{
            if(strcmp(c[end], "\0") == 0){
                if(strcmp(c[end-1], ")") == 0 && strcmp(c[k+1], "(") == 0){
                    root->right = addTree(c,k+2, end - 2);
                }else{
                    root->right = addTree(c,k+1,end-1);
                }
            }else{
                if(strcmp(c[end], ")") == 0 && strcmp(c[k+1], "(") == 0){
                    root->right = addTree(c,k+2, end - 1);
                }else{
                    root->right = addTree(c,k+1,end);
                }
            }
        }
        
    }else{
        if(root == NULL){
            for(int i = start; i <= end; i++){ 
                root = makeLeaf(c[i]);
                break;
            }
        }
    }
    return root;
}
bool checkNum(char c){
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){
            return false;
        }
        return true;
    }

char** tachChuoi(char* input, int* soPhanTu) {
    char** mangChuoi = (char**)malloc(MAX_SIZE * sizeof(char*));
    for (int i = 0; i < MAX_SIZE; i++) {
        mangChuoi[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    }

    int index = 0;
    int len = strlen(input);
    bool checkNumUse = false;

    for (int i = 0; i < len; i++) {
        if (!checkNum(input[i])) {
            if(input[i] == '-' && !checkNumUse){
                int k = i + 1;
                int j;
                mangChuoi[index][0] = input[i];
                for(j = 1; j < len; j++){
                    if(!checkNum(input[k])){
                        break;
                    }
                    mangChuoi[index][j] = input[k];
                    k++;
                
                }
                mangChuoi[index][j] = '\0';
                index++;
                checkNumUse = true;
            }else{
                mangChuoi[index][0] = input[i];
                mangChuoi[index][1] = '\0';
                index++;
                if(input[i] == ')')checkNumUse = true;
                else checkNumUse = false;
            }
            
        } else {
            int j = i;
            while (j < len && checkNum(input[j])) {
                j++;
            }
            strncpy(mangChuoi[index], input + i, j - i);
            mangChuoi[index][j - i] = '\0';
            index++;
            i = j - 1;
            checkNumUse = true; 
        }
    }

    *soPhanTu = index;
    return mangChuoi;
}
int main(){
    char string[200];
    scanf("%s",string);
    int size;

    char** postFix = (char**)malloc(MAX_SIZE * sizeof(char*));
    for (int i = 0; i < MAX_SIZE; i++) {
        postFix[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    }
    char** res = (char**)malloc(MAX_SIZE * sizeof(char*));
    for (int i = 0; i < MAX_SIZE; i++) {
        res[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    }
    char **chuoiTach = tachChuoi(string, &size);
    setPostfix(addTree(chuoiTach,0,size),*postFix);
    char* p;
    int k = 0;
    for(int i = 0; i < size; i++){
        for(p = strtok(postFix[i],","); p != NULL; p = strtok(NULL,",")){
            strcpy(res[k], p);
            k++;
        }
    }
    bool checkIntNum = true;
    for(int i = 0; i < strlen(string); i++){
        if(string[i] == '.') checkIntNum = false; 
    }
    if(checkIntNum && Caculator(res,size) == (int)(Caculator(res,size))){
        int z = Caculator(res,size);
        printf("%d",z);
    }else{
        printf("%.1f",Caculator(res,size));
    }
   
    return 0;
}
// 10*(2-3.0/4)+1.4
