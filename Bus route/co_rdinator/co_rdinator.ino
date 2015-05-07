#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
unsigned char temp;

void bus()
{
 mySerial.write("+++");
 while(mySerial.read() != 'K');
 mySerial.write("atdl2n\r");
 while(mySerial.read() != 'K');
 mySerial.write("atwr\n\r");
 while(mySerial.read() != 'K');
 mySerial.write("atcn\n\r");
 while(mySerial.read() != 'K'); 
}

void sat1()
{
 mySerial.write("+++");
 while(mySerial.read() != 'K');
 mySerial.write("atdl3n\r");
 while(mySerial.read() != 'K');
 mySerial.write("atwr\n\r");
 while(mySerial.read() != 'K');
 mySerial.write("atcn\n\r");
 while(mySerial.read() != 'K'); 
}

void sat2()
{
 mySerial.write("+++");
 while(mySerial.read() != 'K');
 mySerial.write("atdl4n\r");
 while(mySerial.read() != 'K');
 mySerial.write("atwr\n\r");
 while(mySerial.read() != 'K');
 mySerial.write("atcn\n\r");
 while(mySerial.read() != 'K'); 
}
void Init()
{
  Serial.write("\n\rCordinator\n\r");
  mySerial.write("+++");
  while(mySerial.read() != 'K');
  mySerial.write("atid1234\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atmy1\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atdl2\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atwr\n\r");
  while(mySerial.read() != 'K');
  mySerial.write("atcn\n\r");
  while(mySerial.read() != 'K');
}
void setup()  
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Init();
  delay(1000);
}

void loop() // run over and over
{  
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(5000);
  bus();
  delay(5000);
  do{
   while(!mySerial.available());
   temp = mySerial.read();
   Serial.write(temp);
 }while(temp != '9' && temp != 'D');
 if(temp == '9')
 {
   mySerial.write('q');
   mySerial.write('q');
   mySerial.write('q');
   delay(2000);
   Serial.write("ROUTE1 from Station1 to Station2");
   delay(2000);
   sat1();
   mySerial.write("Bus will arrive in 30mins\n\r");   
   delay(5000);
   bus();
   while(mySerial.read() != '*');
   Serial.write("Bus Arrived*\n\r");
   mySerial.write("Next Station is Staion2*\n\r");
   Serial.write("Next Station is Station2*\n\r");
   delay(5000);
   sat2();
   delay(5000);
   mySerial.write("Bus will arrive in 10mins\n\r");
   Serial.write("Bus will arrive in 10mins\n\r");
   delay(2000);
 }
else if(temp == 'D')
{
   mySerial.write('z');
   mySerial.write('z');
   mySerial.write('z');
   mySerial.write('z');
   delay(1000);
   Serial.write("ROUTE2 from Station2 to Station1\n\r");
   delay(2000);
   sat2();
   mySerial.write("Bus will arrive in 30mins\n\r"); 
   delay(5000);
   bus();
   while(mySerial.read() != '!');
   Serial.write("Bus Arrived*\n\r");
   mySerial.write("Next Station is Staion1*\n\r");
   Serial.write("Next Station is Station1*\n\r");
   delay(5000);
   sat1();
   delay(5000);
   mySerial.write("Bus will arrive in 20mins\n\r");
   Serial.write("Bus will arrive in 20mins\n\r");
   delay(2000);
}
}
