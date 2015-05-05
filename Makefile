CC=g++-4.9
# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s
# Add all warnings
CCFLAGS+=-Wall
# Add c++11 support
CCFLAGS+=-std=c++11

# define all programs
PROGRAMS = receiver
SOURCES = src/${PROGRAMS:=.cpp}

INCLUDE=-Iinc
INCLUDE+=-Icommon

LDFLAGS=-lrf24-bcm


all: ${PROGRAMS} move

${PROGRAMS}: ${SOURCES}
	${CC} ${CCFLAGS} ${INCLUDE} $^ -o $@

clean:
	rm -rf bin/$(PROGRAMS)

move: ${PROGRAMS}
	mv $(PROGRAMS) ./bin
