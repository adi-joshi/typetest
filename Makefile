CC=gcc
CFLAGS=
OBJECTS=typing_test.o
EXEC=typetest

${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} -o ${EXEC}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
