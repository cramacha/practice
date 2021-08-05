# Detailed comments are present in the 'hello' program
# to explain many interesting aspects of this Makefile.
CC=g++
CFLAGS=-g

SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEPS := $(patsubst %.cpp, %.o, $(SRC))

LIBS= -Lpthread

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Here the 'ar' command runs 'ranlib' or 'libtool' to
# archive all the object files into the 'libsched.a'
# file. The options 'r', 'c' and 's' indicate the following:
#
# -c: Create archive silently without any info messages.
# -r: Replace or add specified files in archive.
# -s: Writes or updates an object index file in the archive.
libsched.a: $(OBJ)
	ar rcs libsched.a $(OBJ)

clean:
	rm -rf libsched.a *.o
