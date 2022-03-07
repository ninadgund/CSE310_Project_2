
SRCDIR = .
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/util.cpp $(SRCDIR)/maxheap.cpp $(SRCDIR)/ratio.cpp $(SRCDIR)/hashtable.cpp $(SRCDIR)/bst.cpp 

all : earnings

earnings : $(SOURCES)
	g++ -o earnings $(SOURCES)

# g++ -o earnings ./main.cpp ./util.cpp ./maxheap.cpp ./hashtable.cpp ./bst.cpp 