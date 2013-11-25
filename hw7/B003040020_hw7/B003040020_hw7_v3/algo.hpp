#ifndef _ALAS_HW7_ALGO_HPP_
#define _ALAS_HW7_ALGO_HPP_

typedef unsigned char uint8_t;

class node
{
public:
    long long int w;
    uint8_t ch;
    node *L;
    node *R;
    char leaf;

    node()
    {
        w=0;
        R=L=NULL;
        leaf=0;
        ch=0;

    }
    ~node()
    {

    }
};

node * BuildHuffTree(char *,const unsigned int );

#endif
