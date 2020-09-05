CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin/main
MAIN	:= main
INCLUDE	:= include
LIB		:= lib
TESTBIN := bin/test
TEST	:= test

ifeq ($(OS), Windows_NT)
	LIBRARIES	:= 
else
	LIBRARIES	:= -lpthread
endif

EXECUTABLE	:= main
TESTEXE		:= test

MAINSOURCES		:= \
	main/main.cpp	\
	main/**/*.cpp

TESTSOURCES		:= \
	test/test-main.cpp \
	main/**/*.cpp \
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
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(MAIN) -I$(TEST) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
	-rm $(TESTBIN)/*
