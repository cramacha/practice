This demonstrates the use of a mutex on a shared variable which is being
accessed by multiple threads.

To build this project with synchronization primitives enabled use:

```
export PTHREAD_SYNC=1
make
```

otherwise

```
export PTHREAD_SYNC=0
make
```
