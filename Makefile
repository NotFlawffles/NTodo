CC      = gcc
CFLAGS  = -pedantic -o
INCLUDE = $(wildcard ./include/*.h)
SRC     = $(wildcard ./src/*.c)
OBJECT  = ntodo

default: $(INCLUDE) $(SRC)
	$(CC) $(CFLAGS) $(OBJECT) $(SRC)

clean: $(OBJECT)
	rm $(OBJECT)

install:
	make default
	sudo mv $(OBJECT) /usr/bin/$(OBJECT)
