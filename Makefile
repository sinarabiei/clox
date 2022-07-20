CC := gcc
CFLAGS := -Wall

SRC := src/chunk.o src/memory.o src/debug.o src/value.o src/line.o
TESTS := tests/line.o tests/chunk.o

clox: src/main.o $(SRC)
	$(CC) -o clox src/main.o $(SRC) $(CFLAGS)
src/main.o: src/main.c
	$(CC) -c -o src/main.o src/main.c $(CFLAGS)

src/chunk.o: src/chunk.c
	$(CC) -c -o src/chunk.o src/chunk.c $(CFLAGS)

src/memory.o: src/memory.c
	$(CC) -c -o src/memory.o src/memory.c $(CFLAGS)

src/debug.o: src/debug.c
	$(CC) -c -o src/debug.o src/debug.c $(CFLAGS)

src/value.o: src/value.c
	$(CC) -c -o src/value.o src/value.c $(CFLAGS)

src/line.o: src/line.c
	$(CC) -c -o src/line.o src/line.c $(CFLAGS)

.PHONY: run
run: clox
	./clox

runtests: tests/runtests.o $(SRC) $(TESTS)
	$(CC) -o runtests tests/runtests.o $(SRC) $(TESTS) $(CFLAGS)
tests/runtests.o: tests/runtests.c
	$(CC) -c -o tests/runtests.o tests/runtests.c $(CFLAGS)

tests/line.o: tests/line.c
	$(CC) -c -o tests/line.o tests/line.c $(CFLAGS)

tests/chunk.o: tests/chunk.c
	$(CC) -c -o tests/chunk.o tests/chunk.c $(CFLAGS)

.PHONY: test
test: runtests
	./runtests

.PHONY: clean
clean:
	rm clox runtests *~ src/main.o src/*~ $(SRC) tests/runtests.o tests/*~ $(TESTS)
