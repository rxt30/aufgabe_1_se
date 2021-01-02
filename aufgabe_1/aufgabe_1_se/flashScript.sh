if [ "$#" -eq 1 ]
then
    avr-gcc -g -Os -mmcu=atmega328p $1/*.c sharedLibs/sharedFunctions.c -o program.elf
    avr-objcopy -O ihex -j .text -j .data program.elf program.hex
    avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -U flash:w:program.hex
else
    echo "Insufficient number of arguments"
fi
