COMPILER=cl
LINKER=LINK
SRC=src
LIBS=C:/dev/SDL2/lib/x64/SDL2main.lib C:/dev/SDL2/lib/x64/SDL2.lib
INCLUDEDIR=include #careful not to overwrite the INCLUDE env. variable
INCLUDES=-IC:/dev/SDL2/include -I.\include
BUILD=build
TARGET=bin/Snake.exe
CLARGS=/EHsc /c $(INCLUDES) /Fo.\$(BUILD)\\
LKARGS=/OUT:$(TARGET) /SUBSYSTEM:CONSOLE
OBJECTS=$(BUILD)/main.obj $(BUILD)/SnakeGame.obj

ALL: $(OBJECTS)
	$(LINKER) $(LIBS) $(OBJECTS) $(LKARGS) 

$(BUILD)/main.obj: $(SRC)/main.cpp $(BUILD)/SnakeGame.obj
	$(COMPILER) $(CLARGS) $(SRC)/main.cpp 

$(BUILD)/SnakeGame.obj: $(SRC)/SnakeGame.cpp $(INCLUDEDIR)/SnakeGame.h
	$(COMPILER) $(CLARGS) $(SRC)/SnakeGame.cpp

CLEAN:
	del /Q bin\*
	del /Q build\*