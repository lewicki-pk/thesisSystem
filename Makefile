CXX=g++-4.9
# The recommended compiler flags for the Raspberry Pi
ifeq ($(TARGET),travis)
CFLAGS=
else
ifeq ($(TARGET),linux)
CFLAGS =
else
CFLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

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

LDFLAGS=-lstdc++ -lrf24-bcm


all: ${PROGRAMS} move

${PROGRAMS}: ${OBJ_FILES}
	${CC} ${CFLAGS} ${INCLUDE} $^ -o $@ ${LDFLAGS}

clean:
	rm -rf bin/$(PROGRAMS)
	rm -rf obj/*.o

move: ${PROGRAMS}
	mv $(PROGRAMS) ./bin/

obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

