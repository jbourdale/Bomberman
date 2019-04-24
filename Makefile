## Makefile for mymalloc
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
			./src/engine/entitys/render.c \
			./src/engine/entitys/manager.c \
			./src/engine/components/components.c \
			./src/engine/components/position/position.c \
			./src/engine/components/fpsrate/fpsrate.c \
			./src/engine/components/animation/animation.c \
			./src/engine/components/animation/keyframe.c \
			./src/engine/components/texture/texture.c \
			./src/engine/sdl/sprite/sprite.c \
			./src/engine/sdl/sdl.c \
			./src/engine/events/events.c \
			./src/engine/systems/systems.c \
			./src/engine/systems/position/position.c \
			./src/engine/network/network.c \
			./src/engine/network/utils/utils.c \
			./src/engine/tools/entitys/fps_indicator/fps_indicator.c \
			./src/log/log.c

SRC 	= 	$(BASE_SRC)\
			src/main.c

TEST_SRC =	$(BASE_SRC)\
			src/engine/test.c

NAME	=	Bomberman

OBJ		=	$(SRC:.c=.o)

TEST_OBJ =	$(TEST_SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror -Iinclude/

LDFLAGS	=	`sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lpthread

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

test:		$(TEST_OBJ)
			$(CC) $(LDFLAGS) -o $(NAME)_test $(TEST_OBJ)

re:			fclean all

.PHONY:		all clean fclean re
