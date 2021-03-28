// oh not correct there shoud be some voltage level in the rx tx connection
// the nano is 5volt and the wt32-eth01 is 3.3volt

// ftdi serial monitor loses track/connection with wt32-eth01
// a nano uno serial to usb shows all the serial data on serial monitor
//
int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
}

void loop() {
  
  if (Serial.available() > 0) {            // send data only when you receive data:
    
    incomingByte = Serial.read();         // read the incoming byte from WT32-ETH01 TX0 RX0 :

    Serial.write(incomingByte);          // send incomming on RX TX via usb to serial monitor
  }
}
