/*
 * ThreadPool.cpp
 */

#include "headersS/ThreadPool.h"
#include <unistd.h>
#include <iostream>

ThreadPool::ThreadPool(int threadsNum): stopped(false) {
	threads = new pthread_t[threadsNum];
	for(int i = 0; i < threadsNum; i++) {
		pthread_create(threads + i, NULL, execute, this);
		cout << "thread number " << i << endl; //TODO delete
	}
	pthread_mutex_init(&lock, NULL);
}

void* ThreadPool::execute(void* arg) {
	ThreadPool *pool = (ThreadPool*) arg;
	pool->executeTasks();
	return NULL;
}

void ThreadPool::addTask(Task *task) {
	tasksQueue.push(task);
}

void ThreadPool::executeTasks() {
	while(!stopped) {
		pthread_mutex_lock(&lock);
		if(!tasksQueue.empty()) {
			Task* task = tasksQueue.front();
			tasksQueue.pop();
			cout << "got task " << endl; //TODO delete
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

void ThreadPool::terminate() {
	pthread_mutex_destroy(&lock);
	stopped = true;
}

ThreadPool::~ThreadPool() {
	//delete all tasks
	pthread_mutex_lock(&lock);
	while(!tasksQueue.empty()) {
		cout << "deleting queue " << endl; //TODO delete
		Task* task = tasksQueue.front();
		tasksQueue.pop();
		delete task;
	}
	pthread_mutex_unlock(&lock);
	//delete all threads
	delete[] threads;
}

