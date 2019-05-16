#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"
#define MAX 25000
char arr[MAX];

typedef struct node{
    int size;
    char status;
    struct node *next;
    struct node *prev;
    char *ref;
}node;

node *root;

void init(){
    root=(node*)arr;
    root->size=MAX-sizeof(node);
    root->status='0';
    root->next=NULL;
    root->prev=NULL;
    root->ref=arr+sizeof(node);
}
void split(node *ptr,size_t size){
    if(ptr->size-size<=sizeof(node))
        return;
    node *newnode=(void*)(ptr+1)+size;
    newnode->size=ptr->size-size-sizeof(node);
    ptr->size=size;
    newnode->status='0';
    newnode->ref=(void*)(newnode+1);
    newnode->next=ptr->next;
    newnode->prev=ptr;
    if(ptr->next)
        newnode->next->prev=newnode;
    ptr->next=newnode;
}
void *MyMalloc(size_t size){
    if(root==NULL) init();
    node *ptr=root;
    node *min=NULL;
    while(!(ptr==NULL)){
        if(ptr->status=='0' && ptr->size>=size){
            min=ptr;
            break;
        }
        ptr=ptr->next;
    }
    if(min==NULL) return NULL;
    ptr=min->next;
    while(ptr!=NULL){
        if(ptr->status=='0' && ptr->size>=size && ptr->size<min->size)
            min=ptr;
        ptr=ptr->next;
    }
    if(min->size>size)
        split(min,size);
        min->status='1';
        return min->ref;
}
void mergewithnext(node *ptr){
    ptr->size=(ptr->size)+(ptr->next->size)+sizeof(node);
    ptr->next=ptr->next->next;
    if(ptr->next)
        ptr->next->prev=ptr;
}
void MyFree(void *tofree){
    node *ptr=root;
    while(ptr!=NULL){
        if(ptr->ref==tofree){
            ptr->status='0';
            if(ptr->next && ptr->next->status=='0')
                mergewithnext(ptr);
            if(ptr->prev && ptr->prev->status=='0')
                mergewithnext(ptr->prev);
            return;
        }
        ptr=ptr->next;
    }
}

void Display(){
    node *temp= (node*)arr;
    while(temp!=NULL){
        printf("%p  %c  %u",temp->ref,temp->status,temp->size);
        temp=temp->next;
        printf("\n");
    }
}


