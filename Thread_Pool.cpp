#include "Thread_Pool.h"
#include "iostream"

using namespace std;

bool Thread_Pool::no_task = true;
int Thread_Pool::idle_thread = 0;
int Thread_Pool::running_thread = 0;
Task* Thread_Pool::start = NULL;
Task* Thread_Pool::end = NULL;
bool Thread_Pool::quit = false;
pthread_mutex_t Thread_Pool::Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Thread_Pool::Cond = PTHREAD_COND_INITIALIZER;

void* Thread_Pool::run(void *arg){
    while(true){
        pthread_mutex_lock(&Mutex);

        running_thread++;
        idle_thread++;

        if(start == NULL && !quit){
            pthread_cond_wait(&Cond, &Mutex);
        }

        idle_thread--;

        if(!quit){
            Task *t = start;
            start = t->next;
            pthread_mutex_unlock(&Mutex);
            t->run(t->arg);
            free(t);
            pthread_mutex_lock(&Mutex);
        }

        running_thread--;

        if(quit){
            if(!running_thread){
                pthread_cond_signal(&Cond);
            }
            pthread_mutex_unlock(&Mutex);
            break;
        }
        pthread_mutex_unlock(&Mutex);
    }
    return NULL;
}

void Thread_Pool::initial(int max_thread_num){

    for(int i=0; i<max_thread_num; i++){
        pthread_t tid;
        pthread_create(&tid,NULL,run,NULL);
    }
    cout << "Thread Pool Initialized" <<endl;
}

void Thread_Pool::add_task(void (*run)(void *arg), void *arg){
    pthread_mutex_lock(&Mutex);
    
    Task *t = new Task();
    t->run = run;
    t->arg = arg;
    t->next = NULL;
    
    if(start == NULL){
        start = t;
    }
    else{
        end->next = t;
    }
    end = t;

    if(idle_thread>0) pthread_cond_signal(&Cond);

    pthread_mutex_unlock(&Mutex);
}

void Thread_Pool::destroy(bool force){
    
    if(!force){
        pthread_mutex_lock(&Mutex);
        quit = true;
        if(idle_thread > 0){
            pthread_cond_broadcast(&Cond);
        }
        if(running_thread > 0){
            pthread_cond_wait(&Cond, &Mutex);
        }
        pthread_mutex_unlock(&Mutex);
    }
    
    pthread_mutex_lock(&Mutex);
    while(start != NULL){
        Task *t = start;
        start = t->next;
        
        free(t);
    }
    pthread_mutex_unlock(&Mutex);

    
    pthread_mutex_destroy(&Mutex);
    
    pthread_cond_destroy(&Cond);
    cout<<"Thread Pool Destroied"<<endl;
}