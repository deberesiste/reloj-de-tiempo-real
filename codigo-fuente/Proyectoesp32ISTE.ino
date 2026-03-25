#include <WiFi.h>
#include "time.h"
#include <Wire.h>

#define OLED                      // comment this line if your are not using an OLED Screen 

#ifdef OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C for 128x32 / 128x64 or 0X3D for others
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif
/*
Hardware OLED Screen Wiring in the video.
ESP32  ------ OLED SS1306/1315
 GND   ------  GND
 G12   ------  VDD
 G27   ------  SDA
 G14   ------  SCL   
*/
#define sda_pin 27              // Set your SDA Pin on ESP32
#define scl_pin 14               // Set your SCL Pin on ESP32
#define oled_power_pin 12        // Set your POWER VDD Pin on ESP32

const char* ssid       = "ECUABET";      // Set the SSID of your Wifi Network
const char* password   = "Ecuabet2025@";      // Set the password of your Wifi Network

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;         // Set the GMT shift (3600 seconds = 1 hour) i.e. Colombia is -18000, (GMT-5)
const int   daylightOffset_sec = 0;

struct tm timeinfo;               // Time Structure Definition

void setup(){
  Wire.begin(sda_pin,scl_pin);        // initialize Wire or i2C Serial Interface
  Serial.begin(115200);             // initialize serial transmission for debugging
  pinMode(26,OUTPUT);
  pinMode(25,OUTPUT);
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("WIFI CONNECTED");
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  Serial.println("WIFI DISCONNECTED");

#ifdef OLED
    pinMode(oled_power_pin,OUTPUT);
    digitalWrite(oled_power_pin,HIGH);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }
    display.setTextColor(SSD1306_WHITE);
#endif   
}

void loop(){
  #ifdef OLED
    ShowDataOLED();
  #endif  
    delay(1000);
    printLocalTime();
    /*Primera Forma*/
    int hour = timeinfo.tm_hour;
    int min = timeinfo.tm_min;
    int sec = timeinfo.tm_sec;
    if(hour == 19){
      if(min == 35){
        digitalWrite(26,HIGH);
        digitalWrite(25,LOW);
      }else{
        digitalWrite(26,LOW);
        digitalWrite(25,LOW);
      }
    }
    /*Segunda Forma*/
    // char buffer[10];
    // strftime(buffer,10,"%H:%M",&timeinfo);
    // String data = String(buffer);
    // if (data.equals("23:12")){
    //     digitalWrite(26,HIGH);
    //     digitalWrite(25,LOW);
    // }else{
    //     digitalWrite(26,LOW);
    //     digitalWrite(25,LOW);
    // }
}

/*****************Function Get the local Time and Print it on Serial Monitor******************/
void printLocalTime()
{
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

/*Function To show the data in a OLED Screen */
#ifdef OLED
void ShowDataOLED(){
    display.clearDisplay(); // Clear Display Before Updating
    /****************Show on OLED the Day Of the Week***********************/
    display.setTextSize(2,2); // Draw 2X-scale text
    display.setCursor(0, 0);
    String DayOfWeek = "";
    switch (timeinfo.tm_wday) {
    case 0: DayOfWeek = "Sunday";break;
    case 1: DayOfWeek = "Monday";break;
    case 2: DayOfWeek = "tuesday";break;
    case 3: DayOfWeek = "Wednesday";break;
    case 4: DayOfWeek = "Thursday";break;
    case 5: DayOfWeek = "Friday";break;
    case 6: DayOfWeek = "Saturday";break;
    }
    display.print(DayOfWeek);

        /****************Show on OLED the Hour Minute Second Format (hh:mm:ss)***********************/
    display.setTextSize(2,3);
    display.setCursor(0, 30);
          char buffer[10];
          strftime (buffer,10,"%H:%M:%S",&timeinfo);
          //strftime (buffer,10,"%H:%M:%S",&timeinfo);
          String data = String(buffer);
          DisplayCenter(data);
    //display.print(&timeinfo,"%H:%M:%S");

/****************Show on OLED the Year Month Day Format (YY:MM:DD)***********************/
          char buffer1[10];
          strftime (buffer1,10,"%y/%m/%d",&timeinfo);
          String data1 = String(buffer1);
          display.setTextSize(2,2);
          display.setCursor(32, 48);
          display.print(data1);

    display.display();      // Load Everything on OLED Screen
}
#endif

#ifdef OLED
void DisplayCenter(String text) {
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  display.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);
  int16_t X0 = (SCREEN_WIDTH - width) / 2;
  int16_t Y0 = (SCREEN_HEIGHT - height) / 2;
  int rectangleMargin = 3;
  display.drawRoundRect(X0-rectangleMargin, Y0-rectangleMargin, width+rectangleMargin, height+rectangleMargin, 2, SSD1306_WHITE);
  // display on horizontal and vertical center
  display.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  display.println(text); // text to display
}
#endif
