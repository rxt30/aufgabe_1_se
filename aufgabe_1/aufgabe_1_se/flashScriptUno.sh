if [ "$#" -eq 1 ]
then
    avr-gcc -g -Os -mmcu=atmega328p $1/*.c sharedLibs/sharedFunctions.c -o $1/program.elf
    avr-objcopy -O ihex -j .text -j .data $1/program.elf $1/program.hex
    avrdude -u -v -p atmega328p -c arduino -P /dev/ttyS4 -b 115200 -U flash:w:$1/program.hex:i
	rm $1/program.elf
	rm $1/program.hex
else
    echo "Insufficient number of arguments"
fi