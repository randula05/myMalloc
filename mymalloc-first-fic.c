#include <stdio.h>
#include <stddef.h>
#define MAX 25000
char arr[MAX];

typedef struct node{
    int size;
    int status;
    struct node *next;
    struct node *prev;
    char *ref;
}node;

node *root;

void init(){
    root=(void*)arr;
    root->size=MAX-sizeof(node);
    root->status=0;
    root->next=NULL;
    root->prev=NULL;
    root->ref=arr+sizeof(node);
}
void split(node *ptr,size_t size){
    if(ptr->size-size<=sizeof(node)) return;
    node *newnode=(void*)(ptr+1)+size;
    newnode->size=ptr->size-size-sizeof(node);
    ptr->size=size;
    newnode->status=0;
    newnode->ref=(void*)(newnode+1);
    newnode->next=ptr->next;
    newnode->prev=ptr;
    if(ptr->next) newnode->next->prev=newnode;
    ptr->next=newnode;
}
void *mymalloc(size_t size){
    if(root==NULL) init();
    node *ptr=root;
    while(ptr!=NULL){
        if(ptr->status==0 && ptr->size>=size){
            if(ptr->size>size) split(ptr,size);
            ptr->status=1;
            return ptr->ref;
        }
        ptr=ptr->next;
    }
    return NULL;
}
void mergenext(node *ptr){
    ptr->size=(ptr->size)+(ptr->next->size)+sizeof(node);
    ptr->next=ptr->next->next;
    if(ptr->next) ptr->next->prev=ptr;
}
void myfree(void *target){
    node *ptr=root;
    while(ptr!=NULL){
        if(ptr->ref==target){
            ptr->status=0;
            if(ptr->next && ptr->next->status==0) mergenext(ptr);
            if(ptr->prev && ptr->prev->status==0) mergenext(ptr->prev);
            return;
        }
        ptr=ptr->next;
    }
}
