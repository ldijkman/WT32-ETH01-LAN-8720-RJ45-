# WT32-ETH01 LAN 8720 RJ45 ESP32 wired  Wireless-tag

-WT32-ETH01 +/-7 Dollar 
- ESP32 with Ethernet jack https://www.google.com/search?q=WT32-ETH01

- Buy it from manufacturer
- 1 Piece or a Gazillion
http://www.wireless-tag.com/portfolio/wt32-eth01/
-----------

Struggling to find some info / Arduino IDE examples for WT32-ETH01 Wireless-tag

if you know some examples / usefull info 

share it ?   https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/discussions

------------
my ftdi programmer is not always succesfull with programming = i used board 'ESP32 Dev Module' settings

strange another same FTDI programmer is doing better with programming https://www.google.com/search?q=FTDI+programmer

now using a ESP8266-01 female 2row 8pin programmer with ch340 chip https://www.google.com/search?q=esp8266-01+programmer+ch340G



program = wt32-eth01 powerup with gpio0 pull to ground (better with 10k resistor?)

run / monitor == wt32-eth01 powerup = gpio0 NO connection to ground


--------------
programming mode = better put a resistor in IO0 to ground?

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32prog.jpg">

programming mode = better put a resistor in IO0 to ground?

If someone programs gpio0 as output and high when connected to ground blows the gpio0 pin

So thats why its better to use a resistor on gpio0 pull to ground

--------------

program WT32-ETH01 with ESP-01 / ESP8266-01 programmer https://www.google.com/search?q=esp8266-01+programmer+ch340G

- red      3.3 Volt
- purple   ground
- white    TX0
- grey     RX0
- Connect programmer Gpio0 to WT32-ETH01 Gpio0 
- powerup with switch to PROG program == programming mode
- powerup with switch to UART monitor == run / monitor mode
--------

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/esp8266-01-ch340g-programmer.jpg" width="30%" height="30%"><img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/eps8266-01-pinout.png">

program WT32-ETH01 with ESP-01 / ESP8266-01 programmer https://www.google.com/search?q=esp8266-01+programmer+ch340G

- lefttop---------3.3 Volt
- leftbottom-----RX0
- righttop-------TX0
- rightbottom-----ground
- Connect programmer Gpio0 to WT32-ETH01 Gpio0 
- powerup with switch to PROG program == programming mode
- powerup with switch to UART monitor == run / monitor mode

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32-eth01-esp01-programmer.png" width="50%" height="50%"><img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/eps8266-01-pinout.png">

- usb to esp-01 adapter programmer
- Hmmm, looks like no resistor switch gpio0 to ground  
- https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/USB%20to%20ESP-01%20Adapter%20schematic.pdf


--------------------

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32_ETH01.png">

poor documentation, why no mention of what is analog pins in pinout

chip used wt32-s1 http://www.wireless-tag.com/portfolio/wt32-s1/

more i/o info wt32-s1 https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32-S1-DataSheet-V1.1.pdf

schematic https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32_ETH01_V2.schematic.pdf

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32-ETH01_pinout.jpg">



# Arduino IDE WT32-ETH01 ino files  on  this github
---------
https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32-eth01-wired-google.com-test.ino

https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32-ETH01-wired-webserver-dhcp.ino

https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32-ETH01-i2c-BME280-DS3231.ino

https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/not-tested-code/sdcard-i2c-bme280-ds3231-wt32-eth01.ino

-----------
## Install the ESP32 Board in Arduino IDE in less than 1 minute (Win, Mac, Linux)
- https://youtu.be/mBaS3YnqDaU
- - https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
- - - https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
-
- Board settings i used
<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/Board_Settings.png">

-------------
Less Wires => power over ethernet cable is not included on WT32-ETH01, but you can D.I.Y. 
- Do It YourSelf

10 Euro PoE power over ethernet injector https://www.google.com/search?q=PoE+injector

3 Euro PoE power over ethernet splitter 5v  https://www.google.com/search?q=PoE+splitter+5v


--------

things to try

example i2c connection == Done & tested 

test example howto connect SD card reader/writer

test a rotary encoder, maybe use the 3 input only pins? (or maybe make a nano i2c rotary encoder)

- get some more i/o
- i2c pcf8574 i/o expander 
  https://youtu.be/GqKjo0lKVVk

-----------------

replace the arduino mega with ethernetshield http://arduino.tk:8888/HC.htm?file=27-3-21.CSV

the mega2560 with uno/mega ethernetshield W5100 did not work with cheap longer ethernet cables

the WT32-ETH01 works with cheap longer ethernet cables


---------------

## A Penny for Sharing My Thoughts?
www.paypal.me/LDijkman


