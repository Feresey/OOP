.PHONY :  all, clean
TARGET := ../lab05
SRC    := $(wildcard ../*.cpp)
HDR    := $(wildcard ../*.hpp ../*.h)
CXX    := g++
CFLAGS := -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3\
          -Weffc++ -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
          -Wconversion -Wsign-conversion -Wunreachable-code -pg#-fsanitize=address #-fprofile-arcs -ftest-coverage  

all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:../%.cpp=%.o)

main.o: ../main.cpp $(HDR)
	$(CXX) $(CFLAGS) -c ../main.cpp

%.o: ../%.cpp $(HDR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(SRC:../%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm
