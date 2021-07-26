#include "../sched/sched.h"

using namespace std;

/*
 * This does a power of 2 operation on the val supplied in
 * argument.
 */
void
power(void *arg, int thread)
{
	int *elem;
	int val;
	int res;
	assert (arg != NULL);
	elem = (int *) arg;
	val = *elem;
	res = val * val;
	*elem = res;
}

int
main(int argc, char **argv)
{
	int *nums;
	int i;
	int nworkers = atoi(argv[1]);
	int ntasks = atoi(argv[2]);
	nums = new int[ntasks];
	task **tasks = new task*[ntasks];
	sched *sp = new sched(nworkers, ntasks);

	for (i = 0; i < ntasks; ++i)
		nums[i] = i;

	/*
	 * Create a new task with priority 1, the function 'power'
	 * to be executed and the address of nums[1] as argument.
	 */
	for (i = 0; i < ntasks; ++i) {
		tasks[i] = new task(1, power, (void *) &nums[i]);

		/*  Post this task in the scheduler to be run later. */
		sp->post(tasks[i], false);
	}

	/*  Execute all tasks. */
	(void) sp->execute();

	/*  Cleanup. */
	sp->done();

	delete (nums);
	delete[] (tasks);
	return (0);
}
