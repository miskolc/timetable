using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
#define nmax 6000
#define pb push_back
vector<short> G[nmax];
short C[6000][6000];
short F[6000][6000];
short idm[40][10];
short idp[10][20];
int viz[nmax],ante[nmax],q[nmax],snm[nmax];
int nrm[nmax],nrom[nmax];
int S,D;
ofstream fout("projectai1.out");
int LEV1,LEV2,LEV3,LEV4,LEV5,LEV6,LEV7,LEV8,LEV9,LEV10,LEV11;
int nrp,nrc;
int snrm,sigma;

bool BFS()
{
    int i;
   for(i=0;i<=D;i++)
   {
       viz[i]=0;
       q[i]=0;
   }
   q[++q[0]]=S;
   viz[S]=1;
   int front=1,u;

   int prof,ora,clasa,materie,nod;

   vector<short>::iterator it;
   while(front<=q[0])
   {
       u=q[front++];
       ///niv 6...4
       ///Nivelul 6
       if((LEV6+1<=u && u<=LEV7)
          && (LEV4+1<=ante[ante[u]] && ante[ante[u]]<=LEV5))
       {
           prof=(ante[ante[u]]-LEV4-1)/30+1;
           clasa=(u-LEV6-1)/30+1;
           ora=(u-LEV6-1)%30+1;
           materie=idm[prof][clasa];
           nod=LEV7+30*snm[clasa-1]+30*(materie-1)+ora;
           if(!viz[nod])
           {
               if(C[u][nod]>F[u][nod])
               {
                   ante[nod]=u;
                   viz[nod]=1;
                   q[++q[0]]=nod;
               }
           }
       }
       else
       if((LEV5+1<=u && u<=LEV6)
          && (LEV7+1<=ante[ante[u]] && ante[ante[u]]<=LEV8))
       {
           clasa=(u-LEV5-1)/30+1;
           materie=(ante[ante[u]]-LEV7-snm[clasa-1]*30-1)/30+1;//nu e bine
           prof=idp[clasa][materie];
           ora=(ante[ante[u]]-LEV7-snm[clasa-1]*30-1)%30+1;
           ora=(u-LEV5-1)%30+1;
           nod=LEV4+(prof-1)*30+ora;
           if(!viz[nod])
           {
               if(C[u][nod]>F[u][nod])
               {
                   ante[nod]=u;
                   viz[nod]=1;
                   q[++q[0]]=nod;
               }
           }

       }
       else
       for(it=G[u].begin();it<G[u].end();it++)
       {
           if(!viz[*it])
           {
               if(C[u][*it]>F[u][*it])
               {
                   ante[*it]=u;
                   viz[*it]=1;
                   q[++q[0]]=*it;

               }
           }
       }
   }
   return viz[D];
}

void solve()
{
    int fmin,flow=0;
    int i;
    vector<short>::iterator it;
    for(;BFS();)
    {
        for(it=G[D].begin();it<G[D].end();it++)
        {
            if(viz[*it])
            {
               fmin=C[*it][D]-F[*it][D];
               for(i=*it;i!=S;i=ante[i])
               {
                   fmin=min(fmin,C[ante[i]][i]-F[ante[i]][i]);
               }
               //cout<<*it<<" "<<fmin<<"\n";
               F[*it][D]+=fmin;
               F[D][*it]-=fmin;
               for(i=*it;i!=S;i=ante[i])
               {
                   F[ante[i]][i]+=fmin;
                   F[i][ante[i]]-=fmin;
               }
               flow+=fmin;
            }
        }
    }
    fout<<flow<<"="<<sigma<<"\n";
    int clasa,ora,prof,materie,nod;
    for(clasa=1;clasa<=nrc;clasa++)
    {
           //fout<<"CLASA: "<<clasa<<"\n";
           for(ora=1;ora<=30;ora++)
           {
               nod=LEV5+(clasa-1)*30+ora;
               for(it=G[nod].begin();it<G[nod].end();it++)
               {
                   if(*it<=LEV5)
                   {
                       if(F[*it][nod]>0)
                       {
                           prof=(*it-LEV4-1)/30+1;
                           materie=idm[prof][clasa];
                           //fout<<"  ora "<<ora<<" materie "<< materie<<" prof "<<prof<<"; \n";
                           fout<<ora<<" "<<materie<<" "<<prof<<"\n";

                       }
                   }
               }
           }
    }

}

void cit()
{

    ifstream fin("projectai.in");
    int i;
    fin>>nrp>>nrc;  ///nrp<=30 nrc<=8
    cout<<nrp<<" "<<nrc<<"\n";

    for(i=1;i<=nrc;i++)
    {
        fin>>nrm[i];                        ///nrm<=15
        snrm+=nrm[i];
        snm[i]=snrm;
    }
    LEV1=0;               ///+1    /1
    LEV2=1;               ///+nrp  /30 /25
    LEV3=1+nrp;           ///+5*nrp  /180 /145
    LEV4=LEV3+5*nrp;     ///+30*nrp  /1080 /24*30+145=720+145=865
    LEV5=LEV4+5*6*nrp;   ///+30*nrc  /1080+30*8=1080+240=1320  //865+240=1105
    LEV6=LEV5+5*6*nrc;   ///+30*nrc  /1560  //1345
    LEV7=LEV6+5*6*nrc;  ///+30*snrm  /3600+1560= 5160  //4225
    LEV8=LEV7+snrm*30;  ///+5*snrm   /5760  //4705
    LEV9=LEV8+snrm*5;  ///+snrm     /5880  //4801
    LEV10=LEV9+snrm;  ///+nrc       /5895  //4809
    LEV11=LEV10+nrc;  ///+1         /5896   //4810
    ///level1
    S=LEV1+1;
    D=LEV11+1;
    cout<<D<<"\n";
    int x,ii,i3,j;
    ///level 2 de la sursa la prof
    for(i=1;i<=nrp;i++)
    {
        fin>>x;             ///x<=30
         G[S].pb(LEV2+i);
         G[LEV2+i].pb(S);
         C[S][LEV2+i]=x;
         ///level3 de la prof la zi
         for(ii=1;ii<=5;ii++)
         {
             G[LEV2+i].pb(LEV3+5*(i-1)+ii);
             G[LEV3+5*(i-1)+ii].pb(LEV2+i);
             C[LEV2+i][LEV3+5*(i-1)+ii]=6;

             ///level4 de la zi la ora
             for(i3=1;i3<=6;i3++)
             {
                 G[LEV3+5*(i-1)+ii].pb(LEV4+5*6*(i-1)+6*(ii-1)+i3);
                 G[LEV4+5*6*(i-1)+6*(ii-1)+i3].pb(LEV3+5*(i-1)+ii);
                 C[LEV3+5*(i-1)+ii][LEV4+5*6*(i-1)+6*(ii-1)+i3]=1;
             }
         }
    }
    int i4;
     ///level 11  de la clase la sursa
     int s=0;
     for(i=1;i<=nrc;i++)
     {
         G[LEV10+i].pb(D);
         G[D].pb(LEV10+i);
         for(j=1;j<=nrm[i];j++)
         {
             fin>>nrom[j];
             C[LEV10+i][D]+=nrom[j];
             sigma+=nrom[j];
         }
         ///level 10  de la materii la clase
         for(ii=1;ii<=nrm[i];ii++)
         {
             G[LEV9+s+ii].pb(LEV10+i);
             G[LEV10+i].pb(LEV9+s+ii);
             C[LEV9+s+ii][LEV10+i]=nrom[ii];

             ///level 9  de la zile la materii
             for(i3=1;i3<=5;i3++)
             {
                 G[LEV8+s*5+(ii-1)*5+i3].pb(LEV9+s+ii);
                 G[LEV9+s+ii].pb(LEV8+s*5+(ii-1)*5+i3);
                 C[LEV8+s*5+(ii-1)*5+i3][LEV9+s+ii]=(nrom[ii]-1)/5+1;     //o singura ora din o materie pe zi

                 ///level 8 de la ore la zile
                 for(i4=1;i4<=6;i4++)
                 {
                     G[LEV7+s*30+(ii-1)*30+(i3-1)*6+i4].pb(LEV8+s*5+(ii-1)*5+i3);
                     G[LEV8+s*5+(ii-1)*5+i3].pb(LEV7+s*30+(ii-1)*30+(i3-1)*6+i4);
                     C[LEV7+s*30+(ii-1)*30+(i3-1)*6+i4][LEV8+s*5+(ii-1)*5+i3]=1;                             //o singura ora pe ora din materia restpectiva

                     ///level 7  de la orarul clasei la orarele materiilor fiecarei clase
                     G[LEV6+30*(i-1)+(i3-1)*6+i4].pb(LEV7+s*30+(ii-1)*30+(i3-1)*6+i4);
                     G[LEV7+s*30+(ii-1)*30+(i3-1)*6+i4].pb(LEV6+30*(i-1)+(i3-1)*6+i4);
                     C[LEV6+30*(i-1)+(i3-1)*6+i4][LEV7+s*30+(ii-1)*30+(i3-1)*6+i4]=1;


                 }
             }
         }
         s+=nrm[i];
     }
     ///level6 dublarea nodurilor 1 singura ora pe clasa in o singura 1 cu 1 singur profespor 1 singura materie
     for(i=1;i<=nrc*30;i++)
     {
         G[LEV5+i].pb(LEV6+i);
         G[LEV6+i].pb(LEV5+i);
         C[LEV5+i][LEV6+i]=1;

     }

     for(i=1;i<=nrc;i++)
     {
         for(j=1;j<=nrm[i];j++)
         {
             fin>>idp[i][j];
             idm[idp[i][j]][i]=j;
           ///  idcm[idp[i][j]].c


           ///level 5
           for(ii=1;ii<=30;ii++)
           {
              G[LEV5+(i-1)*30+ii].pb(LEV4+(idp[i][j]-1)*30+ii);
              G[LEV4+(idp[i][j]-1)*30+ii].pb(LEV5+(i-1)*30+ii);
              C[LEV4+(idp[i][j]-1)*30+ii][LEV5+(i-1)*30+ii]=1;
           }
         }
     }

    /*ofstream gout("date.out");;
    vector<short>::iterator it;
    for(i=1;i<=D;i++)
    {
        gout<<i<<" :   ";
        for(it=G[i].begin();it<G[i].end();it++)
        {
            if(*it>i)
            gout<<*it<<" ";
        }
        gout<<"\n";
    }

    gout.close();*/
    fin.close();

}
int main()
{
    cit();
    solve();
    fout.close();
    return 0;

}
