
SRCDIR = ./src
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/util.cpp $(SRCDIR)/maxheap.cpp $(SRCDIR)/hashtable.cpp $(SRCDIR)/bst.cpp 

all : earnings

earnings : $(SOURCES)
	g++ -o earnings $(SOURCES)

# g++ -o earnings ./src/main.cpp ./src/util.cpp ./src/maxheap.cpp ./src/hashtable.cpp ./src/bst.cpp 