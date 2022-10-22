#include<cstdio>
#include<iostream>
#include<omp.h>
#include<algorithm>
#include"matrix_tool.h"
#include<cmath>
#include<string>
#include"js.h"
using namespace std;
int **A;
int **B;
int **C;
int M,N,K,T;
string mode;
void default_sc()
{
    #pragma omp parallel for num_threads(T)
    for(int i=0;i<M;i++)
    {
        //printf("I am thread %d\n",omp_get_thread_num());
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
void static_sc()
{
    #pragma omp parallel for schedule(static,1) num_threads(T)
    for(int i=0;i<M;i++)
    {
        //printf("I am thread %d\n",omp_get_thread_num());
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
void dynamic_sc()
{
    #pragma omp parallel for schedule(dynamic,1) num_threads(T)
    for(int i=0;i<M;i++)
    {
        //printf("I am thread %d\n",omp_get_thread_num());
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
void test()
{
    printf("thread %d\n",omp_get_thread_num());
}
int main(int argc,char ** argv)
{
    if(argc==6)
    {
        M=stoi(argv[1]);
        N=stoi(argv[2]);
        K=stoi(argv[3]);
        T=stoi(argv[4]);
        mode=argv[5];
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
    long long int costs;
    jser timer;
    if(mode=="default")
    {
        timer.begin();
        default_sc();
        costs=timer.end_ns();
    }
    else if(mode=="static")
    {
        timer.begin();
        static_sc();
        costs=timer.end_ns();
    }
    else if(mode=="dynamic")
    {
        timer.begin();
        dynamic_sc();
        costs=timer.end_ns();
    }
    printf("%d %s %lld\n",M,mode.c_str(),costs);

}