using namespace std;
#include <iostream>
#include<fstream>
#include<vector>
ofstream fout("projectai.in");
int nrp;
int nrc;
int mpr[40],nrm[40];
int nrom[40][40];
int nrop[40];
int idp[40][40];
void cit()
{
    ifstream fin("fish.in");
    fin>>nrp;
    int i,clasa,prof,j,nro;
    for(i=1;i<=nrp;i++)
    {
        fin>>mpr[i];
    }
    int nrc=0;
    while(fin>>clasa)
    {
        nrc=max(nrc,clasa);

        fin>>prof>>nro;
        nrm[clasa]++;
        nrop[prof]+=nro;
        nrom[clasa][nrm[clasa]]=nro;
        idp[clasa][nrm[clasa]]=prof;
    }
    fout<<nrp<<" "<<nrc<<"\n";
    for(i=1;i<=nrc;i++)
    {
        fout<<nrm[i]<<" ";
    }
    fout<<"\n";
    for(i=1;i<=nrp;i++)
    {
        fout<<nrop[i]<<" ";
    }
    fout<<"\n";
    for(i=1;i<=nrc;i++)
    {
        for(j=1;j<=nrm[i];j++)
        {
            fout<<nrom[i][j]<<" ";
        }
        fout<<"\n";
    }
    for(i=1;i<=nrc;i++)
    {
        for(j=1;j<=nrm[i];j++)
        {
            fout<<idp[i][j]<<" ";
        }
        fout<<"\n";
    }

    fin.close();
}


int main()
{
    cit();

    fout.close();
    return 0;
}

