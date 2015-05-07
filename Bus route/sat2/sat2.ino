/*
  The circuit:
 * LCD RS pin to digital pin 6
 * LCD Enable pin to digital pin 7
 * LCD D4 pin to digital pin 8
 * LCD D5 pin to digital pin 9
 * LCD D6 pin to digital pin 10
 * LCD D7 pin to digital pin 11
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
  
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
SoftwareSerial mySerial(2, 3); // RX, TX
unsigned char temp;

void setup()  
{
  lcd.begin(16, 2);
  mySerial.begin(9600);
  delay(1000);
  mySerial.write("+++");
  while(mySerial.read() != 'K');
  mySerial.write("atid1234\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atmy4\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atdl1\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atwr\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atcn\n\r");
  while(mySerial.read() != 'K');
}

void loop()           // run over and over
{  
  char arr[50];
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Bus Stop 2");
  delay(1000);
  while(mySerial.read() != 'B');
  for(int i=0; i < 24; i++)       
  {
    while(!mySerial.available());
    arr[i] = mySerial.read();
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print('B');
  for(int i=0 ; i < 15; i++)   lcd.print(arr[i]);   
  lcd.setCursor(3, 1);
  for(int i=15; i < 24; i++)   lcd.print(arr[i]);  
  do{
      while(!mySerial.available());
      temp = mySerial.read();
    } while(temp != '$' && temp != '%');
  if(temp == '$')
    {
      delay(5000);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Bus Arrived"); 
      mySerial.write("Bus Arrived*");
      delay(3000);
    }
   else if(temp == '%')
    {
      delay(5000);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Bus Arrived"); 
      mySerial.write("Bus Arrived!");
      delay(3000);
     }
   delay(100);
}
