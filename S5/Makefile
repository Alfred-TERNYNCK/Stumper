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

CPPFLAGS = -iquote include/

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:
	make clean
	$(RM) $(NAME)

debug : CFLAGS += -g3

debug : all

re:	fclean all

.PHONY: all clean fclean debug re
