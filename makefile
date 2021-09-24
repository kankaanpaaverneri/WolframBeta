CC = g++
CFLAGS = -std=c++17 -Wall -g
OBJECTS = main.o InputParser.o Util.o
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
	./$^ 7*12^4-72+8*4+5^6
	./$^ 21xy^2*3+-31--2
	./$^ -x^2+x--12
	./$^ +-xy^2--20*2
	./$^ -+x*200+1
	./$^ x*12-1
	./$^ +-[2+2*[12-5]+200]-3*-+x
	./$^ [+-12--x][-3+-1]-2
	
