CC=g++
CFLAGS=-c -Wall
GLUTFLAGS=-framework GLUT -framework OpenGL
COCOAFLAGS=-framework Cocoa
SOURCES=AllTests.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Graph

CPPFLAGS = -I$$CPPUTEST_HOME/include
LIB = $(CPPUTEST_HOME)lib/libCppUTest.a

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIB)

.cpp.o: 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

run:
	./$(EXECUTABLE)