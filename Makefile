objects = tools.o log.o test.o

test: $(objects)
	g++ -o test $(objects)

tools.o: ./lib/tools.h ./lib/tools.cpp
	g++ -c ./lib/tools.cpp

log.o: ./lib/log.h ./lib/log.cpp
	g++ -c ./lib/log.cpp

clean:
	rm test $(objects)

