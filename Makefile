GREY   = $ \033[30m
RED    = $ \033[31m
GREEN  = $ \033[32m
YELLOW = $ \033[33m
BLUE   = $ \033[34m
PURPLE = $ \033[35m
CYAN   = $ \033[36m
WHITE  = $ \033[37m

END    = $ \e[0m
BOLD   = $ \e[1m
UNDER  = $ \e[4m
REV    = $ \e[7m

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
