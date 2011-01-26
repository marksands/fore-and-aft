CXX = g++

# SOURCES
PRODUCTION_CODE = main.cpp
TEST_CODE_HELPER = TestHelper.cpp
TEST_CODE_MAIN = TestMain.cpp
TEST_CODE_RUNNER = TestRunner.cpp

P_OBJECTS = $(PRODUCTION_CODE:.cpp=.o)
T_OBJECTS_HELPER = $(TEST_CODE_HELPER:.cpp=.o)
T_OBJECTS_MAIN = $(TEST_CODE_MAIN:.cpp=.o)
T_OBJECTS_RUNNER = $(TEST_CODE_RUNNER:.cpp=.o)

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
	@echo "============="
	@echo "Linking the target $@"
	@echo "============="
	$(CXX) $(P_OBJECTS) -o $@
	@echo -- Link finished --

$(TEST_EXECUTABLE): $(T_OBJECTS_RUNNER) $(T_OBJECTS_HELPER) $(T_OBJECTS_MAIN)
	@echo "============="
	@echo "Linking the target $@"
	@echo "============="
	$(CXX) $(T_OBJECTS_RUNNER) -o $@ $(LIB)
	@echo -- Link finished --

$(P_OBJECTS).o:
	@echo "============="
	@echo "Compiling $<"
	$(CXX) $(CFLAGS) $< -o $@

$(T_OBJECTS_HELPER).o:
	@echo "============="
	@echo "Compiling $<"
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(T_OBJECTS_MAIN).o:
	@echo "============="
	@echo "Compiling $<"
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(T_OBJECTS_RUNNER).o:
	@echo "============="
	@echo "Compiling $<"
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE) $(TEST_EXECUTABLE)

run:
	./$(TEST_EXECUTABLE)