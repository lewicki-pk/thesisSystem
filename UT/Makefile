CXX=g++-4.9

# Where to find user code.
#USER_DIR = ../src

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -std=c++11 -fPIC

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -DUNIT_TEST --coverage

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = SitemapGeneratorTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = include/gtest/*.h \
                include/gtest/internal/*.h \
                include/gmock/*.h \
                include/gmock/internal/*.h

INCLUDE=-Iinclude -I../inc/ -I../common/ 

LDFLAGS=-lpthread -lstdc++

all : sources UnitTests

CPP_FILES = $(filter-out ../src/thesisSystem.cpp, $(wildcard ../src/*.cpp))
OBJ_FILES := $(addprefix ../obj/,$(notdir $(CPP_FILES:.cpp=.o)))
TEST_CPP_FILES = $(wildcard src/*.cpp)
TEST_OBJ_FILES := $(addprefix obj/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))

UnitTests : $(OBJ_FILES) $(TEST_OBJ_FILES) make/gtest_main.a make/gmock_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

test : all
	./UnitTests

clean : 
	rm -rf UnitTests *.info ../obj/* obj/* coverage.info result/

obj/%.o: src/%.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

sources : ${OBJ_FILES}

../obj/%.o: ../src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

result :
	lcov -d './obj' -d './UT/obj' --zerocounters
	lcov -d './obj' -d './UT/obj' --capture --output-file coverage.info --no-external
	genhtml -o result coverage.info

