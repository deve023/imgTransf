CXX = g++
CXXFLAGS = -Wall -pedantic -g

all: tp1

token.o: token.cpp token.h Complejo.h lista.h
	$(CXX) $(CXXFLAGS) -c token.cpp

cola.o: cola.cpp cola.h token.h lista.h
	$(CXX) $(CXXFLAGS) -c cola.cpp

pila.o: pila.cpp pila.h token.h lista.h
	$(CXX) $(CXXFLAGS) -c pila.cpp

Complejo.o: Complejo.cpp Complejo.h
	$(CXX) $(CXXFLAGS) -c Complejo.cpp

Pixel.o: Pixel.cpp Pixel.h Complejo.h
	$(CXX) $(CXXFLAGS) -c Pixel.cpp

Imagen.o: Imagen.cpp Imagen.h Pixel.h Complejo.h
	$(CXX) $(CXXFLAGS) -c Imagen.cpp

comando.o: comando.cpp comando.h
	$(CXX) $(CXXFLAGS) -c comando.cpp

main.o: main.cpp Imagen.h comando.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tp1: main.o Pixel.o Imagen.o Complejo.o comando.o token.o cola.o pila.o
	$(CXX) $(CXXFLAGS) $^ -o tp1

clean:
	rm *.o
