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
			./src/engine/entities/manager.c \
			./src/engine/entities/components.c \
			./src/engine/entities/render.c \
			./src/engine/server/entities/init.c \
			./src/engine/server/entities/serializer.c \
			./src/engine/server/manager/manager.c \
			./src/engine/sdl/sprite/sprite.c \
			./src/engine/sdl/sdl.c \
			./src/engine/components/fpsrate/fpsrate.c \
			./src/engine/components/components.c \
			./src/engine/components/animation/animation.c \
			./src/engine/components/id/id.c \
			./src/engine/components/counter/counter.c \
			./src/engine/components/range/range.c \
			./src/engine/components/velocity/velocity.c \
			./src/engine/components/velocity/movement.c \
			./src/engine/components/animation/keyframe.c \
			./src/engine/components/collision/collision.c \
			./src/engine/components/position/observable.c \
			./src/engine/components/position/position.c \
			./src/engine/components/position/movement.c \
			./src/engine/components/position/serializer.c \
			./src/engine/components/events/keystroke/keystroke.c \
			./src/engine/components/events/hover/hover.c \
			./src/engine/components/events/click/click.c \
			./src/engine/components/texture/texture.c \
			./src/engine/components/networkable/networkable.c \
			./src/engine/components/networkable/serializer/serializer.c \
			./src/engine/network/network.c \
			./src/engine/network/events/events.c \
			./src/engine/network/configuration.c \
			./src/engine/tools/entities/fps_indicator/fps_indicator.c \
			./src/engine/events/events.c \
			./src/engine/framerate/framerate.c \
			./src/engine/log/log.c \
			./src/engine/engine.c \
			./src/game/player/player.c \
			./src/game/player/animations/idle.c \
			./src/game/player/animations/walking.c \
			./src/game/player/animations/animations.c \
			./src/game/bonus/bonus.c \
			./src/game/bomb/bomb.c \
			./src/game/bomb/animations/animations.c \
			./src/game/menus/home/home.c \
			./src/game/server/init.c \
			./src/game/server/parsing.c \
			./src/game/server/entities.c \
			./src/game/server/server.c \
			./src/game/server/player.c \
			./src/game/server/state/state.c \
			./src/game/server/state/init.c \
			./src/game/server/state/bomb.c \
			./src/game/server/state/players.c \
			./src/game/server/state/wall.c \
			./src/game/server/state/bonus.c \
			./src/game/server/requests/join.c \
			./src/game/server/requests/requests.c \
			./src/game/server/requests/entities.c \


SRC 	= 	$(BASE_SRC)\
			src/main.c

TEST_SRC =	$(BASE_SRC)\
			src/engine/test.c

NAME	=	Bomberman

OBJ		=	$(SRC:.c=.o)

TEST_OBJ =	$(TEST_SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror -g -D_GNU_SOURCE

LDFLAGS	=	`sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lpthread -lm

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
