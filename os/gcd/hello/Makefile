CC=g++
CFLAGS=-g

SCHED=../sched

# Variables defined with := are expanded once as opposed
# to variables defined with a plain =.
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

LIBS=	-L. \
		-L$(SCHED) \
		-lsched \
		-lpthread

# $@ refers to the target name.
# $< refers to the first prerequisite, for example, if the
# following is the target:
#
# all: a.cpp b.cpp
#
# Then $@ refers to 'all' and $< refers to a.cpp.
# If you see $^ it would refer to a.cpp and b.cpp.
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

# This is a rookie mistake but it is easy to add the
# -c argument again to $(CC) here which is incorrect.
# The compilation has already happened when we specified
# the %.o target above.
hello: $(OBJ)
	$(MAKE) -C $(SCHED)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# The -C argument whenever we build for the 'sched' library
# indicates that we need to switch to that directory
# before reading the makefiles or doing anything else.
# Without that argument, the compiler will be attempting
# to do 'make ../sched' and it will terminate with an error.
clean:
	rm -rf hello *.o
	$(MAKE) -C $(SCHED) clean
