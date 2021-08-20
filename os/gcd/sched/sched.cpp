#include "sched.h"

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

priority_queue::priority_queue(int queue_depth)
{

	if (pthread_cond_init(&cv, NULL) != 0)
		return;

	if (pthread_mutex_init(&mutex, NULL) != 0) {
		(void) pthread_cond_destroy(&cv);
		return;
	}

	if ((hp = new heap(queue_depth)) == NULL) {
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
	heap_element t;
	if (hp->empty())
		return (NULL);

	hp->remove(&t);
	return (task *) t.meta;
}

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
	state = SCHED_DONE;
	/*  Wakeup all threads blocked on the condition variable. */
	(void) pthread_mutex_lock(&pq->mutex);
	(void) pthread_cond_broadcast(&pq->cv);
	(void) pthread_mutex_unlock(&pq->mutex);

	/*  Wait for everyone to finish. */
	cout << "Waiting for everyone to finish" << endl;
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
		cout << "heap full" << endl;
		(void) pthread_mutex_unlock(&pq->mutex);
		return (false);
	}

	(void) bzero(&heap_elem, sizeof (heap_elem));
	heap_elem.val = tp->pri;
	heap_elem.meta = tp;

	(void) pq->hp->insert(&heap_elem);
	if (run_now) {
		state = SCHED_RUNNING;
		(void) pthread_cond_signal(&pq->cv);
	}
	state = SCHED_STOPPED;
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

	tid = sp->get_thread_index();
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
		t = pq->get_next_task();
		(void) pthread_mutex_unlock(&pq->mutex);
		if (t != NULL) {
			t->process(tid);

			(void) pthread_mutex_lock(&pq->mutex);

			/*
			 * At this point there is no more work left to be
			 * done by the scheduler. Wakeup all threads blocked on
			 * the condition variable.
			 */
			if (pq->hp->used == 0) {
				(void) pthread_cond_broadcast(&pq->cv);
				sp->state = SCHED_DONE;
			}
		(void) pthread_mutex_unlock(&pq->mutex);
		}
	}
	return (NULL);
}


