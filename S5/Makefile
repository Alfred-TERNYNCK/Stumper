##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Compiler
##

SRC= src/main.c \
	src/game.c \

OBJ = $(SRC:.c=.o)

NAME = stumper

CC = gcc

CFLAGS = -I include/

RM= rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:
	make clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
