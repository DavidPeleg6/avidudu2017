a.out: main.o Server.o FileReader.o
	g++ main.o Server.o FileReader.o -o ../exe/server.out
FileReader.o: FileReader.cpp headersS/FileReader.h
	g++ -c FileReader.cpp
Server.o: Server.cpp headersS/Server.h
	g++ -c Server.cpp
main.o: main.cpp
	g++ -c main.cpp
