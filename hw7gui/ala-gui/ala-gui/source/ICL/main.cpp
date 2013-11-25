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
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <cerrno>
using namespace std;

#define VERBOSE 0x1


_while_decoding_ decode[0xFF+1];

void BuildMyCuteTreeUsing0101(DecodingTree **root)
{
    if(*root==NULL)
        *root=new DecodingTree;
    int n;
    DecodingTree *now=NULL;
    bitset<32> temp;
    for(int i=0; i<=0xFF; ++i)
    {
        if (decode[i].size!=0 )
        {
            temp=decode[i].value;
            for(now=*root,n=0; n<decode[i].size; ++n)
            {
                if( temp[n] ==1 )
                {
                    if( now->right == NULL )
                        now->right=new DecodingTree;
                    now=now->right;
                }
                else
                {
                    if( now->left == NULL )
                        now->left=new DecodingTree;
                    now=now->left;
                }
            }
            now->data=i;
        }
    }
}


void decompress(const char *Inname,const char *Outname,unsigned char flag)
{
    char *arr=NULL;
    fstream output;
    output.open(Outname,ios::binary|ios::out|ios::trunc);
    if ( !output.good() )
    {
        std::cerr<<strerror(errno) <<std::endl;
        exit(EXIT_FAILURE);
    }
    if (ReadFileIntoArray(Inname,&arr)==0 ) return;
    C_FileHeader *FileHeader=(C_FileHeader *)arr;

    for(int i=0; i<FileHeader->Huff_Table_Size; i=i+6)
    {
        //unsigned long *temp=(unsigned long *)&(arr[0x20+i+1]);
        decode[(unsigned char)(arr[0x20+i])].value=*(unsigned long *)&(arr[0x20+i+1]);
        decode[(unsigned char)(arr[0x20+i])].size=arr[0x20+i+5];
    }

    DecodingTree *root=NULL;

    BuildMyCuteTreeUsing0101(&root);
    /*arr[FileHeader->Huff_Table_Size+0x20];*/ /* Content */
    DecodingTree *now=root;

    for(int i=0,outsize=0; outsize < FileHeader->Original_File_Size; ++i)
    {
        for(int bitpos=7; bitpos>=0; --bitpos)
        {
            if (arr[i+0x20+FileHeader->Huff_Table_Size]>>bitpos & 0x1 ==1 )
                now=now->right;
            else now=now->left;
            if(now->left == NULL && now->right ==NULL )
            {
                if (outsize < FileHeader->Original_File_Size) output.write((const char*)&(now->data),1);
                now=root;
                outsize++;
            }
        }
    }

    if (flag&VERBOSE) cout<<"File:"<<Outname<<"  Compression Ratio:"<<(int)(((float)FileHeader->Compressed_File_Size/FileHeader->Original_File_Size)*100)<<"%"<<endl;
}
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
#ifndef _FILEHEADER_HPP_
#define _FILEHEADER_HPP_


class C_FileHeader
{
public:
    char Magic_identifier[4];
    unsigned int Huff_Table_Size;
    unsigned int Original_File_Size;
    unsigned int Compressed_File_Size;
    // unsigned int CheckSum;

    C_FileHeader()
    {
        Magic_identifier[0]='A';
        Magic_identifier[1]='L';
        Magic_identifier[2]='A';
        Magic_identifier[3]='S';
        Huff_Table_Size=Original_File_Size=Compressed_File_Size=0;
    }
};



#endif

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
#ifndef _ALAS_HW7_IO_HPP_
#define _ALAS_HW7_IO_HPP_

int B003040020_bit_write(std::fstream &,std::bitset<32> ,int );

int GetFileSize(std::fstream &);

int ReadFileIntoArray(const char *,char **);
#endif
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int verbose=0;
int deco=0;
int force=0;

void usage()
{
    /* 參考gzip1.2.4 的help */
    cout<<"ala 1.0.2 (27 Nov 2012)\n\
usage: ala [-dhtvV] [-S suffix] [file ...]\n\
 -d\tdecompress\n\
 -h\tgive this help\n\
 -S .suf\tuse suffix .suf on compressed files\n\
 -t\ttest compressed file integrity\n\
 -v\tverbose mode\n\
 -V\tdisplay version number"<<endl;
    exit(EXIT_SUCCESS);
}

int main(int argc,char **argv)
{
    char c;
    string suffix(".ala");
    string file1;
    string file2;

    while((c=getopt(argc, argv, "dht:vV-:S:")) != -1)
    {
        switch(c)
        {
        case 'd':
            deco=1;

            break;
        case ':':
            cout <<"missing filename"<<endl;
            exit(EXIT_FAILURE);
            break;

        case 'h':
            usage();
            break;

        case 't': /* todo with CRC16*/

            break;

        case '-':/*  */
            break;
        case 'S':
            suffix=optarg;
            break;
        case 'v':
            verbose=0x1;
            break;

        case 'V':
            cout<<"ala 1.0.2 (27 Nov 2012)"<<endl;
            exit(EXIT_SUCCESS);
            break;

        case '?':
            cout<<"For help, type: alazip -h"<<endl;
            break;
        }
    }

    if(optind==argc)
    {
        cout<<"ala 1.0.2 (27 Nov 2012)\nFor help, type: alazip -h"<<endl;
        exit(EXIT_SUCCESS);
    }


    if (optind+1<argc )
    {
        file1=argv[optind];
        file2=argv[optind+1];
    }
    else if (optind<argc)
    {
        file1=argv[optind];
    }

    if (deco|| (file1.find(".ala")!=-1) ) //means decompress
    {
        if ( file2.size()>0 )
            decompress(file1.c_str() ,file2.c_str(),force|verbose);
        else
        {
            file2=argv[optind];
            file2.replace(file2.rfind("."),file2.size()-file2.rfind("."),"");
            decompress(file1.c_str() ,file2.c_str(),force|verbose);
        }
    }
    else
    {
        if ( file2.size()>0 )
            compress(file1.c_str() ,file2.c_str(),force|verbose);
        else
        {
            file2=argv[optind];
            file2+=".ala";
            compress(file1.c_str() ,file2.c_str(),force|verbose);
        }
    }

    return 0;
}
#include <deque>
#include <algorithm>

int compare(node *a,node *b)
{
    if (a->w == b->w)
    {
        while(a->leaf == 0)
            a=a->L;
        while(b->leaf == 0)
            b=b->L;

        return a->ch < b->ch;
    }
    return a->w  < b->w;
}

node * BuildHuffTree(char *arr,const unsigned int i_size)
{
    int Times[0xFF+1]= {0};
    std::deque<node*> dpn;
    node *temp=NULL;
    /* 計算每個byte出現的次數 */

    for(unsigned int i=0; i<i_size; ++i)
        Times[(unsigned char)arr[i]]++;

    /* 並以此建立所有leaf node */
    for(int i=0x0; i<=0xFF; ++i)
        if ( Times[i] )
        {
            temp= new node();
            temp->leaf=1;
            temp->ch=i;
            temp->w=Times[i];
            dpn.push_back(temp);
        }
    /* 依規定建立huffman tree */

    while(dpn.size()>1)
    {
        sort(dpn.begin(),dpn.end(),compare);
        temp=new node();
        temp->w=dpn[0]->w+dpn[1]->w;
        temp->L =dpn[0];
        temp->R=dpn[1];
        dpn.pop_front();
        dpn.pop_front();
        dpn.push_back(temp);
    }
    if ( dpn.front()->leaf==1 )
    {
        temp=new node();
        temp->w=dpn[0]->w;
        temp->L =dpn[0];
        dpn.pop_front();
        dpn.push_back(temp);
    }


    return dpn.front();
}
