EXEC = Boggle
CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g -lncurses -lm

SRC_DIR = src/
INCLUDE_DIR = include/
BIN_DIR = bin/

OBJECTS = $(addprefix $(BIN_DIR), main.o Affichage.o Game.o Liste.o Mots.o)

$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_DIR)%.o : $(SRC_DIR)%.c 
	mkdir -p $(BIN_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -f $(BIN_DIR)*.o $(EXEC)
	rm -r $(BIN_DIR)