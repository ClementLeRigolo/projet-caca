GREY   = $ \x1b[30m
RED    = $ \x1b[31m
GREEN  = $ \x1b[32m
YELLOW = $ \x1b[33m
BLUE   = $ \x1b[34m
PURPLE = $ \x1b[35m
CYAN   = $ \x1b[36m
WHITE  = $ \x1b[37m

END    = $ \x1b[0m
BOLD   = $ \x1b[1m
UNDER  = $ \x1b[4m
REV    = $ \x1b[7m

SRC := $(shell find $(SOURCEDIR) -name '*.cpp')

FLAGS = -g -I include -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lm

WFLAGS = -g -I include -I../lib/SFML-mingw/include -L"../lib/SFML-mingw/lib" -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lm

NAME = RPG_MASTERCLASS

OBJ =	$(SRC:.cpp=.o)

## Build standard binary file

%.o: %.cpp
	@g++ -o $@ -c $< $(FLAGS)
	@printf "\t${PURPLE}%s\n${END}"  $<

all: $(NAME)

$(NAME): header $(OBJ) done
	@g++ -o $(NAME) $(OBJ) $(FLAGS)

## Build Windows executable file

wincmp:
	x86_64-w64-mingw32-g++ $(SRC) -o $(NAME) $(WFLAGS)

## Make args

header:
	@printf "${IWHITE}               ${BOLD}${PURPLE}FILES                  \
	${END}\n"

done:
	@printf "${IGREEN}          ${BOLD}${WHITE}BUILD SUCCESSFUL            \
	${END}\n"

clean:
	@printf "${IWHITE}               ${BOLD}${GREY}CLEAN                  \
	${END}\n\n"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
