/*
   Author：張博雲(莊博雲) B003040020
   Date：2012.09.17
   Purpose：印出介於1與N之間所有數之階乘
*/


#include <iostream>
#include <iomanip>
#define ARR_SIZE 100000
using namespace std;

class BigNum
{
    unsigned n[ARR_SIZE];

    public:
        /* 大數用陣列初始化的方法 */
        BigNum(unsigned *n)
        {
            for(int i=0;i<ARR_SIZE;++i)
                this->n[i]=n[i];
        }
        /* 大數一般初始化的方法 */
        BigNum()
        {
            for(int i=ARR_SIZE-1;i>0;--i)
                n[i]=0;
                n[0]=1;
        }
    friend ostream& operator<<(ostream& out,BigNum lol); /* 印出大數的方法 */
    BigNum operator*(unsigned ); /* 大數與unsigned的乘法方法 */

};

/* 用來印出物件 */
ostream& operator<<(ostream& out,BigNum lol)
{
int i=ARR_SIZE;
        while(!lol.n[i])i--; /* 找開頭元素的位置 */
        out<<lol.n[i--]; /* 目的是為了不印出開頭的0*/
        for(;i>=0;--i)
        {
            out<<setw(6) << setfill('0') <<lol.n[i]; /* 用setw又setfill的目的是為了讓例如003040020印出是003040020而不是3040020*/
        }
            return out;
}

/* 物件與數字的乘法 */
BigNum BigNum::operator*(unsigned b)
{
        BigNum temp(n); /* 先暫存一個temp來作運算*/
            unsigned add=0;
        for(int i=0;i<ARR_SIZE;++i)
        {
            temp.n[i]=temp.n[i]*b+add; /* add 是進位 */
            add=temp.n[i]/1000000; /* 算下次該進多少位 */
            temp.n[i]=temp.n[i]%1000000; /* 本位進位後的答案 */
        }
        return temp; /* 算完最後傳回去 */
}


int main ()
{
BigNum lol; /* 宣告一個大數物件 */
int n; /* 乘數 ,使用者輸入*/

while(cin>>n&&n<1); /* 題目要求輸出1~N之間的數的階層  所以<1不接受 */
//lol=lol*10;
 for(unsigned i=1;i<=n;++i) /* 印階層數從1到N */
 cout<<i<<"!="<<(lol=lol*i)<<endl;

}
