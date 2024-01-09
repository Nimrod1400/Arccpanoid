TARGET = arcpp
TESTS_TARGET = arcpp_tests

CC = clang++-15
CFLAGS = -Wall -Wextra -O3 -pedantic -std=c++20 -lraylib -lyaml-cpp

PREF_SRC = ./src/
PREF_OBJ = ./obj/

PREF_TESTS_SRC = ./tests/
PREF_TESTS_OBJ = ./obj/tests/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.so, $(SRC))

TESTS_SRC = $(wildcard $(PREF_TESTS_SRC)*.cpp)
TESTS_OBJ = $(patsubst $(PREF_TESTS_SRC)%.cpp, $(PREF_TESTS_OBJ)%.so, $(TESTS_SRC))

$(PREF_OBJ)%.so : $(PREF_SRC)%.cpp
	$(CC) -c $< -o $@

all: $(TARGET)
$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

$(PREF_TESTS_OBJ)%.so : $(PREF_TESTS_SRC)%.cpp
	$(CC) -c $< -o $@

tests: $(TESTS_TARGET)
$(TESTS_TARGET) : $(TESTS_OBJ)
	$(CC) $(TESTS_OBJ) $(filter-out $(PREF_OBJ)main.so, $(OBJ)) -o $(TESTS_TARGET) $(CFLAGS) -lboost_unit_test_framework

clean :
	rm $(TARGET) $(TEST_TARGET) $(PREF_OBJ)*.so $(PREF_TESTS_OBJ)*.so
