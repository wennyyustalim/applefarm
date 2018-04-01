all: src/kijang.cpp
	g++ -o kijang src/kijang.cpp -framework OpenGL -framework GLUT

clean:
	$(RM) kijang