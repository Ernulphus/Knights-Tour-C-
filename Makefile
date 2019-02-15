CXXFLAGS=-std=c++11

main: main.o
	g++ $(CXXFLAGS) -o main main.o

main.o: main.cpp

clean:
	rm main.o
