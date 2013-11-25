/*
 *
 *          Name:Data Structure HW4
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
#include <signal.h>

int skip=0;
/* delta of x coord & y coord */
int dx[]= {2,1,-1,-2,-2,-1,1,2};
int dy[]= {1,2,2,1,-1,-2,-2,-1};

/* mark available direction of the point(x,y) @ map */
int markava(int x,int y,char *arr, char *map,int n)
{
    int i,cc=0;
    for (i=0; i<8; ++i)
    {
        arr[i]=(x+dx[i]) >=0 && (x+dx[i]) <n && (y+dy[i]) >=0 && (y+dy[i]) <n && map[ (x+dx[i]) + (y+dy[i])*n ]==0;
        cc+=arr[i];
    }
    return cc;
}

/* print the solution */
void found_solution(char *map,int n)
{
int i;
static int sol=1,sn;
if( sn != n )  sol=1,sn=n;

printf("Solution #%d while n=%d [Press Ctrl+C to skip this n]\n",sol++,n);

   for(i=0; i<n*n; ++i)
            {
                printf("%2d ",map[i]);
                if  (!((i+1)%n))printf("\n");
            }
    printf("\n");
}

/* walk around the map */
int walkaround(int x,int y,char *map,int n,int step,int sol)
{

    if (map[x+y*n]||skip) return sol;
       map[x+y*n]=step;
    char d[8]={0};
    int i;

    if (markava(x,y,d,map,n))
    for(i=0;i<8;++i)
    {
    if ( d[i] ) walkaround(x+dx[i],y+dy[i],map,n,step+1,sol);
    }

    if (step==n*n)
{
found_solution(map,n);
sol++;
}

        map[x+y*n]=0;
        return sol;
}



/* finished the walk (solution done) */
int fin(char *map,int size)
{
    int i;
    for(i=0; i<size; ++i)
        if(!map[i]) return 0;

    return 1;

}
/* used to skip some solution */
void skipit()
{
skip=1;
}

int main()
{
 signal (SIGINT,skipit);

    int iMapN;
    char *map;

    for(iMapN=1; iMapN<=6; ++iMapN)
    {
        map=malloc(iMapN*iMapN);
        memset(map,0,iMapN*iMapN);
        printf("n=%d...\n",iMapN);
        skip=0;
        /* setup finished */

        /* go around */
        if ( walkaround(0,0,map,iMapN,1,0) == 0)
            printf("No Solution!\n");
        /*  */

        free(map);
    }
    return 0;
}
