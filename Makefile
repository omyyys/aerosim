CC=gcc
CPPFLAGS=-Wall -Wextra -std=c++11
CPPLIBS=-L./raylib/lib -Wl,-rpath ./raylib/lib/ -lraylib -lm

all: aerosim

aerosim: src/main.cpp 
	$(CC) $(CPPFLAGS) -o aerosim src/main.cpp $(CPPLIBS)
