RED="\033[0;31m"
GREEN="\033[0;32m"
BOLDGREEN="\033[1;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"	
PURPLE="\[\033[0;35m\]"	
CYAN="\[\033[0;36m\]"	
WHITE="\033[0;37m"
BOLDWHITE="\033[1;37m"
GREY="\[\033[0;97m\]"
PS_CLEAR="\033[0m"
SCREEN_ESC="\[\033k\033\134\]"

CXX = g++

# dirs
OBJDIR = .

# platform dependent
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
  # do something Linux-y
endif
ifeq ($(UNAME), Solaris)
  # do something Solaris-y
endif
ifeq ($(UNAME), Darwin) 
  # do something Apple-y
endif


# SOURCES
PRODUCTION_CODE = main.cpp
#TEST_CODE = $(wildcard tests/*.cpp)
#TEST_CODE = tests/TestHelper.cpp tests/TestMain.cpp tests/TestRunner.cpp
TEST_CODE_HELPER = tests/TestHelper.cpp
TEST_CODE_MAIN = tests/TestMain.cpp
TEST_CODE_RUNNER = tests/TestRunner.cpp

P_OBJECTS = $(PRODUCTION_CODE:.cpp=.o)
T_OBJECTS_HELPER = $(TEST_CODE_HELPER:.cpp=.o)
T_OBJECTS_MAIN = $(TEST_CODE_MAIN:.cpp=.o)
T_OBJECTS_RUNNER = $(TEST_CODE_RUNNER:.cpp=.o)

#PRODUCTION_OBJECTS = $(PRODUCTION_CODE:.cpp=.o)
#TEST_OBJECTS = $(addprefix $(OBJDIR)/,$(TEST_CODE:.cpp=.o))
#TEST_OBJECTS =  $(TEST_CODE:.cpp=.o)

# home
PROJECT_ROOT=.

# gcc flags + frameworks
CFLAGS = -g -O2 -c -Wall -I$(PROJECT_ROOT)/include -I$(PROJECTROOT)/tests -I$$CPPUTEST_HOME/include
GLUTFLAGS = -framework GLUT -framework OpenGL
COCOAFLAGS = -framework Cocoa

# Application + Test Application
EXECUTABLE = graph
TEST_EXECUTABLE = test

# Include CppUnit
CPPFLAGS = -g -O2 -c -Wall -I$(PROJECT_ROOT)/include -I$(PROJECTROOT)/tests -I$$CPPUTEST_HOME/include
LIB = $(CPPUTEST_HOME)lib/libCppUTest.a

all: clean $(TEST_EXECUTABLE) cleanup

production: $(EXECUTABLE) cleanup

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXECUTABLE): $(P_OBJECTS)
	@echo $(YELLOW)"========================================"
	@echo "Linking the target $@"
	@echo "========================================"
	@echo $(PS_CLEAR)
	@$(CXX) $(P_OBJECTS) -o $@
	@echo "$(CXX) *.o -o $@"
	@echo $(YELLOW)
	@echo -- Link finished --
	@echo $(PS_CLEAR)

$(TEST_EXECUTABLE): $(T_OBJECTS_RUNNER) $(T_OBJECTS_MAIN) $(T_OBJECTS_HELPER) 
	@echo $(YELLOW)"========================================"
	@echo "Linking the target $@"
	@echo "========================================"
	@echo $(PS_CLEAR)
	@$(CXX) $(T_OBJECTS_RUNNER) $(T_OBJECTS_MAIN) $(T_OBJECTS_HELPER) -o $@ $(LIB)
	@echo "$(CXX) *.o -o $@"
	@echo $(YELLOW)
	@echo -- Link finished --
	@echo $(PS_CLEAR)

.cpp.o:
	@echo $(GREEN)"========================================"$(PS_CLEAR)
	@echo "Compiling "$(BOLDWHITE)"$<"
	@echo $(GREEN)"========================================"
	@echo $(PS_CLEAR)
	@$(CXX) $(CPPFLAGS) $< -o $@
	@echo "$(CXX) $<"
	@echo

cleanup:
	@rm -rf *.o tests/*.o

clean: cleanup
	@rm -rf $(EXECUTABLE) $(TEST_EXECUTABLE)

run:
	./$(TEST_EXECUTABLE)

log:
	git log '--pretty=format:%ad %s (%cn)' --date=short > CHANGELOG
	cat CHANGELOG

  # LOADED SUITE test
  # CompactorTest
  #     test_ignores_xmlns                                                    PASS
  #     test_makes_value_empty_Array_if_nil                                   PASS
  #     test_pivots_list_keys_item_and_converts_to_Array_not_already_an_Array PASS
  #     test_pivots_list_keys_item_and_makes_empty_Array_if_nil               PASS
  #     test_pivots_list_keys_on_item                                         PASS
  #     test_pivots_on_root                                                   PASS
  #     test_traverses_list_values_and_compacts                               PASS
  # ExpanderTest
  #     test_converts_Key_of_Range_to_FromKey_ToKey                           PASS
  #     test_expands_Array_values_to_n_key_values                             PASS
  #     test_expands_keys_with_and_Array_values_to_n_key_values               PASS
  #     test_ignores_empty_Array_values                                       PASS
  #     test_ignores_non_String_keys                                          PASS
  #     test_leaves_params_as_is_by_default                                   PASS
  # SlopTest
  #     test_camalize                                                         PASS
  #     test_gets_sloppy                                                      PASS
  #     test_honors_keys_already_camalized                                    PASS
  #     test_raise_InvalidKey_if_key_not_found                                PASS
  # ==============================================================================
  #   pass: 17,  fail: 0,  error: 0
  #   total: 17 tests with 13 assertions in 0.002219 seconds
  # ==============================================================================

