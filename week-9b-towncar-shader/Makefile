CC = g++
CFLAGS = -c -Wall -g -std=c++11
LDFLAGS = -g -lglfw -lGLEW -framework OpenGL -lm

SOURCES = $(wildcard ./src/*.cpp ./src/*/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
MAIN = ./src/main.cpp
EXECUTABLE = ./main

.PHONY: all bin clean

all: bin

bin: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(OBJECTS)
	-rm $(EXECUTABLE)
