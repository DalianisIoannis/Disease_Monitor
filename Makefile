CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS = -lm

ODIR = build
IDIR = headers
SDIR = src

EXECUTABLE = diseaseMonitor

_DEPS = disMonitor.h linkedList.h patients.h AVL.h HashTable.h MaxHeap.h generalFuncs.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o disMonitor.o linkedList.o patients.o AVL.o HashTable.o MaxHeap.o generalFuncs.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(ODIR)/*.o
	rm -f $(EXECUTABLE)
	find  . -name 'out*' -exec rm {} \;
	find  . -name 'myMake*' -exec rm {} \;

all:
	clear
	make clean
	make
	./diseaseMonitor -p "Assets/fakeDiseases.txt" –h1 8 –h2 3 –b 24
	# valgrind ./diseaseMonitor -p "Assets/fakeDiseases.txt" –h1 8 –h2 3 –b 24
	# valgrind ./diseaseMonitor -p "Assets/bigEntries.txt" –h1 2 –h2 2 –b 24
	# valgrind ./diseaseMonitor -p "Assets/small.txt" –h1 50 –h2 50 –b 50
	# valgrind ./diseaseMonitor -p "Assets/entrflor.txt" –h1 8 –h2 3 –b 45
	# valgrind ./diseaseMonitor -p "Assets/fakeDiseasesDups.txt" –h1 8 –h2 3 –b 33