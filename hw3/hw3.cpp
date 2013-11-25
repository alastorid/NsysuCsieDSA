#include <iostream>
using namespace std;

const int dx[]= {-2,2,-1,-1,1,1,2,2},
                dy[]= {1,-1,2,-2,2,-2,1,-1};




inline int isOK(int x,int y, int dx,int dy,int n,char *wtf)
{
    return ( x+dx>=0) && (y+dx>=0) && (x+dx<n) && ( y+dy<n) && !(wtf[n*(y+dy)+x+dx]);
}


int main()
{
    int iMapN,x,y,steps,way,fway,fx,fy,pway[8],sway,mini,i;


    for(iMapN=6; iMapN<=6; ++iMapN)
    {

        char *Map=new char(iMapN*iMapN);

        for(int i=0; i<iMapN*iMapN; ++i)
            Map[i]=0;


        for(x=0,y=0,steps=1;steps<iMapN*iMapN; steps++)
        {
      Map[x+y*iMapN]=steps;

            for(int i=0; i<8; ++i)
                pway[i]=0;

            for(way=0; way<8; ++way)
            {

if(isOK(x,y,dx[way],dy[way],iMapN,Map))
                {
                    fx=x+dx[way];
                    fy=x+dy[way];


                    for(fway=0; fway<8; ++fway)
                        if(isOK(fx,fy,dx[fway],dy[fway],iMapN,Map))
                            pway[way]++;
                    sway=way;
                    mini=pway[way];
                }
            }


                   for(i=0; i<8; ++i)

                    if( pway[i]<mini && pway[i]>0)
                    {

                        sway=i;
                        mini=pway[i];

                    }

cout<<x<<" "<<y<<endl;
                    x+=dx[sway];
                    y+=dy[sway];

cout<<x<<" "<<y<<endl;

                    }

for(int i=0;i<iMapN*iMapN;++i)
{
cout<<Map[i]<<" ";
if(!(i+1)%iMapN) cout<<endl;
}
            delete Map;
        }


        return 0;
    }
