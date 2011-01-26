CXX = g++

# SOURCES
PRODUCTION_CODE = main.cpp
TEST_CODE = tests.cpp

P_OBJECTS = $(PRODUCTION_CODE:.cpp=.o)
T_OBJECTS = $(TEST_CODE:.cpp=.o)

# gcc flags + frameworks
CFLAGS = -c -Wall
GLUTFLAGS = -framework GLUT -framework OpenGL
COCOAFLAGS = -framework Cocoa

# Application + Test Application
EXECUTABLE = graph
TEST_EXECUTABLE = test

# Include CppUnit
CPPFLAGS = -I$$CPPUTEST_HOME/include
LIB = $(CPPUTEST_HOME)lib/libCppUTest.a

all: $(EXECUTABLE) $(TEST_EXECUTABLE)

$(EXECUTABLE): $(P_OBJECTS)
	$(CXX) $(P_OBJECTS) -o $@

$(TEST_EXECUTABLE): $(T_OBJECTS)
	$(CXX) $(T_OBJECTS) -o $@ $(LIB)

$(P_OBJECTS).o:
	$(CXX) $(CFLAGS) $< -o $@

$(T_OBJECTS).o:
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE) $(TEST_EXECUTABLE)

run:
	./$(TEST_EXECUTABLE)