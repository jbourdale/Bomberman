## Makefile for mymalloc
## Makefile for mymalloc
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

BASE_SRC =	./src/engine/resources/manager.c \
			./src/engine/resources/load/load.c \
			./src/engine/resources/load/ttf.c \
			./src/engine/resources/load/png.c \
			./src/engine/resources/resources.c \
			./src/engine/entities/init.c \
			./src/engine/entities/observable.c \
			./src/engine/entities/components.c \
			./src/engine/entities/render.c \
			./src/engine/sdl/sprite/sprite.c \
			./src/engine/sdl/sdl.c \
			./src/engine/components/fpsrate/fpsrate.c \
			./src/engine/components/animation/animation.c \
			./src/engine/components/animation/keyframe.c \
			./src/engine/components/components.c \
			./src/engine/components/position/observable.c \
			./src/engine/components/position/position.c \
			./src/engine/components/events/keystroke/keystroke.c \
			./src/engine/components/events/hover/hover.c \
			./src/engine/components/events/click/click.c \
			./src/engine/components/texture/texture.c \
			./src/engine/tools/entities/fps_indicator/fps_indicator.c \
			./src/engine/events/events.c \
			./src/engine/framerate/framerate.c \
			./src/engine/log/log.c \
			./src/engine/engine.c


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
			$(CC) -g -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

test:		$(TEST_OBJ)
			$(CC) $(LDFLAGS) -o $(NAME)_test $(TEST_OBJ)

re:			fclean all

.PHONY:		all clean fclean re
