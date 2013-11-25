#include <stdio.h>

int a[11][10000000]={0};

int Ackerman(int m, int n)
{
if (a[m][n]) return a[m][n];
if (m == 0) return n+1;
if (n == 0) return Ackerman(m-1,1);

return a[m][n]=Ackerman(m-1,Ackerman(m,n-1));
}

int main()
{

    int m,n;

  //  for (m=0; m<=10; ++m )
  m=2;
       for (n=0; n<=10000000; ++n)
        printf("Ackerman(%d,%d) = %d\n",m,n,Ackerman(m,n));

return 0;
}
