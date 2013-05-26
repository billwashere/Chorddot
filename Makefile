CC=g++
EXE=chorddot

all:
	$(CC) chorddot.cpp -o $(EXE)

clean:
	rm $(EXE)
