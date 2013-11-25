/*
 *
 *          Name:Data Structure HW3
 *          Author: B003040020 Henry Hong Wei Zhang
 *          Date:2012.10.12
 *          Propose:一個n*n的西洋棋盤上，騎士(knight)置於某位置(x,y)，撰寫一個程式以便找出此騎士(n2-1)次移動的順序，而每個格子只拜訪過一次。(使用stack，而不使用recursion)
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* delta of x coord & y coord */
int dx[]= {2,1,-1,-2,-2,-1,1,2};
int dy[]= {1,2,2,1,-1,-2,-2,-1};

/* the structure to save walked point info */
struct lol
{
    int x; /* the x value */
    int y; /* the y value */
    char dire[8]; /* possible walk direction ,0 for impossible,1 for possible */
    struct lol *next;
};

/* push into stack */
void push(struct lol **top,int x,int y,char *dire)
{
    struct lol *New=malloc(sizeof(struct lol));
    int i;
    if( New==NULL ) exit(EXIT_FAILURE);

    New->x=x;
    New->y=y;
    for(i=0; i<8; ++i)
        New->dire[i]=dire[i];

    New->next=(*top);
    (*top)=New;

}
/* pop stack and go back */
void pop(struct lol **top,int *x,int *y)
{
    if( *top==NULL ) return;
    struct lol *temp=(*top);
    (*top)=(*top)->next;
    if(*top)
    {

        *x=(*top)->x;
        *y=(*top)->y;

    }

    free(temp);
}

/* mark available direction of the point(x,y) @ map */
void markava(int x,int y,char *arr, char *map,int n)
{
    int i;
    for (i=0; i<8; ++i)
    {
        arr[i]=(x+dx[i]) >=0 && (x+dx[i]) <n && (y+dy[i]) >=0 && (y+dy[i]) <n && map[ (x+dx[i]) + (y+dy[i])*n ]==0 ;
    }
}

/* from the last point to the first point have no way to walk (absolute no way)*/
int absnoway(struct lol *top)
{
    int i;
    for(; top!=NULL; top=top->next )
        for(i=0; i<8; ++i)
            if( top->dire[i]==1 ) return 0;

    return 1;
}

/* this point no way (no way) */
int noway(struct lol *top)
{
    int i;
    if (top==NULL) return 1;
    for(i=0; i<8; ++i)
        if(top->dire[i]) return 0;

    return 1;
}

/* finished the walk (solution done) */
int fin(char *map,int size)
{
    int i;
    for(i=0; i<size; ++i)
        if(!map[i]) return 0;

    return 1;

}

int main()
{
    struct lol *top=NULL;
    int iMapN,i,steps, x,y,giveup;
    char dire[8],*map;

#ifdef PB
    int processbar=1;
#endif
    for(iMapN=1; iMapN<=6; ++iMapN)
    {
        map=malloc(iMapN*iMapN);
        memset(map,0,iMapN*iMapN);
        x=y=0;
        steps=1;
        giveup=0;
        printf("n=%d...\n",iMapN);
        /* setup finished */

        /* go around */
        while(giveup==0)
        {

            if ( !map[x+y*iMapN] )
            {
                markava(x,y,dire,map,iMapN);
                push(&top,x,y,dire);
                map[x+y*iMapN]=steps++;
            }

#ifdef DEBUG  /* for debug (sorry i haven't learned how to use gdb :[ ) */
            printf("%d %d  %d:\n\n",x,y,absnoway(top));


            for(i=0; i<iMapN*iMapN; ++i)
            {
                printf("%2d ",map[i]);
                if  (!((i+1)%iMapN))printf("\n");
            }



            for(now=top,j=0; now!=NULL; now=now->next,j++);
            printf("[%d]",j);
            getchar();
#endif


            if (noway(top))
            {

                if(fin(map,iMapN*iMapN)) break; /* finished */

                giveup=absnoway(top)|| (steps <1);

                /* going back */
                map[x+y*iMapN]=0;
                steps--;
                pop(&top,&x,&y);



            }
            else for(i=0; i<8; ++i) /* go next step */
                    if (top->dire[i] !=0 )
                    {
                        x+=dx[i];
                        y+=dy[i];
                        top->dire[i]=0;
                        break;
                    }
#ifdef PB
            switch(processbar)
            {
            case 1:
                printf("\r|");
                break;
            case 2:
                printf("\r\\");
                break;
            case 3:
                printf("\r-");
                break;
            case 4:
                printf("\r/");
                processbar=0;
                break;
            }
            processbar++;
            fflush(stdout);
#endif
        }
        /*  */


        /* end & print */
        printf("\r");
        if (giveup)
        {
            printf("No Solution!\n");
        }
        else   for(i=0; i<iMapN*iMapN; ++i)
            {
                printf("%2d ",map[i]);
                if  (!((i+1)%iMapN))printf("\n");
            }
        printf("\n\n");


        free(map);
    }
    return 0;
}
