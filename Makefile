CCXX = g++
CXXFLAGS = -std=c++11 -march=native -O3

all: test_file

test_file: test_file.cpp
	$(CCXX) $(CXXFLAGS) $^ -o $@
