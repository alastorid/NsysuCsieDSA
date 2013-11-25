#include <deque>
#include <algorithm>
#include "algo.hpp"

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
