/*
 * ThreadPool.cpp
 */

#include "headersS/ThreadPool.h"
#include <unistd.h>
#include <iostream>

/*
 * constructor for the thread pool
 * @param threadNum the amount of threads to be added
 */
ThreadPool::ThreadPool(int threadsNum): stopped(false) {
	threads = new pthread_t[threadsNum];
	for(int i = 0; i < threadsNum; i++) {
		pthread_create(threads + i, NULL, execute, this);
	}
	pthread_mutex_init(&lock, NULL);
}

/*
 * execute method to run tasks
 * @param arg the thread pool itself
 */
void* ThreadPool::execute(void* arg) {
	ThreadPool *pool = (ThreadPool*) arg;
	pool->executeTasks();
	return NULL;
}

/*
 * method to add a new task
 * @param task the new task to add
 */
void ThreadPool::addTask(Task *task) {
	tasksQueue.push(task);
}

/*
 * method to execute a task
 * will delete every that is done running
 */
void ThreadPool::executeTasks() {
	while(!stopped) {
		pthread_mutex_lock(&lock);
		if(!tasksQueue.empty()) {
			Task* task = tasksQueue.front();
			tasksQueue.pop();
			pthread_mutex_unlock(&lock);
			task->execute();
			delete task;
		}
		else {
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
	}
}

/*
 * method to terminate the thread pool
 */
void ThreadPool::terminate() {
	pthread_mutex_destroy(&lock);
	stopped = true;
}

/*
 * destructor to the thread pool
 */
ThreadPool::~ThreadPool() {
	//delete all tasks
	pthread_mutex_lock(&lock);
	while(!tasksQueue.empty()) {
		Task* task = tasksQueue.front();
		tasksQueue.pop();
		delete task;
	}
	pthread_mutex_unlock(&lock);
	//delete all threads
	delete[] threads;
}

