## Makefile for mymalloc
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

SRC		=	src/main.c

NAME	=	Bomberman

OBJ		=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror -Iinclude/

LDFLAGS	=

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
