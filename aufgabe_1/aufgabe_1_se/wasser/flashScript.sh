avr-gcc -g -Os -mmcu=atmega328p wasser.c pumpe.c ../sharedLibs/sharedFunctions.c -o wasser.elf
avr-objcopy -O ihex -j .text -j .data wasser.elf wasser.hex
avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -U flash:w:wasser.hex
