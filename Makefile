CC=g++
LIBFLAGS=-lGL -lGLU -lglut
EXEC=particules
SRC=main.cpp Particules.cpp Particule.cpp perlin.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) -o $(EXEC) $(SRC) $(LIBFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)

re: clean $(EXEC)
