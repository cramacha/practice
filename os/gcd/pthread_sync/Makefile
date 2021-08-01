CC=g++
CFLAGS=-g

SCHED=../sched
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEPS := $(patsubst %.cpp, %.o, $(SRC))

ifeq ($(PTHREAD_SYNC), 1)
	CFLAGS+= -DPTHREAD_SYNC
endif

LIBS = -L. \
		-L$(SCHED) \
		-lsched \
		-lpthread

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pthread_sync: $(OBJ)
	$(MAKE) -C $(SCHED)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf pthread_sync *.o
	$(MAKE) -C $(SCHED) clean

