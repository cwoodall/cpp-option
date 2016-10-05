CPPFLAGS += -I../include -I$(CPPUTEST_HOME)/include -g -fprofile-arcs -ftest-coverage
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h --coverage
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt -lstdc++ -g -fprofile-arcs -ftest-coverage

SRC_DIR = ../include
C_FILES =
CPP_FILES =
TEST_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(C_FILES:.c=.o))
OBJ_CPP_FILES = $(notdir $(CPP_FILES:.cpp=.o))
OBJ_TEST_FILES = $(notdir $(TEST_FILES:.cpp=.o))

test: $(OBJ_TEST_FILES) $(OBJ_FILES) $(OBJ_CPP_FILES)
	$(CXX) -g -o test $(OBJ_TEST_FILES) $(OBJ_CPP_FILES) $(OBJ_FILES) $(LD_LIBRARIES)
	./test

%.o: $(SRC_DIR)/%.c
	$(CC) -Wall --std=c99 -g $(CPPFLAGS) -c -o $@ $<

%.o: $(SRC_DIR)/%.cpp
	$(CXX) -Wall --std=c++11 -g $(CPPFLAGS)  $(CXXFLAGS)-c -o $@ $<

%.o: %.cpp
	$(CXX) --std=c++11 -g $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.gcno *.gcda test

cleanAndRun: clean test
