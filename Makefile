
SRC := $(shell find $(SOURCEDIR) -name '*.cpp')

WIN_SRC := $(shell dir /S /B *.cpp)

FLAGS = -g -I include -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lm

WIN_FLAGS = -g -I include -LC:\msys64\SFML-2.5.1\lib -I"C:\msys64\SFML-2.5.1\include" -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lm

NAME =	RPG_MASTERCLASS

all:
	g++ $(SRC) -o $(NAME) $(FLAGS)

wincmp:
	g++ $(WIN_SRC) -o $(NAME) $(WIN_FLAGS)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all, clean, re