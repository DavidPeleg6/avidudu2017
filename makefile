

a.out: compileAll
	g++ *.o
	rm -f *.o

compileAll: headers/*.h ./*.cpp
	g++ -Iinclude/ -c ./*.cpp
run:
	./a.out
