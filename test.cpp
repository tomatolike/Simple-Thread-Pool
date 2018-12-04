#include "Thread_Pool.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void mytask(void *arg)
{
    printf("thread %lu is working on task %d\n", (uintptr_t)pthread_self(), *(int*)arg);
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
        printf("Create Task %d\n",i);
        Thread_Pool::add_task(mytask, arg);
        
    }
    Thread_Pool::destroy();
    return 0;
}
