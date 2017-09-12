CCXX = g++
CXXFLAGS = -std=c++11 -march=native -O3

all: test_file test_read test_write

test_file: test_file.cpp
	$(CCXX) $(CXXFLAGS) $^ -o $@

test_read: test_read.cpp
	$(CCXX) $(CXXFLAGS) $^ -o $@

test_write: test_write.cpp
	$(CCXX) $(CXXFLAGS) $^ -o $@
