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

/* �Τ��ǧ�o�ʾ𪺸`�I�a�}�����ڧa�}�}*/
void hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(lol *root,vector<lol*> &vec)
{
    if( root == NULL ) return;

    hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(root->l,vec);
    vec.push_back(root);
    hey_give_me_all_of_the_pointer_to_the_nodes_in_the_tree_in_inorder_please(root->r,vec);
}

/* �䨺���`�I�æ^�ǥL */
lol *Search_the_cute_tree(lol *root,int data)
{
    lol *ret=NULL;
    if( root==NULL ) return (lol *) NULL;
    if ( root ->data == data ) return root;

    if(( ret=Search_the_cute_tree(root->l,data) ) !=NULL) return ret;
    if(( ret=Search_the_cute_tree(root->r,data) ) !=NULL) return ret;
    return NULL;
}

/* �o�O�� Case 1: �R��leaf node�G�����R���Y�i�C
Case 2: ���R����nonleaf node�u���@��son�G�����N��node�R���A�ñN����son�������W�s���Y�i�C
Case 3: ���R����nonleaf node�u�����son�G���]���R����node��p�A�h��p��right subtree���A�̾a����node q�]�Yp��inorder successor�^�A�Nq������m��p����m�A�ӱNq��son�]q�u�|��right son�^�V�W�s���_�ӧY�i(�Y�i��Case 2)�C
���禡 (by b003040020)*/
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
    /* ��J (PS. �̫������j��п�J'\0' (�r�� \0) �Ҧp�bwindows�O��ctrl+z .... )*/
    while(cin>>in)
    {
        do_that_THREE_things_which_i_ve_told_you_earlier_time(&root,in);
        /* �ӳW��L�X�� */
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
        /* �L�� */
    }
    cout<<"*******************************************************\n******\t\t\tRESULT\t\t\t*******\n*******************************************************"<<endl;

    /* ���G�P�̫�@����J ��o�쪺tree*/
    cout<<"RESULT IS: ";
    for(vector<lol*>::iterator it=veclol.begin(); it<veclol.end(); ++it)
        cout<<" "<<(*it)->data;
    cout<<" !!!!!!!"<<endl;

}
