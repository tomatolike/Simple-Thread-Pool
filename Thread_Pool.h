#ifndef _THREAD_POOL_
#define _THREAD_POOL_

#include "pthread.h"

typedef struct Task_struct{
    void (*run)(void *arg);
    void *arg;
    struct Task_struct* next;
}Task;

class Thread_Pool{
    private:
        static bool no_task;
        static bool quit;
        static int idle_thread;
        static int running_thread;
        static Task* start;
        static Task* end;
        static pthread_mutex_t Mutex;
        static pthread_cond_t Cond;

        static void* run(void *arg);
        Thread_Pool(){};
        ~Thread_Pool(){};

    public:
        static void initial(int max_thread_num);
        static void add_task(void (*run)(void *arg), void *arg);
        static void destroy(bool force = false);
};

#endif