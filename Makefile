EXENAME = finalproj
OBJS = Airport.o BFS.o Traversal.o Graph.o ShortestPathFinder.o main.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

Airport.o: Airport.cpp
	$(CXX) $(CXXFLAGS) Airport.cpp

BFS.o: BFS.cpp 
	$(CXX) $(CXXFLAGS) BFS.cpp 

Traversal.o: Traversal.cpp 
	$(CXX) $(CXXFLAGS) Traversal.cpp

Graph.o: random.cpp Graph.cpp
	$(CXX) $(CXXFLAGS) Graph.cpp

ShortestPathFinder.o: ShortestPathFinder.cpp
	$(CXX) $(CXXFLAGS) ShortestPathFinder.cpp

<<<<<<< HEAD
test: output_msg cs225/catch/catchmain.cpp tests/tests.cpp Airport.cpp BFS.cpp Traversal.cpp Graph.cpp ShortestPathFinder.cpp
	$(LD) cs225/catch/catchmain.cpp tests/tests.cpp Airport.cpp BFS.cpp Traversal.cpp Graph.cpp ShortestPathFinder.cpp $(LDFLAGS) -o test

tests.o: tests/tests.cpp cs225/catch/catch.hpp Airport.h BFS.h Traversal.h Graph.h ShortestPathFinder.h
	$(CXX) $(CXXFLAGS) tests/tests.cpp
=======
test: output_msg catch/catchmain.cpp tests/tests.cpp Airport.cpp BFS.cpp Traversal.cpp Graph.cpp ShortestPathFinder.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp Airport.cpp BFS.cpp Traversal.cpp Graph.cpp ShortestPathFinder.cpp$(LDFLAGS) -o test
>>>>>>> 7b11b2addc97c39367c60002c56b4fd5e2f7b03e

clean:
	-rm -f *.o $(EXENAME) test
