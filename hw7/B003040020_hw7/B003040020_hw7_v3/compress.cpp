#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <cerrno>
//#include <iomanip>

#include "fileheader.hpp"
#include "compress.hpp"
#include "io.hpp"
#include "algo.hpp"
#define FORCE 0x2
#define VERBOSE 0x1

using namespace std;

class _while_encoding_ encode[0xFF+1];

string ch_code;

int printCode(node *now,uint8_t ch)
{
    if ( now == NULL ) return 0;
    if ( now->leaf==1 && ch == now->ch )
    {
        return 1;
    }

    if ( now->L )
    {
        if ( printCode(now->L,ch) )
        {
            ch_code+='0';
            return 1;
        }
    }
    if ( now->R )
    {
        if ( printCode(now->R,ch) )
        {
            ch_code+='1';
            return 1;
        }
    }

    return 0;
}


void compress(const char *FN_in,const char *FN_out,unsigned char flag)
{
    C_FileHeader FileHeader;

    fstream aux_huf_table;
    string tname(FN_out);
    tname+=".codetable.txt";
    node *root=NULL;
    char *arr=NULL;

    int i_size= FileHeader.Original_File_Size=ReadFileIntoArray(FN_in, &arr);

    fstream out;
    fstream table;
    string codes;

    out.open(FN_out,ios::out|ios::binary|ios::trunc);
    table.open(tname.c_str(),ios::out|ios::trunc);
    if(i_size==0) return;
    if ( out.bad() || table.bad() )
    {
        cerr << strerror(errno) <<endl;
        exit(EXIT_FAILURE);
    }
    table<<"Filename: "<<FN_out<<endl;

    out.seekg(32,ios::beg);

    root=BuildHuffTree(arr,i_size);
    /* 最後用 root 代表樹根 */
//    root=BuildHuffTree(arr,FileHeader.Original_File_Size);

    /* TODO:目前想到的建立charset的方式 應該有更好的寫法 暫時想不到*/
    for(int ch=0; ch<=0xFF; ++ch)
        if (printCode(root,ch))
        {
            encode[ch].value=new bitset<32>(ch_code);
            reverse(ch_code.begin(),ch_code.end());
            table<<"["<<hex<<"0x"<<ch<<"]: "<<ch_code<<endl;

            encode[ch].size=ch_code.size();
            ch_code.clear();
        }

    /*
    Offset +0x0 Dword 4bytes 超級檔頭 flag表示檔案類型 (ALAS)
    Offset +0x4 Dword 4bytes 正整數 表示編碼表的大小
    offset +0x8 Word (2bytes) 表示最長huff code的長度
    offset +0xA Dword 原始檔案大小 in bytes
    offser +0xE Dword 壓縮後檔案大小 in bytes
    offset +0x20 huff table開始
    offset [file+0]+8 本片開始

    */
    /*
    以上已用fileheader class 方式取代
    */
    /* 先寫入可怕的huff table */

    //這裡是舊版的寫法 雖然好但是很難寫~"~
    unsigned long codeValue;

    for(int i=0; i<=0xFF; ++i )
    {
        if (encode[i].size)
        {
            out.write((char*)&i,1);
            //codes=encode[i].value->to_string();
            //reverse (codes.begin(), codes.end());
            //codeValue= strtol(codes.c_str(),NULL,2) ; // add 1 to the front of code to indicate how much 0s there
            codeValue= encode[i].value->to_ulong();
            out.write((char *)&codeValue,4);
            out.write((char *)&encode[i].size,1);
        }
    }


    /* 寫入完畢 */
    /* 先寫入可怕的huff table 2.0*/
    /*
    for(int i=0;i<=0xFF;++i)
    {
        bitset<32> temp;
    if (encode[i].value) bitset<32> temp(*(encode[i].value));

    out.write((char*)(&temp),sizeof(bitset<32>));
    out.write((char*)&(encode[i].size),sizeof(unsigned char));
    }
    */
    /* 寫入完畢 */
    FileHeader.Huff_Table_Size=(int)out.tellg()-32;

    /* 轉換開始 */
    for(unsigned int i=0; i< i_size; ++i)
        B003040020_bit_write(out,*(encode[(unsigned char)arr[i]].value),encode[(unsigned char)arr[i]].size);
    /* 結束 */
    B003040020_bit_write(out,NULL,0); /* 把最後緩存的資料寫入 */



    FileHeader.Compressed_File_Size=out.tellg();
    out.seekg(ios::beg);

    out.write((char* )&FileHeader,sizeof(C_FileHeader));
    out.close();
    if (flag&VERBOSE) cout<<"Ouput:"<<FN_out<<"  Compression Ratio:"<<(int)(((float)FileHeader.Compressed_File_Size/FileHeader.Original_File_Size)*100)<<"%"<<endl;
}
