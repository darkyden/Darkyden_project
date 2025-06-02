CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lgpiod

SRC_PILOTE = $(wildcard pilote/*.c)
SRC_INTERFACE = $(wildcard interface/*.c)
SRC_SERVICE = $(wildcard service/*.c)
SRC_PROCESSUS = $(wildcard processus/*.c)

OBJ = $(SRC_PILOTE:.c=.o) $(SRC_INTERFACE:.c=.o) $(SRC_SERVICE:.c=.o) $(SRC_PROCESSUS:.c=.o)

EXEC = lcd_demo

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)