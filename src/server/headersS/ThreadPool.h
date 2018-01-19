/*
 * ThreadPool.h
 *
 *  Created on: Jan 19, 2018
 *      Author: david
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "Task.h"
#include <queue>
#include <pthread.h>
#include <stdio.h>

using namespace std;
class ThreadPool {

public:
	ThreadPool(int threadsNum);
	void addTask(Task *task);
	void terminate();
	virtual ~ThreadPool();

private:
	queue<Task *> tasksQueue;
	pthread_t* threads;
	void executeTasks();
	bool stopped;
	pthread_mutex_t lock;
	static void *execute(void* arg);
};

#endif /* THREADPOOL_H_ */
