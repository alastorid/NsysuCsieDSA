#ifndef _ALAS_HW7_ALAS_HPP_
#define _ALAS_HW7_ALAS_HPP_
#include <bitset>

class _while_encoding_
{
public:
    std::bitset<32> *value;
    unsigned char size;
    _while_encoding_()
    {
        value=NULL;
        size=0;
    }
};

void compress(const char *,const char *,unsigned char );

#endif
