/*
 * Task.h
 */

#ifndef SERVER_TASK_H_
#define SERVER_TASK_H_

class Task
{
public:
	Task(void (*func)(void* arg), void* arg): func(func), arg(arg) {}
	void execute() {
		func(arg);
	}
	virtual ~Task() {}

private:
	void (*func)(void* arg);
	void* arg;

};
#endif /* SERVER_TASK_H_ */
