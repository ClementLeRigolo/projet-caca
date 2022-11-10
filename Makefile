##
## EPITECH PROJECT, 2022
## rpg_masterclass
## File description:
## Makefile
##

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

IGREY   = $ \x1b[40m
IRED    = $ \x1b[41m
IGREEN  = $ \x1b[42m
IYELLOW = $ \x1b[43m
IBLUE   = $ \x1b[44m
IPURPLE = $ \x1b[45m
ICYAN   = $ \x1b[46m
IWHITE  = $ \x1b[47m

SRC := $(shell find $(SOURCEDIR) -name '*.cpp')

FLAGS = -g -I include -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lm

NAME = RPG_MASTERCLASS

OBJ =	$(SRC:.cpp=.o)

%.o: %.cpp
	@g++ -o $@ -c $< $(FLAGS)
	@printf "\t${PURPLE}%s\n${END}"  $<

all: $(NAME)

$(NAME): header $(OBJ) done
	@g++ -o $(NAME) $(OBJ) $(FLAGS)

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
