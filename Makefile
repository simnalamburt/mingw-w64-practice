all: main.c
	g++ $< -lopengl32 -lgdi32
