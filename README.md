# WT32-ETH01 LAN 8720 RJ45 wired  Wireless-tag

WT32-ETH01 +/-7 Dollar ESP32 with Ethernet jack https://www.google.com/search?q=WT32-ETH01

-----------
# struggling to find some info / examples for WT32-ETH01 Wireless-tag

if you know some examples / usefull info 

share it ?   https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/discussions
------------
my ftdi programmer is not always succesfull with programming = used ESP32 Dev Module settings

### strange another same FTDI programmer is doing better with programming

### but still some garbage char with FTDI serial monitor on https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32-eth01-wired-google.com-test.ino test, not with nano/uno serial to usb  monitor

FTDI as serial monitor is also no good losing connection no data => uno nano as serial to usb monitor shows all the serial data

program = powerup with gpio0 pull to ground better with 10k resistor

wt32-eth01 run powerup = gpio0 no connection to ground


--------------
programming mode = better put a resistor in IO0 to ground?

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32prog.jpg">

programming mode = better put a resistor in IO0 to ground?
--------------



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


-------------
Less Wires => power over ethernet cable is not included on WT32-ETH01, but you can D.I.Y. Do It YourSelf

10 Euro PoE power over ethernet injector https://www.google.com/search?q=PoE+injector

3 Euro PoE power over ethernet splitter 5v  https://www.google.com/search?q=PoE+splitter+5v


