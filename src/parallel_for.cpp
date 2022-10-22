#include<pthread.h>
#include<cstdio>
#include<cmath>
#include<iostream>
#include<pthread.h>
using namespace std;
class for_index
{
    public:
    int start;
    int end;
    int increment;
};
void parallel_for(int start,int end,int increment,void*(*functor)(void*),void *arg,int num_threads)
{
    if(num_threads==1)
    {
        for_index arg;
        arg.start=start;
        arg.end=end;
        arg.increment=increment;
        functor(&arg);
        return;
    }
    int n=end-start;
    int T=num_threads;
    if(T>n) T=n;
    int avg=ceil((double)n/T);
    auto args=new for_index[T];
    pthread_t thread[T];
    for(int t=0;t<T;t++)
    {
        args[t].start=avg*t;
        args[t].increment=increment;
        args[t].end=avg*(t+1);
        if(args[t].end>end)
        {
            args[t].end=end;
        }
        pthread_create(thread+t,NULL,functor,(void*)(args+t));
    }
    for(int t=0;t<T;t++)
    {
        pthread_join(thread[t],NULL);
    }
    delete[] args;
}