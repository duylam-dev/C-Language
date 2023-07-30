#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    node *next;
};

node *Makenode(int x){
    node *newnode=(node *)malloc(sizeof(node));
    newnode->data=x;
    newnode->next=NULL;
    return newnode;
}

void duyet(node *head){
    while(head != NULL){
        printf("%d ",head->data);
        head=head->next;
    }
}
int count(node *head){
    int dem=0;
    while(head!=NULL){
        dem++;
        head=head->next;
    }
}

void pushFront(node **head,int x){
    node *newnode=Makenode(x);
    newnode->next=*head;
    *head=newnode;
}
void pushBack(node **head,int x){
    node *temp=*head;
    node *newnode=Makenode(x);
    if(*head==NULL) {
        *head=newnode; return;
    }
    
    while(temp->next != NULL){
        temp=temp->next;
    }
    
    temp->next=newnode;
}
void insert(node **head,int k,int x){
    int n=count(*head);
    node *newnode=Makenode(x);
    
    if(k<1||k>n+1) return;
    if(k==1){
        pushFront(head,x); return;
    }
    node *temp = *head;
    for(int i=1;i<=k-2;i++){
        temp=temp->next;
    }
    newnode->next=temp->next;
    temp->next=newnode;
}
int main(){
    node *head=NULL;
    pushFront(&head,4);
    pushFront(&head,3);
    pushFront(&head,1);
    insert(&head,2,10);
    duyet(head);
    
    return 0;
}