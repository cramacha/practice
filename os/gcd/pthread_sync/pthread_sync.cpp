#include "../sched/sched.h"

#ifdef PTHREAD_SYNC
pthread_mutex_t plock;
#endif

/*
 * This demonstrates the usage of a plock by incrementing a
 * shared variable a few times in a loop with or without synchronization
 * primitives.
 */
void
increment(void *args, int thread_num)
{
	int *val;
	int elem;
	int i;
	assert (args != NULL);

	val = (int *)args;
	elem = *val;
#ifdef PTHREAD_SYNC
	(void) pthread_mutex_lock(&plock);
#endif
	for (i = 0; i < 20; ++i) {
		cout << "thread: " << thread_num << " sees: " << elem << endl;
		elem = elem + 1;
		*val = elem;
	}
#ifdef PTHREAD_SYNC
	(void) pthread_mutex_unlock(&plock);
#endif
}

int
main(int argc, char **argv)
{
	sched *sp;
	task **tasks;
	int *args;
	int i;
	int queue_depth = atoi(argv[1]);
	int nworkers = atoi(argv[2]);

#ifdef PTHREAD_SYNC
	cout << "pthread sync is defined" << endl;
	if (pthread_mutex_init(&plock, NULL) != 0)
		exit(-1);
#endif

	if ((tasks = (task **) malloc(nworkers * sizeof (task *))) == NULL)
		exit(-1);

	if ((args = (int *) malloc(sizeof (int))) == NULL)
		exit(-1);

	sp = new sched(nworkers, queue_depth);

	if (sp == NULL)
		exit(-1);

	args = 0;

	/*
	 * Initialize each task with a priority of 1, pointer to the increment
	 * function which needs to be executed and address of args[i]
	 * which contains the value which needs to be incremented.
	 */
	for (i = 0; i < nworkers; ++i) {
		tasks[i] = new task(1, increment, (void *)&args);

		/*
		 * Post the task in the scheduler's queue to be run whenever possible.
		 */
		sp->post(tasks[i], false);
	}

	/*
	 * Execute all tasks in the scheduler.
	 */
	sp->execute();

	/*
	 * We are done - exit.
	 */
	sp->done();

	free(tasks);
	return (0);
}
