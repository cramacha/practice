#ifndef SCHED_H_
#define SCHED_H_

#include <cstring>
#include <cstdint>
#include "heap.h"
#include "pthread.h"

using namespace std;

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
 *  Describes the structure of a task with its priority,
 *  function to be executed and its supporting args.
 */
class task
{
public:
	task(uint64_t, void (*fptr) (void *, int));
	void process(int);

	uint64_t pri;
	void (*fptr) (void *, int);
	void *args;
};

task::task(uint64_t pri, void (*fptr) (void * args, sint thread_num))
{
	this->pri = pri;
	this->fptr = fptr;
	this->args = args;
}

void
task::process(int thread_num)
{
	fptr(args, thread_num);
}

/*
 * This priority queue is backed by a heap. The heap uses a task's
 * priority (defined above) for ordering.
 */
class priority_queue
{
public:
	priority_queue(int);
	~priority_queue();

	/*  Public modifiers. */
	task *get_next_task();

	heap *hp;
	int remaining;
	pthread_cond_t cv;
	pthread_mutex_t mutex;
};

priority_queue::priority_queue(int queue_depth)
{
	remaining = queue_depth;
	
	if (pthread_cond_init(&cv, NULL) != 0)
		return;

	if (pthread_mutex_init(&mutex, NULL) != 0) {
		(void) pthread_cond_destroy(&cv);
		return;
	}

	if ((hp = (heap *) malloc(queue_depth * sizeof (heap))) == NULL) {
		(void) pthread_cond_destroy(&cv);
		(void) pthread_mutex_destroy(&mutex);
		return;
	}
}

priority_queue::~priority_queue()
{
	(void) pthread_cond_destroy(&cv);
	(void) pthread_mutex_destroy(&mutex);
	free(hp);
}

task *
priority_queue::get_next_task()
{
	task *t;
	assert(!hp->empty());

	hp->remove(&t);
	return (t);
}

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
	bool sched_post(task *, bool);
	bool sched_execute();
	bool sched_done();

	priority_queue_t *pq;
	int num_workers;
	pthread_t *workers;
	sched_state_t state;
};

sched::sched(int num_workers, int queue_depth)
{
	int i;
	state = SCHED_STOPPED;
	
	if ((pq = new priority_queue(queue_depth)) == NULL)
		return;

	this->num_workers = num_workers;
	
	if ((workers = (pthread_t *) malloc(num_workers * sizeof (pthread_t))) == NULL) {
		delete (pq);
		return;
	}
	
	(void) pthread_mutex_lock(&pq->mutex);
	for (i = 0; i < num_workers; ++i)
		(void) pthread_create(workers[i], NULL, worker_func, (void *) this);
	(void) pthread_mutex_unlock(&pq->mutex);	
}

sched::~sched()
{
	int i;
	free(pq);
	pthread_exit(NULL);
}

/*
 *	This posts a task to the scheduler either to be executed right away
 *	or at a later point in time.
 *
 *	Here pthread_cond_signal is used to unblock atleast a single thread
 *	waiting on a specified condition variable to process the task.
 */
bool
sched::sched_post(task *tp; bool run_now)
{
	heap_element_t heap_elem;
	assert(pq != NULL && tp != NULL);

	(void) pthread_mutex_lock(&mutex);
	if (pq->hp->full()) {
		(void) pthread_mutex_unlock(&mutex);
		return (false);
	}

	heap_elem.val = tp->pri;
	heap_elem.meta = tp;

	(void) pq->hp->insert(heap_elem);
	pq->hp->remaining++;

	if (run_now) {
		state = SCHED_RUNNING;
		(void) pthread_cond_signal(&cv);
	}
	
	(void) pthread_mutex_unlock(&mutex);
	return (false);
}

/*
 * This gets the current thread's index from the workers' array.
 *
 * pthread_self() - gets the current thread_id for this thread.
 * pthread_equal() - compares two threads and returns 0 if equal.
 */
int
sched::get_thread_index()
{
	int i, index;
	pthread_t tid;
	assert(workers != NULL);

	tid = pthread_self();

	(void) pthread_mutex_lock(&mutex);
	for (i = 0; i < num_workers; i++) {
		if (pthread_equal(workers[i], tid) != 0) {
			index = i;
			break;
		}
	}
	(void) pthread_mutex_unlock(&mutex);
	return (index);
}

/*
 * This executes all the tasks currently queued up.
 * pthread_cond_broadcast - This signals all threads waiting
 * on a condition variable to wakeup.
 * pthread_cond_wait - This waits to be
 */
bool
sched::sched_execute()
{
	assert(pq != NULL);

	(void) pthread_mutex_lock(&mutex);
	state = SCHED_RUNNING;
	(void) pthread_cond_broadcast(&cv);

	while (pq->remaining > 0)
		(void) pthread_cond_wait(&cv);

	state = SCHED_STOPPED;
	(void) pthread_mutex_unlock(&mutex);
}

static void worker_func(void *);

#endif /*  SCHED_H_ */

