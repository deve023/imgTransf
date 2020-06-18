CXX = g++
CXXFLAGS = -Wall -pedantic -g

all: tp1

Token.o: Token.cpp Token.h Complejo.h Lista.h Cola.h Pila.h
	$(CXX) $(CXXFLAGS) -c Token.cpp

Complejo.o: Complejo.cpp Complejo.h Cola.h
	$(CXX) $(CXXFLAGS) -c Complejo.cpp

Pixel.o: Pixel.cpp Pixel.h Complejo.h
	$(CXX) $(CXXFLAGS) -c Pixel.cpp

Imagen.o: Imagen.cpp Imagen.h Pixel.h Complejo.h Cola.h Token.h
	$(CXX) $(CXXFLAGS) -c Imagen.cpp

Comando.o: Comando.cpp Comando.h
	$(CXX) $(CXXFLAGS) -c Comando.cpp

main.o: main.cpp Imagen.h Comando.h Pila.h Cola.h Token.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tp1: main.o Pixel.o Imagen.o Complejo.o Comando.o Token.o 
	$(CXX) $(CXXFLAGS) $^ -o tp1

clean:
	rm *.o
