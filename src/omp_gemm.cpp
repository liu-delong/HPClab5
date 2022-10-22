#include<omp.h>
#include"matrix_tool.h"
#include<iostream>
#include<algorithm>
#include<cmath>
#include"js.h"
using namespace std;
int **A;
int **B;
int **C;
int M,N,K,T;
int fix_M;
int avg_M;
void omp_gemm()
{
    int rank=omp_get_thread_num();
    int first=rank*avg_M;
    int last=(rank+1)*avg_M;
    for(int i=first;i<last;i++)
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
}
void gemm()
{
    for(int i=0;i<M;i++)
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
    avg_M=ceil((double)M/T);
    fix_M=avg_M*T;
    A=create_matrix(fix_M,N);
    B=create_matrix(N,K);
    C=create_matrix(fix_M,K);
    init_matrix(M,N,A);
    init_matrix(N,K,B);
    jser timer;
    timer.begin();
    if(T==1)
    {
        gemm();
    }
    else
    {
        #pragma omp parallel num_threads(T)
        omp_gemm();
    }
    auto cost=timer.end_ns();
    if(M<5)
    {
        cout<<"A"<<endl;
        print_matrix(A,M,N);
        cout<<"B"<<endl;
        print_matrix(B,N,K);
        cout<<"C"<<endl;
        print_matrix(C,M,K);
    }   
    cout<<M<<" "<<T<<" "<<cost<<endl;;

}