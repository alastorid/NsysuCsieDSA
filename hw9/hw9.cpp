#include <iostream>
#include <vector>

using namespace std;

class lol
{
public:
    int data;
    lol *l;
    lol *r;
    lol *f;

    lol(int data)
    {
        this->data=data;
        f=l=r=NULL;
    }

};

/* 用中序把這棵樹的節點地址都給我吧ㄎㄎ*/
void hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(lol *root,vector<lol*> &vec)
{
    if( root == NULL ) return;

    hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(root->l,vec);
    vec.push_back(root);
    hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(root->r,vec);
}

/* 找那顆節點並回傳他 */
lol *Search_the_cute_tree(lol *root,int data)
{
    lol *ret=NULL;
    if( root==NULL ) return (lol *) NULL;
    if ( root ->data == data ) return root;

    if(( ret=Search_the_cute_tree(root->l,data) ) !=NULL) return ret;
    if(( ret=Search_the_cute_tree(root->r,data) ) !=NULL) return ret;
    return NULL;
}

/* 這是做 Case 1: 刪除leaf node：直接刪除即可。
Case 2: 欲刪除的nonleaf node只有一個son：直接將該node刪除，並將它的son直接往上連接即可。
Case 3: 欲刪除的nonleaf node只有兩個son：假設欲刪除的node為p，則找p的right subtree中，最靠左的node q（即p之inorder successor），將q直接放置於p之位置，而將q的son（q只會有right son）向上連接起來即可(即進行Case 2)。
的函式 (by b003040020)*/
void do_that_THREE_things_which_i_ve_told_you_earlier_time(lol **root,int data)
{
    lol *prev=NULL;
    lol *cur=NULL;
    lol *Foundptr=NULL;
    lol *NearestRightNode=NULL;
    lol *New;
    /* Search */
    Foundptr=Search_the_cute_tree(*root,data);
    if ( Foundptr )
    {
        if ( Foundptr -> l && Foundptr -> r ) /* 2 sons*/
        {
            for ( NearestRightNode =NULL , cur=Foundptr->r ; cur!=NULL;)
            {
                NearestRightNode=cur;
                cur=cur->l ? cur->l : cur->r;
            }
            NearestRightNode ->l=Foundptr->l;
            NearestRightNode->f->l=NearestRightNode ->r;
            NearestRightNode ->r=Foundptr->r;
            if ( Foundptr->f->l == Foundptr  )
                Foundptr->f->l = NearestRightNode;
            else
                Foundptr->f->r = NearestRightNode;
        }
        else
        {
            if ( Foundptr->f )
            {
                if (Foundptr->f->l == Foundptr )
                    Foundptr->f->l = Foundptr->l? Foundptr->l : Foundptr->r;
                else
                    Foundptr->f->r = Foundptr->l? Foundptr->l : Foundptr->r ;

            }
            else
                *root = Foundptr->l? Foundptr->l : Foundptr->r;
        }

        delete Foundptr;
    }
    else
    {
        New=new lol(data);
        for(cur=*root; cur!=NULL;)
        {
            prev=cur;
            if(cur->data> data ) cur=cur->l;
            else cur=cur->r;
        }
        New->f=prev;

        if ( prev==NULL ) *root=New;
        else
        {
            if ( prev->data > data ) prev->l=New;
            else prev->r=New;

        }
    }
}


int main()
{
    int in;
    vector<lol*> veclol;

    lol *root=NULL;
    /* 輸入 (PS. 最後欲跳脫迴圈請輸入'\0' (字元 \0) 例如在windows是按ctrl+z .... )*/
    while(cin>>in)
    {
        do_that_THREE_things_which_i_ve_told_you_earlier_time(&root,in);
        /* 照規格印出來 */
        cout<<"Done"<<endl;
        veclol.clear();
        hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(root,veclol);

        cout<<"node";
        for(vector<lol*>::iterator it=veclol.begin(); it<veclol.end(); ++it)
            cout<<"\t"<<(*it)->data;
        cout<<endl;

        cout<<"left";
        for(vector<lol*>::iterator it=veclol.begin(); it<veclol.end(); ++it)
            if ( (*it)->l ) cout<<"\t"<<(*it)->l->data;
            else cout<<"\t-1";
        cout<<endl;

        cout<<"right";
        for(vector<lol*>::iterator it=veclol.begin(); it<veclol.end(); ++it)
            if ( (*it)->r ) cout<<"\t"<<(*it)->r->data;
            else cout<<"\t-1";
        cout<<endl;
        cout<<endl;
        /* 印完 */
    }
    cout<<"*******************************************************\n******\t\t\tRESULT\t\t\t*******\n*******************************************************"<<endl;

    /* 結果同最後一次輸入 後得到的tree*/
    cout<<"RESULT IS: ";
    for(vector<lol*>::iterator it=veclol.begin(); it<veclol.end(); ++it)
        cout<<" "<<(*it)->data;
    cout<<" !!!!!!!"<<endl;

}
