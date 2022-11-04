SRC := $(shell find $(SOURCEDIR) -name '*.cpp')

FLAGS = -g -I include -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lm

NAME =	RPG_MASTERCLASS

all:
	g++ $(SRC) -o $(NAME) $(FLAGS)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all, clean, re
