#
# Makefile
#
# Spellcheck tool using C++ 
# Author: Arjun Rao
#


# compiler to use
CC = c++

# flags to pass compiler
CFLAGS = -ggdb3 -O0

# name for executable
EXE = spellcheck

# space-separated list of header files
HDRS = fileloader.h dictionary.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = spellcheck.cpp fileloader.cpp dictionary.cpp

# automatically generated list of object files
OBJS = $(SRCS:.cpp=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
