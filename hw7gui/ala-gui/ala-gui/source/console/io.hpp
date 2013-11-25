#ifndef _ALAS_HW7_IO_HPP_
#define _ALAS_HW7_IO_HPP_

int B003040020_bit_write(std::fstream &,std::bitset<32> ,int );

int GetFileSize(std::fstream &);

int ReadFileIntoArray(const char *,char **);
#endif
