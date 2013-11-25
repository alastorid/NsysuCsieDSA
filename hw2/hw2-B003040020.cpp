/*
   Author：張博雲(莊博雲) B003040020
   Date：2012.09.20(左右)
   Purpose：一個「集合」類別(set class)，其能進行加入、刪除、聯集、交集、差集、包含等運算。
   2012.09.25 Updated:cin->gets 現在可以讀空白鍵了
   2012.09.26 Bug fixed:
   ###############################################################
   ## 解說: 之前的第二次BUG的原因是因為 第一次最後scanf("%c",&ch) 輸入一個字元+ENTER('\n')
   ##          字元被讀入後 緩衝區還剩下一個'\n' , 導致下次cin.gets()從緩衝區直接讀入'\n'而沒有讀到第一筆資料
   ###############################################################
*/

#include <iostream>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
using namespace std;
/* SET物件*/
class TSet{
char lol[32];

public:
/* 創建空SET的方法*/
    TSet()
    {
        for(int i=0;i<32;++i)
            lol[i]=0;
    }
/* 以STRING來創建SET的方法*/
    TSet(char *str)
    {
        for(int i=0;i<32;++i)
            lol[i]=0;

        while( *str )
        {
            lol[(*str)/8]|=1<<((*str)%8);
            str++;
        }
    }
/* 洗空SET的方法 */
    void reset(char *str)
    {
        for(int i=0;i<32;++i)
            lol[i]=0;

        while( *str )
        {
            lol[(*str)/8]|=1<<((*str)%8);
            str++;
        }
    }
/* 運算子.+法 */
TSet operator +(TSet );
/* 運算子.-法 */
TSet operator -(TSet );
/* 運算子.*法 */
TSet operator *(TSet );
/* 運算子.>=法 用於SET */
bool operator >=(TSet );
/* 運算子.>=法 用於CHAR*/
bool operator >=(char );

/* 運算子.<<法 */
friend ostream& operator << (ostream& ,TSet);

};


/* +法實作(bitwise) */
TSet TSet::operator +(TSet b)
{
TSet temp;
for(int i=0;i<32;++i)
    temp.lol[i]=lol[i] | b.lol[i];
    return temp;
}

/* -法實作(bitwise) */
TSet TSet::operator -(TSet b)
{
TSet temp;
for(int i=0;i<32;++i)
{
    temp.lol[i]= lol[i] & (b.lol[i]^0xFF);
    /* temp.lol[i]= lol[i] & (!b.lol[i]); */
}
    return temp;
}

/* 聯集法實作(bitwise) */
TSet TSet::operator *(TSet b)
{
    TSet temp;
for(int i=0;i<32;++i)
    temp.lol[i]=lol[i] & b.lol[i];
    return temp;

}

/* 包含法實作(bitwise) */
bool TSet::operator >=(TSet b)
{
        for(int i=0;i<32;++i)
    if ( (b.lol[i] | lol[i]) != lol[i] ) return FALSE;
    return TRUE;
}

/* 包含法實作(bitwise) */
bool TSet::operator >=(char ch)
{
    if( lol[ch/8]>>(ch%8)&0x1 ) return TRUE;
    else return FALSE;
}
/* 印法實作(bitwise) */
ostream& operator<<(ostream& out,TSet lol)
{
    out<<"{";
    for(int i=0;i<256;++i)
        if( lol.lol[i/8]>>(i%8)&0x1 )
            out<<(char) i;

   out<<"}";
    return out;
}

int main ()
{
TSet A, B;
char ch,input[256];
char c;
int iCaseNumber=1,times;

cin>>times;




while(times--)
{

/* 這裡等同flush(stdin) */
while(( c=getchar()) && c!='\0' && c!='\n' );
/* 到此 */

/* 輸入第一組SET MEMBER */
    gets(input);

    A.reset(input);

/* 輸入第二組SET MEMBER */
    gets(input);
    B.reset(input);

    scanf("%c",&ch);

    cout<<"Test Case "<<iCaseNumber++<<endl;
cout<<"A: "<<A<<endl;
cout<<"B: "<<B<<endl;
cout<<"A+B: "<<A+B<<endl;
cout<<"A*B: "<<A*B<<endl;
cout<<"A-B: "<<A-B<<endl;
cout<<"B-A: "<<B-A<<endl;

if( (A>=B) == TRUE)
cout<<"A does contain B"<<endl;
else cout<<"A does not contain B"<<endl;

if( (B>=A) == TRUE)
cout<<"B does contain A"<<endl;
else cout<<"B does not contain A"<<endl;

if ((A>=ch) ==TRUE)
cout<<"'"<<ch<<"' is in A"<<endl;
else cout<<"'"<<ch<<"' is not in A"<<endl;

if ((B>=ch) ==TRUE)
cout<<"'"<<ch<<"' is in B\n"<<endl;
else cout<<"'"<<ch<<"' is not in B\n"<<endl;


}


return 0;
}
