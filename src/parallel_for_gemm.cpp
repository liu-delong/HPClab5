#include"parallel_for.h"
#include"js.h"
#include"matrix_tool.h"
#include<algorithm>
using namespace std;
int **A,**B,**C;
int M,N,K,T;
void* func(void* _arg)
{
    for_index* arg=(for_index*)_arg;
    for(int i=arg->start;i<arg->end;i+=arg->increment)
    {
        for(int j=0;j<K;j++)
        {
            int temp=0;
            for(int z=0;z<N;z++)
            {
                temp+=A[i][z]*B[z][j];
            }
            C[i][j]=temp;
        }
    }
    return NULL;
}
int main(int argc,char** argv)
{
    if(argc==5)
    {
        M=stoi(argv[1]);
        N=stoi(argv[2]);
        K=stoi(argv[3]);
        T=stoi(argv[4]);
    }
    else
    {
        cout<<"please input M N K T:";
        cin>>M>>N>>K>>T;
    }
    A=create_matrix(M,N);
    B=create_matrix(N,K);
    C=create_matrix(M,K);
    init_matrix(M,N,A);
    init_matrix(N,K,B);
    for_index arg;
    arg.start=0;
    arg.end=M;
    arg.increment=1;
    jser timer;
    timer.begin();
    parallel_for(0,M,1,func,NULL,T);
    auto costs=timer.end_ns();
    cout<<M<<" "<<T<<" "<<costs<<endl;
    
}