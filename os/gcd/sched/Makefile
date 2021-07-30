CC=g++
CFLAGS=-g

SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEPS := $(patsubst %.cpp, %.o, $(SRC))

LIBS= -Lpthread

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libsched.a: $(OBJ)
	ar rcs libsched.a $(OBJ)

clean:
	rm -rf libsched.a *.o
