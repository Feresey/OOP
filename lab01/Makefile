.PHONY :  all, clean
TARGET  = $(shell basename $(shell pwd))
SRC     = $(wildcard *.cpp)
HDR     = $(wildcard *.hpp)
CXX     = zapcc++ -std=c++1z
CFLAGS  = -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3 -Weffc++ #-lm -pg -DDMALLOC -DDMALLOC_FUNC_CHECK -I/usr/local/include -L/usr/local/lib
LDFLAGS = -lm

all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $^


main.o: main.cpp $(HDR) 
	$(CXX) $(CFLAGS) -c main.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
