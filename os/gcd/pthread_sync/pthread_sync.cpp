#include "../sched/sched.h"

#ifdef PTHREAD_SYNC
pthread_mutex_t mutex;
#endif

void
print_array(int *args, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		cout << args[i] << " ";
	cout << endl;
}

/*
 * This demonstrates the usage of a mutex by incrementing a
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
	(void) pthread_mutex_lock(&mutex);
#endif
	for (i = 0; i < 20; ++i) {
		cout << "thread: " << thread_num << " sees: " << elem << endl;
		elem = elem + 1;
		*val = elem;
	}
#ifdef PTHREAD_SYNC
	(void) pthread_mutex_unlock(&mutex);
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

	if ((tasks = (task **) malloc(nworkers * sizeof (task *))) == NULL)
		exit(-1);

	if ((args = (int *) malloc(nworkers * sizeof (int))) == NULL)
		exit(-1);

	sp = new sched(nworkers, queue_depth);

	if (sp == NULL)
		exit(-1);

	for (i = 0; i < nworkers; ++i)
		args[i] = i;

	print_array(args, nworkers);

	/*
	 * Initialize each task with a priority of 1, pointer to the increment
	 * function which needs to be executed and address of args[i]
	 * which contains the value which needs to be incremented.
	 */
	for (i = 0; i < nworkers; ++i) {
		tasks[i] = new task(1, increment, (void *)&args[i]);

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
	print_array(args, nworkers);
	return (0);
}
