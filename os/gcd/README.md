This provides an implementation of a grand central dispatch-type scheduler.
The scheduler provides an easy way for multiple clients to schedule their tasks
to be run in a concurrent fashion.

The 'sched' folder contains the actual scheduler which can
accept tasks for either running immediately or to be run later. Each task has a
specific priority, a function to execute and supporting args.
