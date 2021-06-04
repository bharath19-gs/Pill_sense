#include"RTClib.h"
#include<EEPROM.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define button 7

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);



RTC_DS1307 rtc;

//current_address is used to store the last changed or updated address when store push button is pressed
int Number_of_pill = 0;




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //Initialize Display
  display.begin();

  // you can change the contrast around to adapt the display for the best viewing!
  display.setContrast(57);

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  //assigning input functionality to button variables
  pinMode(button, INPUT_PULLUP);
  EEPROM.write(1023,Number_of_pill);
}



void loop() 
{
  // the size of the EEPROM is 1024(0-1023) bytes so making sure the storage isn't getting full.1023 is used to dynamically store the current_address.
 if(Number_of_pill < 50)
 {   
  //When button is pressed or it goes LOW, state variable updates and starts pointing to next address value
  
  if (digitalRead(button) == LOW)
  {
    int start = millis();
    DateTime t;
    Number_of_pill = EEPROM.read(1023);
     store_time(Number_of_pill);
    display_data(t);
    EEPROM.write(1023,Number_of_pill+1);
    if(millis()-start >=  5)
    {
      print_data(EEPROM.read(1023));
    } 
    
    
    delay(250);
  }
 }

   
}




/*
 * This function prints on the serial monitor for showing stored data in the memory, 
 * we can make the same data to be printed on the lcd being used.
*/

void print_data(uint32_t val)
{
  int date;
  int mon;
  int yr; 
  int hr;
  int mn;
  int S_no=1;
  Serial.println("The list of pills taken till now:");
  for(int i=0;i<val;i++)
  {
  // Extracting information received from EEPROM and storing it in Time t variable
    
  // Reading values stored in EEPROM on given address location
  byte add1 = EEPROM.read((i * 3));
  byte add2 = EEPROM.read((i * 3) + 1);
  byte add3 = EEPROM.read((i * 3) + 2);

  date = add2 >> 3;
  mon = B00001111 & add1;
  yr = 2020 + (add1 >> 4);

  hr = ((B111 & add2) << 2) | (add3 >> 6);
  mn = add3 & B111111;

//display on the serial monitor
  {
    Serial.print(S_no);
    Serial.print(") ");
    Serial.print(date);
    Serial.print('/');
    Serial.print(mn);
    Serial.print('/');
    Serial.print(yr);
    Serial.print(", ");
    Serial.print(hr);
    Serial.print(':');
    Serial.print(mn);    
  }
    S_no++;
    delay(1000);
 }
  
}




/*
 * This function is used to store the data into the memory storage(EEPROM) by reducing the values into bits so the memory consumed in less.
*/
void store_time(int address)
{
  // Declaring structure variable Time t
  DateTime t;
  // Receiving time values from RTC module and storing it in structure variable t

  // Dividing and storing the values in three bytes
  byte add1 = ((t.year() - 2020) << 4) + t.month();
  byte add2 = (t.day() << 3) + (t.hour() >> 2);
  byte add3 = (t.hour() << 6) + t.minute();

  // Writing those three bytes in EEPROM
  EEPROM.write((address * 3), add1);
  EEPROM.write((address * 3) + 1, add2);
  EEPROM.write((address * 3) + 2, add3);

}



/*
 * This function prints on the lcd(DISPLAY)..
*/


void display_data(DateTime T)
{
  /*
   * 1.display relay time.
   * 2.display the number of pills++ taken and number of pills there.
   * 3.display the last time and date the pills taken.
   * 4.write "hold for 5secs to preview of the all the pills taken till now."
  */
  
}
