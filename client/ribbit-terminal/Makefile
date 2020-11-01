CC = g++
BUILD = .toejam/build/
LIBS =   
DEPS = src/ribbit-terminal.h 

ribbit-terminal: $(BUILD)ribbit-terminal.o
	$(CC) -o bin/ribbit-terminal $^ $(LIBS)

$(BUILD)ribbit-terminal.o: src/ribbit-terminal.cpp $(DEPS)
	$(CC) -c src/ribbit-terminal.cpp -o $@

.PHONY: clean

clean:
	rm .toejam/build/*.o
	rm -rf bin
