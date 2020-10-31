CC = g++
BUILD = .toejam/build/
LIBS =   
DEPS = src/ribbit.h 

ribbit: $(BUILD)ribbit.o
	$(CC) -o bin/ribbit $^ $(LIBS)

$(BUILD)ribbit.o: src/ribbit.cpp $(DEPS)
	$(CC) -c src/ribbit.cpp -o $@

.PHONY: clean

clean:
	rm .toejam/build/*.o
	rm -rf bin
