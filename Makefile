CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: supercomputer ferate teleportare magazin

run-p1:
	./supercomputer

run-p2:
	./ferate

run-p3:
	./teleportare

run-p4:
	./magazin

supercomputer: supercomputer.cpp
	$(CC) $(CCFLAGS) -o $@ $^

ferate: ferate.cpp
	$(CC) $(CCFLAGS) -o $@ $^

teleportare: teleportare.cpp
	$(CC) $(CCFLAGS) -o $@ $^

magazin: magazin.cpp
	$(CC) $(CCFLAGS) -o $@ $^

clean:
	rm -f supercomputer ferate teleportare magazin