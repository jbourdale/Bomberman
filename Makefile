## Makefile for mymalloc
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

BASE_SRC =	./src/engine/engine.c \
			./src/engine/entitys/components.c \
			./src/engine/entitys/init.c \
			./src/engine/entitys/sprites.c \
			./src/engine/entitys/render.c \
			./src/engine/entitys/core.c \
			./src/engine/entitys/events.c \
			./src/engine/components/components.c \
			./src/engine/components/position/position.c \
			./src/engine/sdl/sprite/sprite.c \
			./src/engine/sdl/sdl.c \
			./src/engine/systems/position/position.c \
			./src/log/log.c

SRC 	= 	$(BASE_SRC)\
			src/main.c

TEST_SRC =	$(BASE_SRC)\
			src/engine/test.c

NAME	=	Bomberman

OBJ		=	$(SRC:.c=.o)

TEST_OBJ =	$(TEST_SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror -Iinclude/

LDFLAGS	=	-I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

test:		$(TEST_OBJ)
			$(CC) $(LDFLAGS) -o $(NAME)_test $(TEST_OBJ)

re:			fclean all

.PHONY:		all clean fclean re
