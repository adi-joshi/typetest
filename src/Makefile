CC=gcc
CFLAGS=
OBJECTS=main.o quotelist.o test.o stats.o
EXEC=typetest

${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} -o ${EXEC} -lncurses

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
