/*
Author:B003040020
Date: 2012.11.4
Propose:一個程式，可以處理兩個多項式之加法與乘法
*/
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int coefficient;
    int exponent;
    struct node *next;// node address
};

int addnode(struct node **top,int exp,int coe)
{
    struct node *now=*top;
    struct node *pre=NULL;
    struct node *New=NULL;
    while(now!=NULL&& now->exponent > exp )
    {
        pre=now;
        now=now->next;
    }

    if (now!=NULL && now->exponent == exp)
    {
        now->coefficient+=coe;
    }
    else
    {
        New=malloc(sizeof(struct node));
        New->coefficient=coe;
        New->exponent=exp;
        New->next=now;
        if (pre!=NULL)
        {
            pre->next=New;
        }
        else
        {
            *top=New;
        }
    }
    return 0;
}

int CollectGarbage(struct node **top)
{
    struct node *garbage=NULL;
    struct node *now=*top;
    struct node *pre=NULL;

    while(now!=NULL)
    {

        if (now->coefficient==0)
        {
            garbage=now;
            if (pre!=NULL)
            {
                pre->next=now->next;
                now=pre;
            }
            else
            {
                (*top)=now->next;
                now=*top;
            }
            free(garbage);
            continue;
        }
        pre=now;
        now=now->next;
    }
    return 0;
}

struct node *add(struct node *a,struct node *b)
{
    struct node *Restop=NULL;
    for(; a!=NULL; a=a->next)
        addnode(&Restop,a->exponent,a->coefficient);

    for(; b!=NULL; b=b->next)
        addnode(&Restop,b->exponent,b->coefficient);

    return Restop;
}

struct node *mul(struct node *a,struct node *b)
{
    struct node *Restop=NULL;
    struct node *n;

    for(; a!=NULL; a=a->next)
        for(n=b; n!=NULL; n=n->next)
            addnode(&Restop,(a->exponent) +(n->exponent),(a->coefficient) *(n->coefficient) );

    return Restop;
}
/* Recursive Way to free the list (suddenly thought) */
void Whoafree(struct node **top)
{
    if (*top ==NULL) return;
    if ((*top)->next !=NULL ) Whoafree( &((*top)->next) );
    free(*top);
    *top=NULL;
}

int main()
{
    int test_case,i,j,num,coe,exp;

    scanf("%d",&test_case);

    struct node *A=NULL;
    struct node *B=NULL;
    struct node *RES=NULL;
    struct node *now=NULL;

    for(i=0; i<test_case; ++i)
    {
        /* -Build A && B link list- */
        scanf("%d",&num);

        for(j=0; j<num; ++j)
        {
            scanf("%d%d",&coe,&exp);
            addnode(&A,exp,coe);
        }
        CollectGarbage(&A);
        scanf("%d",&num);

        for(j=0; j<num; ++j)
        {
            scanf("%d%d",&coe,&exp);
            addnode(&B,exp,coe);
        }

        CollectGarbage(&B);
        /* -ADD- */
        printf("Case %d:\nADD\n",i+1);
        RES=add(A,B);
        CollectGarbage(&RES);
        now=RES;
        if (RES==NULL) printf("0 0\n");
        else
            for(; now!=NULL; now=now->next)
                printf("%d\t%d\n",now->coefficient,now->exponent);

        Whoafree(&RES);

        /* -MULTIPLY- */
        printf("MULTIPLY\n");
        RES=mul(A,B);
        CollectGarbage(&RES);
        now=RES;
        if (RES==NULL) printf("0 0\n");
        else
            for(; now!=NULL; now=now->next)
                printf("%d\t%d\n",now->coefficient,now->exponent);

        Whoafree(&RES);


        Whoafree(&A);
        Whoafree(&B);
    }


    return 0;
}
