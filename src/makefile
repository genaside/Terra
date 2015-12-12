 
# 
SOURCES = main.cpp Terra.cpp FrameRateCap.cpp TitleScreen.cpp Timer.cpp MainGame.cpp
HEADERS =
OBJECTS = main.o
NAME = ../Terra

COMPILER = g++

COMPILER_FLAGS = -std=c++11 -g -Wall

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua



final: 
	$(COMPILER) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SOURCES) -o $(NAME)

clean:	
	-rm -f $(OBJECTS)