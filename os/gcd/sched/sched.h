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
	SCHED_DONE
} sched_state_t;

/*
 *  Describes the structure of a task with its priority,
 *  function to be executed and its supporting args.
 */
class task
{
public:
	task(uint64_t, void (*fptr) (void *, int), void *args);
	void process(int);

	uint64_t pri;
	void (*fptr) (void *, int);
	void *args;
};

task::task(uint64_t pri, void (*fptr) (void * args, int thread_num), void *args)
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
	heap_element *t;
	assert(!hp->empty());

	hp->remove(t);
	return (task *) t->meta;
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
	bool post(task *, bool);
	void execute();
	void done();

	priority_queue *pq;
	int num_workers;
	pthread_t *workers;
	sched_state_t state;
};

static void *worker_func(void *arg);

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
		(void) pthread_create(&workers[i], NULL, worker_func, (void *) this);
	(void) pthread_mutex_unlock(&pq->mutex);	
}

sched::~sched()
{
	int i;
	free(pq);
	pthread_exit(NULL);
}

/*
 * This waits for all threads to complete execution and cleans up
 * resources.
 */
void
sched::done()
{
	int i;
	assert(workers != NULL && pq != NULL);

	/*  Wakeup all threads blocked on the condition variable. */
	(void) pthread_mutex_lock(&pq->mutex);
	(void) pthread_cond_broadcast(&pq->cv);
	(void) pthread_mutex_unlock(&pq->mutex);

	/*  Wait for everyone to finish. */
	for (i = 0; i < num_workers; ++i)
		(void) pthread_join(workers[i], NULL);

	/*  This will invoke the priority queue's destructor. */
	delete (pq);

	delete (workers);
}

/*
 *	This posts a task to the scheduler either to be executed right away
 *	or at a later point in time.
 *
 *	Here pthread_cond_signal is used to unblock atleast a single thread
 *	waiting on a specified condition variable to process the task.
 */
bool
sched::post(task *tp, bool run_now)
{
	heap_element heap_elem;
	assert(pq != NULL && tp != NULL);

	(void) pthread_mutex_lock(&pq->mutex);
	if (pq->hp->full()) {
		(void) pthread_mutex_unlock(&pq->mutex);
		return (false);
	}

	(void) bzero(&heap_elem, sizeof (heap_elem));
	heap_elem.val = tp->pri;
	heap_elem.meta = tp;

	(void) pq->hp->insert(&heap_elem);
	pq->hp->used++;

	if (run_now) {
		state = SCHED_RUNNING;
		(void) pthread_cond_signal(&pq->cv);
	}
	
	(void) pthread_mutex_unlock(&pq->mutex);
	return (true);
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

	(void) pthread_mutex_lock(&pq->mutex);
	for (i = 0; i < num_workers; i++) {
		if (pthread_equal(workers[i], tid) != 0) {
			index = i;
			break;
		}
	}
	(void) pthread_mutex_unlock(&pq->mutex);
	return (index);
}

/*
 * This executes all the tasks currently queued up.
 * pthread_cond_broadcast - This signals all threads waiting
 * on a condition variable to wakeup.
 * pthread_cond_wait - This waits on a condition variable.
 */
void
sched::execute()
{
	assert(pq != NULL);

	(void) pthread_mutex_lock(&pq->mutex);
	state = SCHED_RUNNING;
	(void) pthread_cond_broadcast(&pq->cv);

	while (pq->hp->used > 0)
		(void) pthread_cond_wait(&pq->cv, &pq->mutex);

	state = SCHED_STOPPED;
	(void) pthread_mutex_unlock(&pq->mutex);
}

/*
 * Main method which does actual work. There are 3 possible states:
 *
 * State 1. If the scheduler is done and the heap is empty, then there is no
 *    more work to be done, so we can exit.
 * State 2. If the scheduler is stopped or the heap is empty, then there is
 *    a chance that new work may come, so wait on condition variable.
 * State 3. Otherwise we have just been woken up on the condition variable
 *    and its time to get a task and process it.
 */
static void *
worker_func(void *args)
{
	int tid;
	task *t;
	sched *sp;
	priority_queue *pq;

	assert(args != NULL);

	sp = (sched *) args;

	assert(sp != NULL && sp->pq != NULL);
	pq = sp->pq;

	(void) pthread_mutex_lock(&pq->mutex);
	for (;;) {
		/*
		 * State 1: Time to exit.
		 */
		if (sp->state == SCHED_DONE && pq->hp->empty()) {
			(void) pthread_mutex_unlock(&pq->mutex);
			break;
		}

		/*
		 * State 2: Wait please.
		 */
		if (sp->state == SCHED_STOPPED || pq->hp->empty())
			(void) pthread_cond_wait(&pq->cv, &pq->mutex);


		/*
		 * State 3: Start working.
		 */
		tid = sp->get_thread_index();
		t = pq->get_next_task();
		if (t != NULL) {
			t->fptr(args, tid);

			/*
			 * At this point there is no more work left to be
			 * done by the scheduler. Wakeup all threads blocked on
			 * the condition variable.
			 */
			if (--pq->remaining == 0)
				(void) pthread_cond_broadcast(&pq->cv);
		}
		(void) pthread_mutex_unlock(&pq->mutex);
	}
	return (NULL);
}

#endif /*  SCHED_H_ */

