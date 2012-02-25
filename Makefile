CC         := g++
CFLAGS     := -c -std=c++0x -Wall -I /usr/include/eigen3 -O3 -static
LDFLAGS    := -lboost_program_options
SOURCES    := src/main.cc src/physics.cc src/numerics.cc src/date.cc src/geometry.cc
OBJECTS    := $(SOURCES:.cc=.o)
EXECUTABLE := twilight

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf lib/*.o
	rm -rf src/*.o
	rm -rf build/$(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
