CC = g++
STANDART = -std=c++17

all: main

main: clean
	$(CC) $(STANDART) main.cpp -o main
	./main

test: clean
	$(CC) $(STANDART) test.cpp -o test
	./test

clean:
	rm -rf test main