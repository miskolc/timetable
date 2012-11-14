using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
ofstream fout("date.out");
int h[40][40],idp[40][40],cons=0;
void cit()
{
    ifstream fin("date.in");
    int i,j,ora,materie,prof;
    for(i=1;i<=8;i++)
    {
        for(j=1;j<=12;j++)
        {
            fin>>idp[i][j];
        }
    }
    for(i=1;i<=240;i++)
    {
        fin>>ora>>materie>>prof;
        h[prof][ora]++;
        if(idp[(i-1)/30+1][materie]==prof)
           cons++;
    }
    cout<<cons<<"="<<240<<"\n";
    for(i=1;i<=24;i++)
    {
        for(j=1;j<=30;j++)
        {
            fout<<h[i][j]<<" ";
            if(j%6==0)
              fout<<"\n";

            if(h[i][j]>1)
              cout<<"nu merge";
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
