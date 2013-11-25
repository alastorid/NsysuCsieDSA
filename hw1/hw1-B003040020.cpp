/*
   Author�G�i�ն�(���ն�) B003040020
   Date�G2012.09.17
   Purpose�G�L�X����1�PN�����Ҧ��Ƥ�����
*/


#include <iostream>
#include <iomanip>
#define ARR_SIZE 100000
using namespace std;

class BigNum
{
    unsigned n[ARR_SIZE];

    public:
        /* �j�ƥΰ}�C��l�ƪ���k */
        BigNum(unsigned *n)
        {
            for(int i=0;i<ARR_SIZE;++i)
                this->n[i]=n[i];
        }
        /* �j�Ƥ@���l�ƪ���k */
        BigNum()
        {
            for(int i=ARR_SIZE-1;i>0;--i)
                n[i]=0;
                n[0]=1;
        }
    friend ostream& operator<<(ostream& out,BigNum lol); /* �L�X�j�ƪ���k */
    BigNum operator*(unsigned ); /* �j�ƻPunsigned�����k��k */

};

/* �ΨӦL�X���� */
ostream& operator<<(ostream& out,BigNum lol)
{
int i=ARR_SIZE;
        while(!lol.n[i])i--; /* ��}�Y��������m */
        out<<lol.n[i--]; /* �ت��O���F���L�X�}�Y��0*/
        for(;i>=0;--i)
        {
            out<<setw(6) << setfill('0') <<lol.n[i]; /* ��setw�Ssetfill���ت��O���F���Ҧp003040020�L�X�O003040020�Ӥ��O3040020*/
        }
            return out;
}

/* ����P�Ʀr�����k */
BigNum BigNum::operator*(unsigned b)
{
        BigNum temp(n); /* ���Ȧs�@��temp�ӧ@�B��*/
            unsigned add=0;
        for(int i=0;i<ARR_SIZE;++i)
        {
            temp.n[i]=temp.n[i]*b+add; /* add �O�i�� */
            add=temp.n[i]/1000000; /* ��U���Ӷi�h�֦� */
            temp.n[i]=temp.n[i]%1000000; /* ����i��᪺���� */
        }
        return temp; /* �⧹�̫�Ǧ^�h */
}


int main ()
{
BigNum lol; /* �ŧi�@�Ӥj�ƪ��� */
int n; /* ���� ,�ϥΪ̿�J*/

while(cin>>n&&n<1); /* �D�حn�D��X1~N�������ƪ����h  �ҥH<1������ */
//lol=lol*10;
 for(unsigned i=1;i<=n;++i) /* �L���h�Ʊq1��N */
 cout<<i<<"!="<<(lol=lol*i)<<endl;

}
