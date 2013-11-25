#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;

void A_insertion_sort(int *arr, unsigned Quantity)
{
    unsigned i;
    int j;
    int temp;

    for (i = 1; i<Quantity; i++) //���L�Ĥ@��(�����w�Ƨ�)
    {
        temp = arr[i];
        j=i-1;

        for(j=i-1; (j>=0) && (arr[j] > temp) ; --j  )
            arr[j+1] = arr[j]; //�w�ƧǤ��������

        arr[j+1] = temp;

    }
}

int Qcmp(const void *a,const void *b)
{
    return *(int*)a - *(int*)b;
}
void B_quick_sort(int *arr,unsigned Quantity)
{
    qsort(arr,Quantity,sizeof(int),Qcmp);
}

int C_radix_sort(int *arr,unsigned Quantity)
{
    int *b=new int[Quantity];
    int imax = arr[0];
    int exp = 1;
  for (int i = 0; i < Quantity; i++)
  {
    if (arr[i] > imax)
      imax = arr[i];
  }

  while (imax / exp > 0)
  {
    int Number[10] ={0};

    for (int i = 0; i < Quantity; i++)
      Number[ (arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++) /* calc their addr */
      Number[i] += Number[i - 1];

    for (int i = Quantity - 1; i >= 0; i--)
      b[--Number[arr[i] / exp % 10]] = arr[i];

    for (int i = 0; i < Quantity; i++)
      arr[i] = b[i];
    exp *= 10;

}

delete[] b;
}


int main()
{
    fstream file,outA,outB,outC; /* ��J��X���ɮ� */
    int *ForSortArr1=NULL; /* �ΨӦs���Ƥ��Ȫ��}�C���� �N�|�ʺA���t��Ŷ� */
    int *ForSortArr2=NULL;/* �ΨӦs���Ƥ��Ȫ��}�C���� �N�|�ʺA���t��Ŷ� */
    int *ForSortArr3=NULL;/* �ΨӦs���Ƥ��Ȫ��}�C���� �N�|�ʺA���t��Ŷ� */
    int Quantity,temp,arrpos;
    time_t StartTimeInSec;
    time_t Elapsed;
    time_t ttTime;
    file.open("input.txt",ios::in);
    outA.open("outputA.txt",ios::out|ios::trunc);
    outB.open("outputB.txt",ios::out|ios::trunc);
    outC.open("outputC.txt",ios::out|ios::trunc);

    if(!file.good() || !outA.good() || !outB.good()|| !outC.good() ) /* �p�G�}�ɥ��ѴN�T�T */
    {
        cerr<<strerror(errno)<<endl;
        return 0xFFFFFFFF;
    }

time(&ttTime);
/* ��ܥثe�ɶ�(gmt+8) */
    cout<<"B003040020::DataStructure::HW8 (time: "<<(ttTime%86400/3600+8)%24<<":"<<ttTime%3600/60<<":"<<ttTime%60<<")"<<endl;

    cout<<"\tA: Insertion Sort\tB: Quick Sort\tC: Radix Sort"<<endl;

    while(file>>Quantity)
    {
        ForSortArr1=new int[Quantity];
        ForSortArr2=new int[Quantity];
        ForSortArr3=new int[Quantity];
        /* Read file content into THREEEEEEEEEEEE array*/
        /*cout<<"Preparing \r";*/
        for(arrpos=0; arrpos<Quantity ; arrpos++)
        {
            file>>temp;
            ForSortArr1[arrpos]=ForSortArr2[arrpos]=ForSortArr3[arrpos]=temp;
        }

        /* Result */


        time(&StartTimeInSec);
        A_insertion_sort(ForSortArr1,Quantity);
        Elapsed = time(NULL) -StartTimeInSec;
        cout<<Quantity<<"\t"<< Elapsed <<"\t\t\t"; /* �g�L�Ӥߪ��ƪ� */



        time(&StartTimeInSec);
        B_quick_sort(ForSortArr2,Quantity);
        Elapsed = time(NULL) -StartTimeInSec;

        cout<<Elapsed<<"\t\t"; /* �g�L�Ӥߪ��ƪ���X */



        time(&StartTimeInSec);
        C_radix_sort(ForSortArr3,Quantity);
        Elapsed = time(NULL) -StartTimeInSec;
        cout<<Elapsed<<"\tsec(s)"<<endl; /* �g�L�Ӥߪ��ƪ� */

        outA<<"::::::::"<<Quantity<<"::::::::"<<endl;  /* �g�L�Ӥߪ��ƪ� */
        outB<<"::::::::"<<Quantity<<"::::::::"<<endl; /* �g�L�Ӥߪ��ƪ� */
        outC<<"::::::::"<<Quantity<<"::::::::"<<endl; /* �g�L�Ӥߪ��ƪ� */

        for(int i=0; i<Quantity; ++i)
        {
            outA<<ForSortArr1[i]<<endl;
            outB<<ForSortArr2[i]<<endl;
            outC<<ForSortArr3[i]<<endl;
        }



        delete[] ForSortArr1;
        delete[] ForSortArr2;
        delete[] ForSortArr3;

    }

outA.close();
outB.close();
outC.close();

    cout<<"all done in "<<time(NULL)-ttTime<<"secs"<<endl;

    /*
    out.open("outputB.txt",ios::out|ios::trunc);
    B_quick_sort(data,out);
    */

    return 0;
}
