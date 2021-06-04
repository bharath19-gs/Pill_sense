#include"RTClib.h"
#include <LiquidCrystal.h>


//constants 
 const int Push_button = 7;
// for lcd 
 const int rs = 12;
 const int en = 11;
 const int d4 = 5;
 const int d5 = 4;
 const int d6 = 3;
 const int d7 = 2;


RTC_DS1307 rtc;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char daysOfWeek[7][5]={"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};


void setup () {
  Serial.begin(57600);
  pinMode(Push_button,INPUT);
  lcd.begin(16, 2); 

  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
  }
  // December 19, 2020 at 3am you would call:
  // rtc.adjust(DateTime(2020, 12, 19, 3, 0, 0));

}

void upload_data_on_cloud(DateTime data)
{
  
}
void upload_data_to_eeprom(DateTime data)
{


  if()
  upload_data_on_cloud(now);
}
display_time(DateTime data)
{
  DateTime past = data;
  lcd.setCursor(0, 0);
  lcd.print("Last pill taken at:");
  lcd.setCursor(0, 1);
  lcd.print(data.year());
  lcd.print('/');
  lcd.print(data.month());
  lcd.print('/');
  lcd.print(data.day());
  lcd.print(" (");
  lcd.print(dayOfWeek[now.dayOfTheWeek()]);
  lcd.print(") ");
  lcd.print(data.hour());
  lcd.print(':');
  lcd.print(data.minute());
  lcd.print(':');
  lcd.print(data.second());
}
void loop() 
{
  int i = 0;
  
    DateTime now = rtc.now();
    int push = digitalRead(Push_button);
    while(push == 1)
    {
      i=1;
    }
    if( push == 0 && i == 1 )// when button is pushed and released it will be considered as a toggle or  a pill taken.
    {
      now = rtc.now();
      upload_data_to_eeprom(now);
      display_time(now,i);
      i=0;
    }
    if()//check for wifi connection
    {
      
    }
    
}
