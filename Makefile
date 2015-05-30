CXX=g++-4.9
# The recommended compiler flags for the Raspberry Pi
ifeq ($(TARGET),travis)
CFLAGS=-DUNIT_TEST
LDFLAGS=-lstdc++
else
ifeq ($(TARGET),linux)
CFLAGS =
LDFLAGS=-lstdc++ -lrf24-bcm
else
CFLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s
LDFLAGS=-lstdc++ -lrf24-bcm
endif
endif

CFLAGS+=-Ofast
# Add all warnings
CFLAGS+=-Wall
# Add c++11 support
CFLAGS+=-std=c++11 --coverage

# define all programs
PROGRAMS = thesisSystem
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

INCLUDE=-Iinc
INCLUDE+=-Icommon


all: ${PROGRAMS} move

${PROGRAMS}: ${OBJ_FILES}
	${CXX} ${CFLAGS} ${INCLUDE} $^ -o $@ ${LDFLAGS}

clean:
	rm -rf bin/$(PROGRAMS)
	rm -rf obj/*.o obj/*.gcda obj/*.gcno coverage.info
clean_all: clean
	make clean -C UT
	make clean -C arduino
	tags_clear

move: ${PROGRAMS}
	mv $(PROGRAMS) ./bin/

obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

