CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin/main
MAIN	:= main
INCLUDE	:= include
LIB		:= lib
TESTBIN := bin/test
TEST	:= test

LIBRARIES	:=
EXECUTABLE	:= main
TESTEXE		:= test

MAINSOURCES		:= \
	main/main.cpp	\
	main/**/*.cpp

TESTSOURCES		:= \
	main/**/*.cpp \
	test/test-main.cpp \
	test/**/*.cpp


build: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

test: $(TESTBIN)/$(TESTEXE)
	./$(TESTBIN)/$(TESTEXE)

$(BIN)/$(EXECUTABLE): $(MAINSOURCES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(MAIN) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(TESTBIN)/$(TESTEXE): $(TESTSOURCES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(MAIN) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/$(SRC)*
	-rm $(BIN)/$(TEST)*
