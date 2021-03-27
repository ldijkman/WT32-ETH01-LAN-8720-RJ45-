# WT32-ETH01-LAN-8720-RJ45-
WT32-ETH01 LAN 8720 RJ45 wired  Wireless-tag
-----------
# struggling to find some info / examples for WT32-ETH01 Wireless-tag
------------
my ftdi programmer is not always succesfull with programming = used ESP32 Dev Module settings

### strange another same FTDI programmer is doing better with programming

### but still some garbage char with FTDI serial monitor on https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32-eth01-wired-google.com-test.ino test, not with nano/uno serial to usb  monitor

FTDI as serial monitor is also no good losing connection no data => uno nano as serial to usb monitor shows all the serial data

program = powerup with gpio0 pull to ground better with 10k resistor

wt32-eth01 run powerup = gpio0 no connection to ground

serial monitor with ftdi no good
--------------
programming mode = better put a resistor in IO0 to ground?

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/wt32prog.jpg">

programming mode = better put a resistor in IO0 to ground?
--------------
<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32-ETH01.jpeg">

https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32_ETH01_V2.schematic.pdf


<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32_ETH01.png">

<img src="https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/WT32_ETH01_pinout.png">
