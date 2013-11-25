/*
   Author�G�i�ն�(���ն�) B003040020
   Date�G2012.09.20(���k)
   Purpose�G�@�ӡu���X�v���O(set class)�A���i��[�J�B�R���B�p���B�涰�B�t���B�]�t���B��C
   2012.09.25 Updated:cin->gets �{�b�i�HŪ�ť���F
   2012.09.26 Bug fixed:
   ###############################################################
   ## �ѻ�: ���e���ĤG��BUG����]�O�]�� �Ĥ@���̫�scanf("%c",&ch) ��J�@�Ӧr��+ENTER('\n')
   ##          �r���QŪ�J�� �w�İ��ٳѤU�@��'\n' , �ɭP�U��cin.gets()�q�w�İϪ���Ū�J'\n'�ӨS��Ū��Ĥ@�����
   ###############################################################
*/

#include <iostream>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
using namespace std;
/* SET����*/
class TSet{
char lol[32];

public:
/* �Ыت�SET����k*/
    TSet()
    {
        for(int i=0;i<32;++i)
            lol[i]=0;
    }
/* �HSTRING�ӳЫ�SET����k*/
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
/* �~��SET����k */
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
/* �B��l.+�k */
TSet operator +(TSet );
/* �B��l.-�k */
TSet operator -(TSet );
/* �B��l.*�k */
TSet operator *(TSet );
/* �B��l.>=�k �Ω�SET */
bool operator >=(TSet );
/* �B��l.>=�k �Ω�CHAR*/
bool operator >=(char );

/* �B��l.<<�k */
friend ostream& operator << (ostream& ,TSet);

};


/* +�k��@(bitwise) */
TSet TSet::operator +(TSet b)
{
TSet temp;
for(int i=0;i<32;++i)
    temp.lol[i]=lol[i] | b.lol[i];
    return temp;
}

/* -�k��@(bitwise) */
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

/* �p���k��@(bitwise) */
TSet TSet::operator *(TSet b)
{
    TSet temp;
for(int i=0;i<32;++i)
    temp.lol[i]=lol[i] & b.lol[i];
    return temp;

}

/* �]�t�k��@(bitwise) */
bool TSet::operator >=(TSet b)
{
        for(int i=0;i<32;++i)
    if ( (b.lol[i] | lol[i]) != lol[i] ) return FALSE;
    return TRUE;
}

/* �]�t�k��@(bitwise) */
bool TSet::operator >=(char ch)
{
    if( lol[ch/8]>>(ch%8)&0x1 ) return TRUE;
    else return FALSE;
}
/* �L�k��@(bitwise) */
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

/* �o�̵��Pflush(stdin) */
while(( c=getchar()) && c!='\0' && c!='\n' );
/* �즹 */

/* ��J�Ĥ@��SET MEMBER */
    gets(input);

    A.reset(input);

/* ��J�ĤG��SET MEMBER */
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
