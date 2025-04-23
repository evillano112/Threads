CXXFLAGS= -std=c++20 -O1 -g -Wall

all: prog5
prog5: *.cpp
	$(CXX) -o $@ $(CXXFLAGS) *.cpp

