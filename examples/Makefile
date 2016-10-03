IDIR =../include
CFLAGS=-std=c++11 -I$(IDIR) 

ODIR=.

_DEPS = option.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

EXAMPLE_PROGRAMS = divide

$(ODIR)/%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

examples: $(EXAMPLE_PROGRAMS)

divide: divide.o 
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXAMPLE_PROGRAMS)
