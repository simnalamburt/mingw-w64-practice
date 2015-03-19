all: main.c
	gcc $< -lopengl32 -lgdi32
