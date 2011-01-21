CC=g++
CFLAGS=-c -Wall
GLUTFLAGS=-framework GLUT -framework OpenGL
COCOAFLAGS=-framework Cocoa
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Graph

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(GLUTFLAGS) $(COCOAFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

run:
	./$(EXECUTABLE)