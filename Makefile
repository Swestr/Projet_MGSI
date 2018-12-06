CC=g++
LIBFLAGS=-lGL -lGLU -lglut
EXEC=particules
SRC=main.cpp Vent.cpp Particules.cpp Particule.cpp perlin.cpp Obstacle.cpp Sphere.cpp Parallelepipede.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) -o $(EXEC) $(SRC) $(LIBFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)

re: clean $(EXEC)
