CC = g++
CFLAGS = -std=c++17 -Wall -g
OBJECTS = main.o InputParser.o Reduce.o Util.o
BIN = WolframBeta
UTIL_PROGRAMS = valgrind

all: link clean

link: ${OBJECTS}
	${CC} ${OBJECTS} -o ${BIN} -lm

%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o

tests: ${BIN}
	${UTIL_PROGRAMS} ./$^ 2+21.5*3-1
	${UTIL_PROGRAMS} ./$^ 123x+12-23
	${UTIL_PROGRAMS} ./$^ 7*12^4-72+8*4+5^6
	${UTIL_PROGRAMS} ./$^ 21xy^2*3+-31--2
	${UTIL_PROGRAMS} ./$^ -x^2+x--12
	${UTIL_PROGRAMS} ./$^ +-xy^2--20*2
	${UTIL_PROGRAMS} ./$^ -+x*200+1
	${UTIL_PROGRAMS} ./$^ x*12-1
	${UTIL_PROGRAMS} ./$^ +-[2+2*[12-5-[-2]]+200]-3*-+x
	${UTIL_PROGRAMS} ./$^ [+-12--x][-3+-1]-2
	${UTIL_PROGRAMS} ./$^ -[+2]+12*2-[--2]
	${UTIL_PROGRAMS} ./$^ 12-[a-[a-[2a+10]]]
	${UTIL_PROGRAMS} ./$^ 2-[-2]
	
