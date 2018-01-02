a.out: compileAll
	g++ *.o -o ../exe/server.out -lpthread
	rm -f *.o

compileAll: headersS/*.h ./*.cpp
	g++ -Iinclude/ -c ./*.cpp
run:
	./a.out
