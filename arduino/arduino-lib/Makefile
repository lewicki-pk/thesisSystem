CC=avr-gcc
CXX=avr-g++
AR=avr-ar
MCU=-mmcu=atmega328p
CPU_SPEED=-DF_CPU=8000000L
CFLAGS+=$(MCU) $(CPU_SPEED) -Os #-w
BOARD=arduino
LIBNAME=lib$(BOARD).a
INCDIR=~/include/$(BOARD)

#OBJECTS=pins_arduino.o wiring.o wiring_analog.o wiring_digital.o \
#        wiring_pulse.o wiring_shift.o HardwareSerial.o Print.o   \
#        Tone.o WMath.o WString.o WInterrupts.o forward.o


#//OBJECTS=CDC.o forward.o HardwareSerial0.o HardwareSerial1.o HardwareSerial2.o \
#//        HardwareSerial3.o HardwareSerial.o HID.o hooks.o IPAddress.o \
#//        new.o Print.o Stream.o Tone.o USBCore.o WInterrupts.o \
#//        wiring_analog.o wiring.o wiring_digital.o wiring_pulse.o \
#//        wiring_shift.o WMath.o WString.o 


OBJECTS=CDC.o HardwareSerial0.o HardwareSerial1.o HardwareSerial2.o \
        HardwareSerial3.o HardwareSerial.o HID.o hooks.o IPAddress.o \
        main.o new.o Print.o Stream.o Tone.o WInterrupts.o wiring_analog.o \
        wiring.o wiring_digital.o wiring_pulse.o wiring_shift.o \
        WMath.o WString.o

default: $(OBJECTS)
	$(AR) rcs $(LIBNAME) $^
	mkdir -p $(INCDIR)
	mkdir -p ~/lib/
	cp *.h $(INCDIR)/
	mv $(LIBNAME) ~/lib/
	rm *.o

%.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@ -I.

%.o : %.cpp
	$(CXX) $< $(CFLAGS) -c -o $@ -I.
