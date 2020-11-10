CC = g++
BUILD = .toejam/build/
LIBS =   
DEPS = src/server.h 

server: $(BUILD)server.o
	$(CC) -o bin/server $^ $(LIBS)

$(BUILD)server.o: src/server.cpp $(DEPS)
	$(CC) -c src/server.cpp -o $@

.PHONY: clean

clean:
	rm .toejam/build/*.o
	rm -rf bin
