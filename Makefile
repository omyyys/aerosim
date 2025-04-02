CC=gcc
CPPFLAGS=-Wall -Wextra -std=c++17
CPPLIBS=-L./raylib-macos/lib -Wl,-rpath ./raylib-macos/lib/ -lraylib -lm

all: aerosim

aerosim: src/main.cpp 
	$(CC) $(CPPFLAGS) -o aerosim src/main.cpp $(CPPLIBS)
