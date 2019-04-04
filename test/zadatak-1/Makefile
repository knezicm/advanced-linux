PROGRAM = 
CC = 
CFLAGS = 

INCLUDE = 
LIBS = 
LIBDIR = 

SRC = $(wildcard src/*.c)

OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(PROGRAM)

library: libhello.so

libhello.so:
	

$(PROGRAM): $(PROGRAM).c libhello.so
	$(CC) -o $@ $< $(CFLAGS) -L$(LIBDIR) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCLUDE)

.PHONY: clean
clean:
	rm -f lib/*.so src/*.o $(PROGRAM)

.PHONY: install
install:
	
