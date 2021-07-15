#ifndef SCHED_H_
#define SCHED_H_

#include "heap.h"
#include "unistd.h"
#include "pthread.h"

using namespace std;

/*
 *  Describes the structure of a task with its priority,
 *  function to be executed and its supporting args.
 */
class task
{
public:
	task(uint64_t, void (*fptr) (void *, int), void *);

	uint64_t pri;
	void (*fptr) (void *, int);
	void *args;
};

/*
 * Backed by a heap, this priority queue is able to execute
 * tasks based on some priority.
 */
class priority_queue
{
public:
	priority_queue(int);
	~priority_queue();

	/*  Public modifiers. */
	task get_next_task();

	heap *hp;
	int remaining;
	pthread_cond_t cv;
	pthread_mutex_t mutex;
};

/*  Enumerates the different scheduler states. */
typedef enum sched_state
{
	/*  Scheduler is accepting tasks and is running currently. */
	SCHED_RUNNING,

	/*  Scheduler is accepting tasks but will execute at a later time. */
	SCHED_STOPPED,

	/*  Scheduler is done with all its execution. */
	SCHED_DONE;
} sched_state_t;

/*
 * Main scheduler class with the ability to post a new task to either
 * run immediately or be queued up and run later.
 */
class sched
{
public:

	sched(int, int);
	~sched();

	/*  Public modifiers. */
	int get_thread_index();
	sched_post(task *, int);
	sched_execute();
	sched_done();

	priority_queue_t *pq;
	int num_workers;
	pthread_t *workers;
	sched_state_t state;
};

static void worker_func(void *);
static void process_task(task *, int);
#endif /*  SCHED_H_ */

