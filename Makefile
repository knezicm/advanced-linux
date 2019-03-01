PROGRAM = test
CC = arm-linux-gnueabihf-gcc
CFLAGS = -O2

INCLUDE = -I./include
LIBS = 
LIBDIR = 

SRC = $(wildcard *.c)

OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBDIR) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	rm -f *.o $(PROGRAM)

