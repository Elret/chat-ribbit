CC = g++
BUILD = .toejam/build/
LIBS = 
DEPS = src/ribbit.h src/server.h 

ribbit: $(BUILD)ribbit.o $(BUILD)server.o
	$(CC) -o bin/ribbit $^ $(LIBS)

$(BUILD)ribbit.o: src/ribbit.cpp $(DEPS)
	$(CC) -c src/ribbit.cpp -o $@

$(BUILD)server.o: src/server.cpp $(DEPS)
	$(CC) -c src/server.cpp -o $@

.PHONY: clean

clean:
	rm .toejam/build/*.o
	rm -rf bin
