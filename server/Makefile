CC = g++
BUILD = .toejam/build/
LIBS =   
DEPS = src/ribbit-server.h 

ribbit-server: $(BUILD)ribbit-server.o
	$(CC) -o bin/ribbit-server $^ $(LIBS)

$(BUILD)ribbit-server.o: src/ribbit-server.cpp $(DEPS)
	$(CC) -c src/ribbit-server.cpp -o $@

.PHONY: clean

clean:
	rm .toejam/build/*.o
	rm -rf bin
