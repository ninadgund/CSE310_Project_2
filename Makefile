
SRCDIR = .
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/util.cpp $(SRCDIR)/maxheap.cpp $(SRCDIR)/ratio.cpp $(SRCDIR)/hashtable.cpp $(SRCDIR)/bstmgr.cpp 

all : earnings

earnings : $(SOURCES)
	g++ -o earnings $(SOURCES)

# g++ -o earnings ./main.cpp ./util.cpp ./maxheap.cpp ./ratio.cpp ./hashtable.cpp ./bstmgr.cpp 