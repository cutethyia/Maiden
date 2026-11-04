CXX = g++
CXXFLAGS = -std=c++11 -O2 -I. -w -Wno-return-type
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
TARGET = xiangqi

SRCS = $(filter-out graphics.cpp, $(wildcard *.cpp))
OBJS = graphics.o $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
