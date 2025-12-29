CXX = g++

SRC := $(shell find . -name "*.cpp")
OBJ := $(SRC:.cpp=.o)

CXXFLAGS = -MMD -MP -std=c++20

TARGET = book

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

$(TARGET) : $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

DEP := $(shell find . -name "*.d")

clean: 
	rm -f $(OBJ) $(TARGET) $(DEP)

tidy:
	rm -f $(OBJ) $(DEP)

install: $(TARGET)
	sudo mv $(TARGET) $(BINDIR)
	rm -f $(OBJ) $(DEP)

.PHONY: clean tidy install
