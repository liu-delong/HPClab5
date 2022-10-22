#ifndef PARALLEL_FOR_H
#define PARALLEL_FOR_H
class for_index
{
    public:
    int start;
    int end;
    int increment;
};
void parallel_for(int start,int end,int increment,void*(*functor)(void*),void *arg,int num_threads);
#endif