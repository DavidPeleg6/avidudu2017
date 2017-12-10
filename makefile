

a.out: compileAll
	g++ *.o -o exe/client.out
	rm -f *.o

compileAll: headers/*.h ./*.cpp
	g++ -Iinclude/ -c ./*.cpp
run:
	./a.out
