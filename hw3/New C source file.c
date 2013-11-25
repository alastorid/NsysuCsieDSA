#include <stdio.h>
#define MAPLEN 16

int   deltai[]= {2,1,-1,-2,-2,-1,1,2};
int   deltaj[]= {1,2,2,1,-1,-2,-2,-1};
int   board[MAPLEN][MAPLEN];
int   exitn(int   i,int   j,int   s,int   a[])
{
    /*求(i,j)的出口数,和各出口号于a[],s是顺序选择着法的开始序号*/
    int   i1,j1,k,count;
    for(count=k=0; k <MAPLEN; k++)
    {
        i1=i+deltai[(s+k)%MAPLEN];
        j1=j+deltaj[(s+k)%MAPLEN];
        if(i1>=0&&i1 <MAPLEN&&j1>=0&&j1 <MAPLEN&&board[i1][j1]==0)
            a[count++]=(s+k)%MAPLEN;
    }
    return   count;
}

int   next(int   i,int   j,int   s)                         /*选下一出口,s是顺序选择着法的开始序号*/
{
    int   m,k,kk,min,a[MAPLEN],b[MAPLEN],temp;
    m=exitn(i,j,s,a);                                   /*确定(i,j)的出口个数*/
    if(m==0)   return   -1;                               /*没有出口*/
    for(min=9,k=0; k <m; k++)                      /*考察各出口*/
    {
        temp=exitn(i+deltai[a[k]],j+deltaj[a[k]],s,b);
        if(temp <min)                                    /*找出有最少出口数的出口*/
        {
            min=temp;
            kk=a[k];
        }
    }
    return   kk;                                                 /*返回选中的着法*/
}

void   main()
{
    int   sx,sy,i,j,step,no,start;
    for(sx=0; sx <MAPLEN; sx++)
        for(sy=0; sy <MAPLEN; sy++)
        {
            start=0;                                     /*从零号着法开始顺序检查*/
            do
            {
                for(i=0; i <MAPLEN; i++)
                    for(j=0; j <MAPLEN; j++)   board[i][j]=0;                 /*清棋盘*/
                board[sx][sy]=1;
                i=sx;
                j=sy;
                for(step=2; step <=64; step++)
                {
                    if((no=next(i,j,start))==-1)   break;
                    i+=deltai[no];                         /*前进一步*/
                    j+=deltaj[no];
                    board[i][j]=step;
                }
                if(step> 64)   break;
                start++;                                     /*最先检查的着法序号增1*/
            }
            while(step <=64);
            for(i=0; i <MAPLEN; i++)
            {
                for(j=0; j <MAPLEN; j++)
                    printf( "%4d ",board[i][j]);
                printf( "\n\n ");
            }
            scanf( "%*c ");                                     /*键入回车,找下一个起点的解*/
        }
}
