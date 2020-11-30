if [ "$#" -eq 1 ]
then
    avr-gcc -g -Os -mmcu=atmega328p $1 -o $1.elf
    avr-objcopy -O ihex -j .text -j .data $1.elf $1.hex
    avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -U flash:w:$1.hex
else
    echo "Insufficient number of arguments"
fi
