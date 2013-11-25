#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <bitset>
#include <cerrno>

int B003040020_bit_write(std::fstream &file,std::bitset<32> data,int size)
{
    static unsigned char buffer=0;
    static int carry=0;
    int wrote=0;
    for(int i=0; i<size; ++i)
    {
        buffer=(buffer<<1) | data[i];
        carry++;
        if ( carry == 8 )
        {
            file<<buffer;
            buffer=0;
            carry=0;
            wrote+=8;
        }
    }
    if(size==0) //size==0 表示要清空緩衝區
    {
        buffer<<=8-carry;
        file<<buffer;
        wrote+=carry;
    }
    return wrote;
}

int GetFileSize(std::fstream &file)
{
    int isize,now;

    now=file.tellg();

    file.seekg(0,std::ios::end);
    isize=file.tellg();
    file.seekg(now,std::ios::beg);
    return isize;
}

int ReadFileIntoArray(const char *filename,char **arr)
{
    /* 開檔 */
    std::fstream file;
    int i_size;
    file.open(filename,std::ios::in|std::ios::binary);
    if ( !file.good() )
    {
        std::cerr<<strerror(errno) <<std::endl;
        exit(EXIT_FAILURE);
    }

    i_size = GetFileSize(file);
    if ( i_size == -1) return -1;

    /* 讀入所有資料到記憶體,並記錄此輸入檔案大小 */
    (*arr)=new char[i_size];
    file.read((*arr), i_size);
    file.close();
    return i_size;
}
