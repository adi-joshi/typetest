CC=gcc
CFLAGS=
OBJECTS=src/main.o src/quotelist.o src/test.o src/stats.o
EXEC=typetest

${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} -o ${EXEC} -lncurses

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
