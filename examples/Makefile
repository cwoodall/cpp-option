IDIR =../include
CC=g++
CFLAGS=-std=c++11 -I$(IDIR) 

ODIR=.

_DEPS = option.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

EXAMPLE_PROGRAMS = divide

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

examples: $(EXAMPLE_PROGRAMS)

divide: divide.o 
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXAMPLE_PROGRAMS)
