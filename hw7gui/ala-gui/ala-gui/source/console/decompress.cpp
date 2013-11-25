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

#include "decompress.hpp"
#include "fileheader.hpp"
#include "io.hpp"

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
