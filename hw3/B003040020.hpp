#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
const int dx[]= {-2,2,-1,-1,1,1,2,2},
                dy[]= {1,-1,2,-2,2,-2,1,-1};

struct lol
{
    int x;
    int y;
    int n;
    struct lol *next;
};

class step
{
    public:

    char *map;

    step(int size)
    {
     map=(char *)malloc(size*size);
     for(int i=0;i<size*size;++i)
     map[i]=0;
    }

    ~step()
    {
        cout<<"WTF";
        free (map);
    }





    friend ostream& operator << (ostream &out,step);




};
