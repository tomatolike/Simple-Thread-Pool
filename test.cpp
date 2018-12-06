#include "Thread_Pool.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

void mytask(void *arg)
{
    std::cout << "thread " << (uintptr_t)pthread_self() << " is working on task " <<  *(int*)arg <<"\n";
    sleep(1);
    free(arg);
    return;
}

//测试代码
int main(void)
{
    Thread_Pool::initial(3);
    int i;
    //创建十个任务
    for(i=0; i < 10; i++)
    {
        //int *arg = malloc(sizeof(int));
        //*arg = i;
        int *arg = new int(i);
        std::cout << "Create Task " << i << "\n";
        Thread_Pool::add_task(mytask, arg);
        
    }
    Thread_Pool::destroy(true);
    return 0;
}
