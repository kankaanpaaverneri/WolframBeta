CC = g++
CFLAGS = -std=c++17 -Wall -g
OBJECTS = main.o InputParser.o
BIN = WolframBeta

all: link clean

link: ${OBJECTS}
	${CC} ${OBJECTS} -o ${BIN}

%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o

tests: ${BIN}
	./$^ 2+21.5*3-1
	./$^ 123x+12-23
	
