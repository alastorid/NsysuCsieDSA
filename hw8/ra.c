#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int TestCase[]= {100,500,1000,5000,10000,50000,100000,500000};

int main()
{
    srand(time(NULL));
    srand(rand());
    int i,n;

    for(i=0; i<8; ++i)
    {
        printf("%d\n",TestCase[i]);
        for(n=0; n<TestCase[i]; ++n)
            printf("%d\n",rand());
    }

    return 0;
}
