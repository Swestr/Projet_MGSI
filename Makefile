CC=g++
LIBFLAGS=-lGL -lGLU -lglut -lGLEW -lm
EXEC=particules
SRC= main.cpp Vent.cpp Particules.cpp Particule.cpp perlin.cpp Obstacle.cpp Sphere.cpp Parallelepipede.cpp shader.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) -o $(EXEC) $(SRC) $(LIBFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)

re: clean $(EXEC)
