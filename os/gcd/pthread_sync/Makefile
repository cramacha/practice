CC=g++
CFLAGS+=-g

SCHED=../sched
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEPS := $(patsubst %.cpp, %.o, $(SRC))

LIBS = -L. \
	   -L$(SCHED) \
	   -lsched \
	   -lpthread

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pthread_sync: $(OBJ)
	$(MAKE) -C $(SCHED)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	$(MAKE) -C $(SCHED) clean
	rm -rf pthread_sync *.o

