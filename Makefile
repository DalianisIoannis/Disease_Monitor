CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS = -lm

BDIR = bin
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
	rm -f $(BDIR)/$(EXECUTABLE)

all:
	clear
	make clean
	make
	valgrind ./diseaseMonitor -p "Assets/fakeDiseases.txt" –h1 8 –h2 3 –b 33
	# valgrind ./diseaseMonitor -p "Assets/bigEntries.txt" –h1 8 –h2 3 –b 33
	# valgrind ./diseaseMonitor -p "Assets/fakeDiseasesDups.txt" –h1 8 –h2 3 –b 33