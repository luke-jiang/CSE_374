# Makefile for rational number calculator
# CSE 374, 17wi, HP

calc: Calc.o Parser.o Rational.o Scanner.o
	g++ -Wall -g -std=c++11 -o calc Calc.o Parser.o Rational.o Scanner.o

Rational.o: Rational.cpp Rational.h
	g++ -Wall -g -std=c++11 -c Rational.cpp

Scanner.o: Scanner.cpp Scanner.h Token.h
	g++ -Wall -g -std=c++11 -c Scanner.cpp

Parser.o: Parser.cpp Parser.h Rational.h Scanner.h Token.h
	g++ -Wall -g -std=c++11 -c Parser.cpp

Calc.o: Calc.cpp Parser.h Rational.h Scanner.h
	g++ -Wall -g -std=c++11 -c Calc.cpp

clean:
	rm -f *.o *~ calc
