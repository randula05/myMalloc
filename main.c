#include <stdio.h>
#include "mymalloc.c"

void main(){
    int *a= (int *)MyMalloc(1000);
    int *b= (int *)MyMalloc(1000);
    char *c= (char *)MyMalloc(1000);
    int *d= (int *)MyMalloc(1000);

    Display();
    printf("\n");

    MyFree(b);
    MyFree(c);
    Display();
    printf("\n");
    
    int *z= (int *)MyMalloc(1500);

    printf("\n");

  /*  int *e = (int *)MyMalloc(10);
    Display();*/
    MyFree(d);
    Display();
    printf("\n");


}

