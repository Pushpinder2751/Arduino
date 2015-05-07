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

unsigned char temp[15];
int i=0;

void sat1()
{
  Serial.write("+++");
  while(Serial.read() != 'K');
  Serial.println("atdl3");
  while(Serial.read() != 'K');
  Serial.println("atwr");
  while(Serial.read() != 'K');
  Serial.println("atcn");
  while(Serial.read() != 'K'); 
}

void sat2()
{
  Serial.write("+++");
  while(Serial.read() != 'K');
  Serial.println("atdl4");
  while(Serial.read() != 'K');
  Serial.println("atwr");
  while(Serial.read() != 'K');
  Serial.println("atcn");
  while(Serial.read() != 'K'); 
}

void Init()
{
  Serial.write("+++");
  while(Serial.read() != 'K');
  Serial.println("atid1234");
  while(Serial.read() != 'K');
  Serial.println("atmy2");
  while(Serial.read() != 'K');
  Serial.println("atdl1");
  while(Serial.read() != 'K');
  Serial.println("atwr");
  while(Serial.read() != 'K');
  Serial.println("atcn");
  while(Serial.read() != 'K'); 
}

void rfid()
{
  delay(1000);
  digitalWrite(4, HIGH);  // activate the RFID reader
  delay(1000);
  while(!mySerial.available());
  for(i=0;i<12;i++)
  {  
    while(!mySerial.available());
      temp[i]=mySerial.read();     
  }
  digitalWrite(4, LOW); // deactivate the RFID reader for a moment so it will not flood
  delay(1000);
}
void setup()  
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
  pinMode(4,OUTPUT);   // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  digitalWrite(4, HIGH); 
}

void loop() // run over and over
{  
  char rec;
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
  Init();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Bus Transport ");
  delay(1000);
  rfid();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Bus Started  ");
  
  for(i=0;i<12;i++)
  { 
   Serial.write(temp[i]);
  }
  do
  {
     rec = Serial.read();
  }while(rec != 'q' && rec != 'z');
  
  if(rec == 'q')
  { 
     Serial.write("ROUTE1 from Station1 to Station2$\n\r");              
     delay(5000);     // wait for a bit 
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("     ROUTE1     ");
     lcd.setCursor(0, 1);
     lcd.print(" Station 1 to 2 "); 
     sat1();
     rfid();
     delay(500); 
     if(temp[10] == 0x39)
       {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Bus Arrived   ");
          lcd.setCursor(0, 1);
          lcd.print("  On Station 1  "); 
          Serial.write("Bus Arrived on Station1$\n\r");
          while(Serial.read() != '*');
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.setCursor(0, 0);
          lcd.print("  Bus Arrived   ");
          lcd.setCursor(0, 1);
          lcd.print("  Next Station2 "); 
          Serial.write("Next Station is Station2.");
          Serial.write("done\n\r");
          delay(5000);delay(5000);
        }
     sat2();
     rfid();
     if(temp[10] == 0x39)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  Bus Arrived   ");
          lcd.setCursor(0, 1);
          lcd.print("  On Station 2  "); 
          Serial.write("Bus Arrived on station2%\n\r");
          delay(5000);
        }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Bus Stoped   ");
      Serial.write("done\n\r");
      delay(2000);
  }
  
  else if(rec == 'z')
  { 
    Serial.write("ROUTE2 from station2 to station1&\n\r");
    delay(5000);                       // wait for a bit 
    lcd.clear();
    lcd.setCursor(0, 0);
     lcd.print("     ROUTE2     ");
     lcd.setCursor(0, 1);
     lcd.print(" Station 2 to 1 "); 
    sat2();
    rfid();
    if(temp[10] == 0x36)
    {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("  Bus Arrived   ");
       lcd.setCursor(0, 1);
       lcd.print("  On Station 2  "); 
       Serial.write("Bus Arrived on station 2%\n\r");
       delay(5000);
       while(Serial.read() != '*');
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("  Bus Arrived   ");
       lcd.setCursor(0, 1);
       lcd.print(" Next station1  "); 
       Serial.write("Next station is station1.");
       Serial.write("done\n\r");
       delay(5000);
       sat1();  
       rfid();  
       delay(500); 
       if(temp[10] == 0x36)
       {
         Serial.write("Bus Arrived on  station1%\n\r");
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("  Bus Arrived   ");
         lcd.setCursor(0, 1);
         lcd.print("  On Station 1  "); 
         delay(5000);
       }
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("  Bus Stoped   ");
       delay(2000);
//       Serial.write("done\n\r");
    }
  }
}
