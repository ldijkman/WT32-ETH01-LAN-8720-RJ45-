// https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/blob/main/not-tested-code/sdcard-i2c-bme280-ds3231-wt32-eth01.ino
//
// https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-/raw/main/wt32prog.jpg
//
// added bit of sd card code for wt32-eth01
// prints directory listing / and size in MB of sdcard on startup
// not standard SPI pins because they are not availeble on WT32-ETH01
// SD_MISO     2
// SD_MOSI    15  // maybe use an inputonly pin for mosi
// SD_SCLK    14
// SD_CS      12
//
// dhcp webserver
// webpage shows button when pressed random data is displayed
//
// i2c BME280 temp humid bar sensor
// i2c DS3231 RTC 
// I2C_SCL 32    // WT32-ETH01 CFG    = Gpio 32      non standard i2c adress 
// I2C_SDA 33    // WT32-ETH01 485_EN = Gpio 33      non standard i2c adress

/*
    Copyright statement: This article is the original article of the CSDN blogger "Naisu_kun",
    which follows the CC 4.0 BY-SA copyright agreement.
    For reprinting, please attach the original source link and this statement.

    Original link：https://blog.csdn.net/Naisu_kun/article/details/88572129
    - Explanation of the code and other parameters: see the link above.
    - Note: Original language: Chinese (You can use the Google translator to read English, or another language)
    
    - Bits of SD card Code form: https://github.com/Xinyuan-LilyGO/LilyGO-T-ETH-POE
      https://github.com/Xinyuan-LilyGO/LilyGO-T-ETH-POE/blob/master/example/eth/eth.ino

   Copyright 2021 Dirk Luberth Dijkman Bangert 30 1619GJ Andijk The Netherlands
   https://github.com/ldijkman/WT32-ETH01-LAN-8720-RJ45-

  GNU General Public License,
  which basically means that you may freely copy, change, and distribute it,
  but you may not impose any restrictions on further distribution,
  and you must make the source code available.

  All above must be included in any redistribution
*/

#include <ETH.h> // quote to use ETH
#include <WiFi.h>
#include <WebServer.h> // Introduce corresponding libraries
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// i2c wire.h normally used i2c pins are not availeble on WT32-ETH01 so use other pins for i2c
#define I2C_SCL    32    // WT32-ETH01 CFG    = Gpio 32      non standard i2c adress 
#define I2C_SDA    33    // WT32-ETH01 485_EN = Gpio 33      non standard i2c adress

// SD-Card
// normally used pins for SPI are not availeble on WT32-ETH01
// saw this use other pins for SPI at  https://github.com/Xinyuan-LilyGO/LilyGO-T-ETH-POE/blob/master/example/eth/eth.ino
#define SD_MISO     2       // SD-Card
#define SD_MOSI    15       // SD-Card maybe use an input only pin for mosi to free an in/out pin
#define SD_SCLK    14       // SD-Card
#define SD_CS      12       // SD-Card

// DS3231 i2c RTC realtimeclock
#include "RTClib.h" // https://github.com/adafruit/RTClib
RTC_DS3231 rtc;    // download zip from above and install library from zip
// Sketch=>include library=>Add ZIP Library

// BME280 i2c temp humid milibar sensor
#include <Adafruit_Sensor.h>  // used zip from https://github.com/adafruit/Adafruit_Sensor 
#include <Adafruit_BME280.h>  // used zip from https://github.com/adafruit/Adafruit_BME280_Library
// Sketch=>include library=>Add ZIP Library
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 BME280; // I2C
bool BME280_status;


int last_second = 0, second_ = 0;          // some variables for time
unsigned long unix_epoch;

const char *monthName[12] = {"Januari", "Februari", "March", "April", "May", "Juni",
                             "Juli", "Augustus", "September", "October", "November", "December"
                            };
char dayname[7][12] = {"Sunday ", "Monday ", "Tuesday ", "Wednesday ", "Thursday ", "Friday ", "Saturday "};


#define ETH_ADDR        1
#define ETH_POWER_PIN   16  // -1             // ??? Do not use it, it can cause conflict during the software reset.
#define ETH_POWER_PIN_ALTERNATIVE 16 // 17    // ???
#define ETH_MDC_PIN    23
#define ETH_MDIO_PIN   18
#define ETH_TYPE       ETH_PHY_LAN8720
#define ETH_CLK_MODE    ETH_CLOCK_GPIO17_OUT // ETH_CLOCK_GPIO0_IN // ???

IPAddress local_ip(192, 168, 178, 112);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2 = (uint32_t)0x00000000;

// Web page
String myhtmlPage =
  String("") + "\r\n" +
  "<html>" + "\r\n" +
  "<head>" + "\r\n" +
  "    <title>ESP32 WebServer Test</title>" + "\r\n" +
  "    <script>" + "\r\n" +
  "        function getData() {" + "\r\n" +
  "            var xmlhttp;" + "\r\n" +
  "            if (window.XMLHttpRequest) {" + "\r\n" +
  "                xmlhttp = new XMLHttpRequest();" + "\r\n" +
  "            }" + "\r\n" +
  "            else {" + "\r\n" +
  "                xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");" + "\r\n" +
  "            }" + "\r\n" +
  "            xmlhttp.onreadystatechange = function() {" + "\r\n" +
  "                if (this.readyState == 4 && this.status == 200) {" + "\r\n" +
  "                    document.getElementById(\"txtRandomData\").innerHTML = this.responseText;" + "\r\n" +
  "                }" + "\r\n" +
  "            };" + "\r\n" +
  "            xmlhttp.open(\"GET\", \"getRandomData\", true); " + "\r\n" +
  "            xmlhttp.send();" + "\r\n" +
  "        }" + "\r\n" +
  "    </script>" + "\r\n" +
  "</head>" + "\r\n" +
  "<body>" + "\r\n" +
  "    <div id=\"txtRandomData\">Unkwon</div>" + "\r\n" +
  "    <input type=\"button\" value=\"random\" onclick=\"getData()\">" + "\r\n" +
  "</body>" + "\r\n" +
  "</html>";

WebServer server(80); // Declare the WebServer object

void handleRoot() // Callback
{
  server.send(200, "text/html", myhtmlPage); //!!! Note that returning to the web page requires "text / html" !!!
}

void handleAjax() // Callback
{
  String message = "Random data: ";
  message += String(random(10000)); // Get random number  // could do millis(); also
  server.send(200, "text/plain", message); // Send message back to page
}

static bool eth_connected = false;

void WiFiEvent(WiFiEvent_t event)                // strange WiFiEvent? we are wired?
{
  switch (event) {
    case SYSTEM_EVENT_ETH_START:
      Serial.println("ETH Started");
      //set eth hostname here
      ETH.setHostname("esp32-ethernet");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      Serial.println("ETH Connected");
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      Serial.print("ETH MAC: ");
      Serial.print(ETH.macAddress());
      Serial.print(", IPv4: ");
      Serial.print(ETH.localIP());
      if (ETH.fullDuplex()) {
        Serial.print(", FULL_DUPLEX");
      }
      Serial.print(", ");
      Serial.print(ETH.linkSpeed());
      Serial.println("Mbps");
      eth_connected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default:
      break;
  }
}

void setup() {
  pinMode(ETH_POWER_PIN_ALTERNATIVE, OUTPUT);
  digitalWrite(ETH_POWER_PIN_ALTERNATIVE, HIGH);
  Serial.begin(115200);
  delay(2500);          // little delay otherwise next printline is not done, because serial begin is not completed or something alike
  Serial.println("hello");

  Wire.begin(I2C_SDA, I2C_SCL);                               // start i2c on non stndard i2c pins

    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);             // SPI for SDcard
    if (!SD.begin(SD_CS)) {                                  // SDcard
        Serial.println("SDCard MOUNT FAIL");
    } else {
        uint32_t cardSize = SD.cardSize() / (1024 * 1024);
        String str = "SDCard Size: " + String(cardSize) + "MB";
        Serial.println(str);

        File root;
        root = SD.open("/");         // list files on SDcard
        printDirectory(root, 0);
    }

  WiFi.onEvent(WiFiEvent);             // WiFi ????

  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE); // Enable ETH

  //ETH.config(local_ip, gateway, subnet, dns1, dns2); // Static IP, leave without this line to get IP via DHCP

    while(!((uint32_t)ETH.localIP())){}; // Waiting for IP (leave this line group to get IP via DHCP)

  server.on("/", handleRoot);                        // Register link and callback function
  server.on("/getRandomData", HTTP_GET, handleAjax); // Request and callback function of the get method sent by ajax in the registration web page

  server.begin(); // Start server
  Serial.println("Web server started");





  if (! rtc.begin()) {
      Serial.println("Could not find RTC, i2c DS3231 realtimeclock not found");
  }


  BME280_status = BME280.begin(0x76);
  if (!BME280_status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }



  // set the time from PC to DS3231 RTC
  if (rtc.lostPower() ) {   
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // This line sets the RTC with an explicit date & time, for example to set
    //           2020 juli 24 20:15:00 you would call:
    //   rtc.adjust(DateTime(2020, 7, 24, 20, 15, 0));
  }
  
}

void loop() {

  DateTime now = rtc.now();       // DS3231 RTC RealTimeClock


  second_ = now.second();
  if (last_second != second_) {   // do next only once each new second
    
    last_second = second_;

    if (now.hour() < 10)Serial.print(" ");        // print 01 to 09 as 1 to 9
    Serial.print(now.hour());
    Serial.print(":");
    if (now.minute() < 10)Serial.print("0");      // print 1 to 9 as 01 to 09
    Serial.print(now.minute());
    Serial.print(":");
    if (now.second() < 10)Serial.print("0");      // print 1 to 9 as 01 to 09
    Serial.print(now.second());

    Serial.print("Day ");
    Serial.print(now.dayOfTheWeek());             // prints daynumber of the week, weekend sux, sunday=0, saturday=6

    Serial.print(dayname[now.dayOfTheWeek()]);
    Serial.print(now.day());
    Serial.print(" ");
    Serial.print(monthName[now.month() - 1]);
    Serial.print("   ");
    Serial.print(now.year());
    Serial.print("  ");
   


float TempCelsius;
    TempCelsius = BME280.readTemperature();                                             // get temp from BME280
    //TempCelsius = TempCelsius + CalibrationOffset;

    // Serial.print("Fahrenheit = "); Serial.print(Tf, 1);
    Serial.print(" Celsius = "); Serial.println(TempCelsius, 1);
    // https://www.google.com/search?q=3+fahrenheit+to+celsius


    Serial.print("Temperature = ");
    Serial.print(TempCelsius);
    Serial.println(" *C");
    // Convert temperature to Fahrenheit
    // Serial.print("Temperature = ");
    // Serial.print(1.8 * BME280.readTemperature() + 32);
    // Serial.println(" *F");
    Serial.print("Pressure = ");
    Serial.print(BME280.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Approx. Altitude = ");
    Serial.print(BME280.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    Serial.print("Humidity = ");
    Serial.print(BME280.readHumidity());
    Serial.println(" %");
    Serial.println();

    
  }  // end last_second not is  second_


  
  server.handleClient(); // Handling web requests from clients
}















// from arduino SD card example listfiles
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}


// A Penny for Sharing My Thoughts?
// www.paypal.me/LDijkman
