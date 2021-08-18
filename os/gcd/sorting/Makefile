CC=g++
CFLAGS=-g

SCHED = ../sched
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))

LIBS := -L$(SCHED) \
		-L. \
		-lpthread \
		-lsched \

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sort: $(OBJ)
	$(MAKE) -C $(SCHED)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	$(MAKE) -C $(SCHED) clean
	rm -rf sort *.o

