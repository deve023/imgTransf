CXX = g++
CXXFLAGS = -Wall -pedantic -g

all: tp1

token.o: token.cpp token.h Complejo.h lista.h cola.h 
	$(CXX) $(CXXFLAGS) -c token.cpp

Complejo.o: Complejo.cpp Complejo.h cola.h
	$(CXX) $(CXXFLAGS) -c Complejo.cpp

Pixel.o: Pixel.cpp Pixel.h Complejo.h
	$(CXX) $(CXXFLAGS) -c Pixel.cpp

Imagen.o: Imagen.cpp Imagen.h Pixel.h Complejo.h cola.h token.h
	$(CXX) $(CXXFLAGS) -c Imagen.cpp

comando.o: comando.cpp comando.h
	$(CXX) $(CXXFLAGS) -c comando.cpp

main.o: main.cpp Imagen.h comando.h pila.h cola.h token.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tp1: main.o Pixel.o Imagen.o Complejo.o comando.o token.o 
	$(CXX) $(CXXFLAGS) $^ -o tp1

clean:
	rm *.o
