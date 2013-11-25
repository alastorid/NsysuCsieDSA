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
    /* �̫�� root �N���� */
//    root=BuildHuffTree(arr,FileHeader.Original_File_Size);

    /* TODO:�ثe�Q�쪺�إ�charset���覡 ���Ӧ���n���g�k �ȮɷQ����*/
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
    Offset +0x0 Dword 4bytes �W�����Y flag����ɮ����� (ALAS)
    Offset +0x4 Dword 4bytes ����� ��ܽs�X���j�p
    offset +0x8 Word (2bytes) ��̪ܳ�huff code������
    offset +0xA Dword ��l�ɮפj�p in bytes
    offser +0xE Dword ���Y���ɮפj�p in bytes
    offset +0x20 huff table�}�l
    offset [file+0]+8 �����}�l

    */
    /*
    �H�W�w��fileheader class �覡���N
    */
    /* ���g�J�i�Ȫ�huff table */

    //�o�̬O�ª����g�k ���M�n���O�����g~"~
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


    /* �g�J���� */
    /* ���g�J�i�Ȫ�huff table 2.0*/
    /*
    for(int i=0;i<=0xFF;++i)
    {
        bitset<32> temp;
    if (encode[i].value) bitset<32> temp(*(encode[i].value));

    out.write((char*)(&temp),sizeof(bitset<32>));
    out.write((char*)&(encode[i].size),sizeof(unsigned char));
    }
    */
    /* �g�J���� */
    FileHeader.Huff_Table_Size=(int)out.tellg()-32;

    /* �ഫ�}�l */
    for(unsigned int i=0; i< i_size; ++i)
        B003040020_bit_write(out,*(encode[(unsigned char)arr[i]].value),encode[(unsigned char)arr[i]].size);
    /* ���� */
    B003040020_bit_write(out,NULL,0); /* ��̫�w�s����Ƽg�J */



    FileHeader.Compressed_File_Size=out.tellg();
    out.seekg(ios::beg);

    out.write((char* )&FileHeader,sizeof(C_FileHeader));
    out.close();
    if (flag&VERBOSE) cout<<"Ouput:"<<FN_out<<"  Compression Ratio:"<<(int)(((float)FileHeader.Compressed_File_Size/FileHeader.Original_File_Size)*100)<<"%"<<endl;
}
