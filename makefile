driver: main.o arrayStack.o linkedStack.o node.o
	g++ main.o arrayStack.o linkedStack.o node.o -o driver

main.o: main.cpp linkedStack.h arrayStack.h stack.h
	g++ -c main.cpp

arrayStack.o: arrayStack.cpp arrayStack.h stack.h
	g++ -c arrayStack.cpp

linkedStack.o: linkedStack.cpp linkedStack.h node.h stack.h
	g++ -c linkedStack.cpp

node.o: node.cpp node.h
	g++ -c node.cpp

clean:
	rm -f *.o driver
