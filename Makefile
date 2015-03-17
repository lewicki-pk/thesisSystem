# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

# define all programs
PROGRAMS = receiver
SOURCES = source/${PROGRAMS:=.cpp}


all: ${PROGRAMS} move

${PROGRAMS}: ${SOURCES}
	g++ ${CCFLAGS} -Wall -Iinclude -lrf24-bcm source/$@.cpp -o $@

clean:
	rm -rf bin/$(PROGRAMS)

move: ${PROGRAMS}
	mv $(PROGRAMS) ./bin
