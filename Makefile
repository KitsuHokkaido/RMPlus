CC = gcc
BIN = rm+
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(BIN)

$(BIN) : $(OBJ)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -o $@ -c $< 

clean:
	rm $(OBJ) $(BIN)
