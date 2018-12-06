## Simple Thread Pool
Realize a simple thread pool by C++

### Design
The thread pool class has four methods.  

+ add\_task(): This method is used to add tasks to thread pool. The arguments will be the function pointer of the task and the arguments of the task function.

```c++
void add_task(function_pointer, arguments){
	lock(mutex); // We have to lock the mutex first, since the thread pool is visiting by mutiple threads
	add the task; // The task will be implemented as a struct. The list of tasks will be implemented as a linked list.
	signal(cond); // Signal the condition variable to wake up the threads in thead pool.
	unlock(mutex);
}
```

+ initial(): This method is used to generate theads in thread pool.

```c++
void initial(){
	for(int i=0; i<max_thread_num; i++){
		thread(Thread_Pool::run);
	}
}
```

+ destroy(): This method is used to destroy thread pool and threads in it.

```c++
void destroy(){
	lock(mutex);
	set quit mark; // The quit mark would be check by very thead so they that they should be terminated.
	if(idle_thread){
		broadcast(cond); // Wake up all the threads.
	}
	if(runing_thread){
		wait(cond); //Wait for all threads to finish.
	}
	unlock(mutex);
	destroy(cond);
	destroy(mutex);
}
```

+ run(): This is the thread function.

```c++
void run(){
	while(true){
		lock(mutex);
		
		runing_thread++;
		idle_thread++;
		
		if(no task && !quit){
			wait(cond);
		}
		
		idle_thread--;
		
		if(!quit){
			unlock(mutex);
			get and do the task;
			lock(mutex);
		}
		
		runing_thread--;
		
		if(quit){
			if(!runing_thread){
				signal(cond);
			}
			unlock(mutex);
			break;
		}
		
		unlock(mutex);
	}
}
```

### Usage

+ Use initial() method to initialize the pool.

```c++
Thread_Pool::initial(3);
```

+ Use add_task() method to add tasks to the pool.

```c++
void task(void *arg){
	....
	return;
}

int main(){
	.....
	int *arg = new int(10);
	Thread_Pool::add_task(task, arg);
	.....
}
```

+ Use destroy() method to destroy the pool.

```c++
Thread_Pool::destroy();
```

+ **Attention!** When the destroy() function is called, the pool will wait for the threads which are running to stop. However, the tasks which are still in the queue will be destroied instead of handled by threads. Or, you can call by destroy(true), then the pool will force destroy all threads and tasks without waiting.