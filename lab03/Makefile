.PHONY :  all, clean
TARGET := $(shell basename $(shell pwd))
SRC    := $(wildcard *.cpp)
HDR    := $(wildcard *.hpp)
CXX    := g++
CFLAGS := -fsanitize=address -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3


all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

main.o: main.cpp $(HDR)
	$(CXX) $(CFLAGS) -c main.cpp

%.o: %.cpp $(HDR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm
