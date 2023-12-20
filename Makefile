TARGET = arcpp
CC = clang++-15
CFLAGS = -Wall -Wextra -O3 -pedantic -std=c++20 -lraylib -lyaml-cpp

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.so, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

$(PREF_OBJ)%.so : $(PREF_SRC)%.cpp
	$(CC) -c $< -o $@

clean :
	rm $(TARGET) $(PREF_OBJ)*.so
