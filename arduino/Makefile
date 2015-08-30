CXX=avr-g++
LD=avr-g++

INCLUDE=-I ~/include/arduino/
INCLUDE+=-I inc
INCLUDE+=-I ../common

LIBS=-L ~/lib -lm -larduino 
LD_FLAGS=-L ~/lib -lm -larduino 

MCU=-mmcu=atmega328p
CPU_SPEED=-DF_CPU=8000000L
ARDUINO_FLAGS=-DARDUINO=157 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR

CFLAGS=$(MCU) $(CPU_SPEED) -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD $(ARDUINO_FLAGS)
CFLAGS+=-std=c++11

#-Os -w -Wl,--gc-sections -ffunction-sections -fdata-sections
#TODO:this needs to be automated
PORT=/dev/ttyACM0

default: node_therm

CPP_FILES := $(filter-out src/node_%.cpp, $(wildcard src/*.cpp))
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

#node_therm rules
node_therm: node_therm.hex

node_therm.hex: node_therm.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom-0 $< $@
	avr-objcopy -O ihex -R .eeprom $< $@

node_therm.elf: $(OBJ_FILES) obj/node_therm.o
	$(LD) -w -Os -Wl,--gc-sections -mmcu=atmega328p -o $@ $^ $(LD_FLAGS)

upload_therm:
	avrdude -F -p atmega328p -c arduino -b 57600 -Uflash:w:node_therm.hex:i -P$(PORT)

#node_pir rules
node_pir: node_pir.hex

node_pir.hex: node_pir.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom-0 $< $@
	avr-objcopy -O ihex -R .eeprom $< $@

node_pir.elf: $(OBJ_FILES) obj/node_pir.o
	$(LD) -w -Os -Wl,--gc-sections -mmcu=atmega328p -o $@ $^ $(LD_FLAGS)

upload_pir:
	avrdude -F -p atmega328p -c arduino -b 57600 -Uflash:w:node_pir.hex:i -P$(PORT)

#node_smoke rules
node_smoke: node_smoke.hex

node_smoke.hex: node_smoke.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom-0 $< $@
	avr-objcopy -O ihex -R .eeprom $< $@

node_smoke.elf: $(OBJ_FILES) obj/node_smoke.o
	$(LD) -w -Os -Wl,--gc-sections -mmcu=atmega328p -o $@ $^ $(LD_FLAGS)

upload_smoke:
	avrdude -F -p atmega328p -c arduino -b 57600 -Uflash:w:node_smoke.hex:i -P$(PORT)

clean:
	@echo -n Cleaning ...
	$(shell rm *.elf 2> /dev/null)
	$(shell rm *.hex 2> /dev/null)
	$(shell rm obj/*.o 2> /dev/null)
	$(shell rm obj/*.d 2> /dev/null)
	$(shell tags_clear 2> /dev/null)
	@echo " done"

#general rule for cpp files
obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

