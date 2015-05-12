CXX=g++-4.9

#GTEST_DIR = /home/pi/gtest-1.6.0
GTEST_DIR = /home/lewiatan/gtest-1.6.0

# Where to find user code.
#USER_DIR = ../src

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -std=c++11 -fPIC

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -DUNIT_TEST -I../inc/ -I../common/ --coverage

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = SitemapGeneratorTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : UnitTests

SitemapGenerator.o : ../src/SitemapGenerator.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@ 

SitemapGeneratorTest.o : src/SitemapGeneratorTest.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR)/include -c src/SitemapGeneratorTest.cpp

UnitTests : SitemapGenerator.o SitemapGeneratorTest.o $(GTEST_DIR)/make/gtest_main.a ../obj/SensorNode.o ../obj/SensorDB.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR)/include $^ -o $@ -lpthread

../obj/%.o: ../src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean : 
	rm -rf *.o UnitTests;
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.info
	rm -rf ../bin/receiver
	rm -rf ../obj/*.o
