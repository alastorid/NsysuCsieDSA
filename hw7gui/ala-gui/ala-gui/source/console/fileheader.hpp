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
