CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
TEST	:= test

ifeq ($(OS), Windows_NT)
	LIBRARIES	:= 
	FixPath = $(subst /,\,$1)
	Run = $(call FixPath,$1).exe
else
	LIBRARIES	:= -lpthread
	FixPath = $1
	Run = ./$1
endif

EXECUTABLE	:= main
TESTEXE		:= test

MAINSOURCES		:= \
	$(SRC)/main.cpp	\
	$(SRC)/**/*.cpp

TESTSOURCES		:= \
	$(TEST)/test-main.cpp \
	$(SRC)/**/*.cpp \
	$(TEST)/**/*.cpp


build: $(BIN)/$(EXECUTABLE)

run: build
	$(call Run,$(BIN)/$(EXECUTABLE))

test: $(BIN)/$(TESTEXE)
	$(call Run,$(BIN)/$(TESTEXE))

$(BIN)/$(EXECUTABLE): $(MAINSOURCES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(SRC) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(TESTEXE): $(TESTSOURCES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(SRC) -I$(TEST) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm -f $(BIN)/*
