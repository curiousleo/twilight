CC=g++
CFLAGS=-c -std=c++0x -Wall -I /usr/include/eigen3 -O3 -static
LDFLAGS=-lboost_program_options
SOURCES=main.cc physics.cc numerics.cc date.cc geometry.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=twilight

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
