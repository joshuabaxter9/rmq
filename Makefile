TARGET_CPPS := RunTests.cpp
CPP_FILES := $(filter-out $(TARGET_CPPS),$(wildcard *.cpp))
OBJ_FILES := $(CPP_FILES:.cpp=.o)

CPP_FLAGS = --std=c++20 -Wall -Werror -Wpedantic -O0 -g

all: run-tests

$(OBJ_FILES): Makefile

run-tests: $(OBJ_FILES) RunTests.o
	g++ -o $@ $^

%.o: %.cpp
	g++ -c $(CPP_FLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o run-tests *~
