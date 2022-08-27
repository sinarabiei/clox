CC := gcc
CFLAGS := -Wall

SRC := src/chunk.o src/memory.o src/debug.o src/value.o src/emulate.o
TESTS :=

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

src/emulate.o: src/emulate.c
	$(CC) -c -o src/emulate.o src/emulate.c $(CFLAGS)

.PHONY: run
run: clox
	./clox

runtests: tests/runtests.o $(SRC) $(TESTS)
	$(CC) -o runtests tests/runtests.o $(SRC) $(TESTS) $(CFLAGS)
tests/runtests.o: tests/runtests.c
	$(CC) -c -o tests/runtests.o tests/runtests.c $(CFLAGS)

.PHONY: test
test: runtests
	./runtests

.PHONY: clean
clean:
	rm clox runtests *~ src/main.o src/*~ $(SRC) tests/runtests.o tests/*~ $(TESTS)
