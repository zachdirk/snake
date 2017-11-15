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
OBJECTS=$(BUILD)/main.obj $(BUILD)/SnakeGame.obj $(BUILD)/Snake.obj $(BUILD)/Grid.obj

ALL: $(OBJECTS)
	$(LINKER) $(LIBS) $(OBJECTS) $(LKARGS) 

$(BUILD)/main.obj: $(BUILD)/SnakeGame.obj $(INCLUDEDIR)/SnakeGame.h $(BUILD)/Grid.obj $(SRC)/main.cpp 
	$(COMPILER) $(CLARGS) $(SRC)/main.cpp 

$(BUILD)/SnakeGame.obj: $(BUILD)/Grid.obj $(BUILD)/Snake.obj $(INCLUDEDIR)/Grid.h $(INCLUDEDIR)/Snake.h $(SRC)/SnakeGame.cpp
	$(COMPILER) $(CLARGS) $(SRC)/SnakeGame.cpp

$(BUILD)/Snake.obj: $(SRC)/Snake.cpp
	$(COMPILER) $(CLARGS) $(SRC)/Snake.cpp

$(BUILD)/Grid.obj: $(SRC)/Grid.cpp
	$(COMPILER) $(CLARGS) $(SRC)/Grid.cpp

CLEAN:
	del /Q bin\*
	del /Q build\*