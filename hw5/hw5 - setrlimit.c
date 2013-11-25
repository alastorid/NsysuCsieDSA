#include <stdio.h>
#include <sys/resource.h>

int Ackerman(int m, int n)
{
if (m == 0) return n+1;
if (n == 0) return Ackerman(m-1,1);

return Ackerman(m-1,Ackerman(m,n-1));
}

int main()
{
const rlim_t kStackSize = 1024 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
rl.rlim_cur = kStackSize;

 setrlimit(RLIMIT_STACK, &rl);


    int m,n;

    for (m=0; m<=10; ++m )
       for (n=0; n<=10; ++n)
        printf("Ackerman(%d,%d) = %d\n",m,n,Ackerman(m,n));

return 0;
}
