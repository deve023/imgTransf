CXX = g++
CXXFLAGS = -Wall -pedantic -g

all: imgTransf
Token.o: ./src/Token/Token.cpp ./src/Token/Token.h ./src/Complejo/Complejo.h ./src/Estructuras/Lista.h ./src/Estructuras/Cola.h ./src/Estructuras/Pila.h
	$(CXX) $(CXXFLAGS) -c ./src/Token/Token.cpp

Complejo.o: ./src/Complejo/Complejo.cpp ./src/Complejo/Complejo.h ./src/Estructuras/Cola.h
	$(CXX) $(CXXFLAGS) -c ./src/Complejo/Complejo.cpp

Pixel.o: ./src/Imagen/Pixel.cpp ./src/Imagen/Pixel.h ./src/Complejo/Complejo.h
	$(CXX) $(CXXFLAGS) -c ./src/Imagen/Pixel.cpp

Imagen.o: ./src/Imagen/Imagen.cpp ./src/Imagen/Imagen.h ./src/Imagen/Pixel.h ./src/Complejo/Complejo.h ./src/Estructuras/Cola.h ./src/Token/Token.h
	$(CXX) $(CXXFLAGS) -c ./src/Imagen/Imagen.cpp

Comando.o: ./src/Comando/Comando.cpp ./src/Comando/Comando.h
	$(CXX) $(CXXFLAGS) -c ./src/Comando/Comando.cpp

main.o: ./src/main.cpp ./src/Imagen/Imagen.h ./src/Comando/Comando.h ./src/Estructuras/Pila.h ./src/Estructuras/Cola.h ./src/Token/Token.h
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp

imgTransf: main.o Pixel.o Imagen.o Complejo.o Comando.o Token.o 
	$(CXX) $(CXXFLAGS) $^ -o imgTransf; \
	rm *.o

clean:
	rm *.o
