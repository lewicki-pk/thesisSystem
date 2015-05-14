CXX=g++-4.9

# Where to find user code.
#USER_DIR = ../src

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -std=c++11 -fPIC --coverage

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -DUNIT_TEST -I../inc/ -I../common/ --coverage

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = SitemapGeneratorTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = include/gtest/*.h \
                include/gtest/internal/*.h

all : UnitTests

SitemapGenerator.o : ../src/SitemapGenerator.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@ 

SitemapGeneratorTest.o : src/SitemapGeneratorTest.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Iinclude -c src/SitemapGeneratorTest.cpp

UnitTests : SitemapGenerator.o SitemapGeneratorTest.o make/gtest_main.a ../obj/SensorNode.o ../obj/SensorDB.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Iinclude $^ -o $@ -lpthread

../obj/%.o: ../src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

test : all
	./UnitTests

clean : 
	rm -rf *.o UnitTests *.gcno *.gcda *.gcov *.info ../obj/*.o;
