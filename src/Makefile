cc := avr-gcc 
copier:= avr-objcopy
flash := avrdude
flashOptions := -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex
options := -Os -DF_CPU=16000000UL -mmcu=atmega328p

default:
	$(cc) $(options) main.c uart.c dio.c adc.c lcd.c i2c.c timer.c pwm.c motor.c eeprom.c rtc.c helpers.c -o main.o
	$(cc) -o main.bin main.o 
	$(copier) -O ihex -R .eeprom main.bin main.hex 
	sudo $(flash) $(flashOptions)
	rm main.bin main.hex main.o

testADC:
	$(cc) $(options) adcTest.c adc.c uart.c -o main.o
	$(cc) -o main.bin main.o 
	$(copier) -O ihex -R .eeprom main.bin main.hex 
	sudo $(flash) $(flashOptions)
	rm main.bin main.hex main.o

testLCD:
	$(cc) $(options) uart.c lcd.c i2c.c lcdTest.c -o main.o
	$(cc) -o main.bin main.o 
	$(copier) -O ihex -R .eeprom main.bin main.hex 
	sudo $(flash) $(flashOptions)
	rm main.bin main.hex main.o

testTimer:
	$(cc) $(options) uart.c dio.c timer.c pwm.c timerTest.c -o main.o
	$(cc) -o main.bin main.o 
	$(copier) -O ihex -R .eeprom main.bin main.hex 
	sudo $(flash) $(flashOptions)
	rm main.bin main.hex main.o

testEeprom:
	$(cc) $(options) uart.c eeprom.c eepromTest.c -o main.o
	$(cc) -o main.bin main.o 
	$(copier) -O ihex -R .eeprom main.bin main.hex 
	sudo $(flash) $(flashOptions)
	rm main.bin main.hex main.o

testRTC:
	$(cc) $(options) uart.c rtc.c i2c.c helpers.c rtcTest.c -o main.o
	$(cc) -o main.bin main.o 
	$(copier) -O ihex -R .eeprom main.bin main.hex 
	sudo $(flash) $(flashOptions)
	rm main.bin main.hex main.o
