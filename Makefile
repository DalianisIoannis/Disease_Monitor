CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS = -lm

BDIR = bin
ODIR = build
IDIR = headers
SDIR = src

EXECUTABLE = diseaseMonitor

_DEPS = includer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o disMonitor.o linkedList.o patients.o AVLfinal.o
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
	valgrind ./diseaseMonitor