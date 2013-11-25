#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "compress.hpp"
#include "decompress.hpp"
using namespace std;

int verbose=0;
int deco=0;
int force=0;

void usage()
{
    /* °Ñ¦Ògzip1.2.4 ªºhelp */
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
