WINDOWS = true
SHELL = true


CC = gcc
CD = -g
#CFLAG = -Wall -Wextra -std=c18 -pedantic
CFLAG = -Wall -Wextra -Werror -std=c18 -pedantic
EXEC = bin/Chess

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

ifeq ($(WINDOWS), true)
	ICO = src/Icone/Icone.o
#	CLIB = -L lib -I include -lSDL2main -lSDL2
	ifeq ($(SHELL), false)
		SHELL = -mwindow
	else
		SHELL = 
	endif
else
	CLIB = `sdl2-config --cflags --libs`
	SHELL = 
endif

all  : $(EXEC)

#Liste des dependances de chaque fichiers
src/main.o : src/main.c src/Board.h
src/Board.o : src/Board.c src/Board.h

%.o : %.c
	$(CC) $(CD) $(CFLAG) -o $@ -c $< $(CLIB)

$(EXEC) : $(OBJ)
	$(CC) $(CD) $(CFLAG) -o $@ $^ $(ICO) $(CLIB) $(SHELL)