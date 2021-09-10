CC = g++
CFLAGS = -std=c++17 -Wall -g
OBJECTS = main.o InputParser.o

all: link clean

link: ${OBJECTS}
	${CC} ${OBJECTS} -o WolframBeta

%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o