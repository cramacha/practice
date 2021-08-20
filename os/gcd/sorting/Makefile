CC=g++
CFLAGS=-g --std=c++11

SCHED = ../sched
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))

LIBS := -L$(SCHED) \
		-L. \
		-lpthread \
		-lsched \

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

sort: $(OBJ)
	$(MAKE) -C $(SCHED)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	$(MAKE) -C $(SCHED) clean
	rm -rf sort *.o

