#ifndef _DECOMPRESS_HPP_
#define _DECOMPRESS_HPP_

class _while_decoding_
{
public:
    std::bitset<32> value;
    uint8_t size;
    _while_decoding_()
    {
        value=NULL;
        size=0;
    }
};

class DecodingTree
{
public:
    unsigned char data;
    DecodingTree *left;
    DecodingTree *right;
    DecodingTree()
    {
        data=0;
        left=NULL;
        right=NULL;
    }
    ~DecodingTree()
    {
        delete left;
        delete right;
    }
};
void decompress(const char *,const char *,unsigned char );
#endif
