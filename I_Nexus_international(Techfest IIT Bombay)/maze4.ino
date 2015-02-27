#include <EEPROM.h>    // header file for EEPROM Functions

// Obstracle Sensor
#define obsSensor  3
// Obstracle Sensor
#define obsSensor2  11
// Switch Input
#define switchPin  2

// Grid Parameters
#define north  0
#define east   1
#define south  2
#define west   3

// Left Motor Controls
# define Lp  7    // ip B
# define Ln  4    // ip A
# define El  5    
// Right Motor Controls
# define Rp  8    // ip A
# define Rn  12   // ip B
# define Er  6
// Grid Sensors // 
# define ERs  A0
# define Rs   A1
# define Ms   A2
# define Ls   A3
# define ELs  A4


      #define gripperClose 0x31    // GRIP
      #define gripperOpen  0x32    // RELEASE
      #define gripperStop  0x30    // STOP GRIPPER ACTION
      
      // gripper motor
      # define G1 9
      # define G2 10
      
#define STD_LOOP_TIME  700
int lastLoopUsefulTime = STD_LOOP_TIME;
unsigned long loopStartTime = 0;      
      
boolean gripperFlag = true;

      
boolean start_pos=true;
boolean homeStart = true;
boolean mappingComplete = false;
boolean ladder =false;
boolean state=false;
int nodeCount = 0;
int myDir = 0;
int row=0;
int column=0;
int rom=0;

byte gridMap[][8] = {0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0  };   // virtual Grid Mapping 8X8
                      
byte gridNavigation[8][8] = {  0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0  };   // navigation Map grid Bot

byte navigate[20] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,255,255,255,255};
int counter=0;
int turn=0;
int boxNo=0;
int p=0;
void setup ()
{  // put your setup code here, to run once:
  Serial.begin(9600);  // Serial @ 9600 baud
  // set motor pins to output
  pinMode (Lp, OUTPUT);
  pinMode (Ln, OUTPUT);
  pinMode (El, OUTPUT);
  pinMode (Rp, OUTPUT);
  pinMode (Rn, OUTPUT);
  pinMode (Er, OUTPUT);
  // enable H-Bridge
  
  digitalWrite (El,HIGH);
  digitalWrite (Er,HIGH);
  // set sensors pins to inputs
  pinMode (ERs, INPUT);  
  pinMode (Rs, INPUT);
  pinMode (Ms, INPUT);
  pinMode (Ls, INPUT);
  pinMode (ELs, INPUT);
  pinMode (switchPin, INPUT);
  pinMode (obsSensor, INPUT);
  
  // internally pullups are disabled in arduino firmware.
  // to use pullup, enable manually
  digitalWrite (obsSensor,HIGH);
  digitalWrite (switchPin,HIGH);
  
  pinMode (G1, OUTPUT);
  pinMode (G2, OUTPUT);

  // indication of code start
  for(int i=0; i<20; i++)
  {
    digitalWrite(13,LOW);
    delay(50);
    digitalWrite(13,HIGH);
    delay(50);
  }
  delay(2000);    // 2.5sec delay
  
  // press Switch to clear grid info // if pressed indicated with led blink
  if( !digitalRead(switchPin) )
  {
    for(int i=0; i<71; i++)
    {
      EEPROM.write(i, 0);
      digitalWrite(13,LOW);
      delay(50);
      digitalWrite(13,HIGH);
      delay(50);
    }
    Serial.println("eprom cleared");
  }
  
      // 2sec delay
    Serial.println("ready");  
  // wait for user to indicate start by momentarily triggering obstracle sensor
  while(!digitalRead(obsSensor));
  while(digitalRead(obsSensor));
  Serial.println("m here");
//EEPROM.write(64,1);  testing purposes
/*EEPROM.write(65,0);
EEPROM.write(66,0);
EEPROM.write(67,0);*/
Serial.println(EEPROM.read(65));
Serial.println(EEPROM.read(66));
Serial.println(EEPROM.read(67));
for(int i=68;i<71;i++)
{
  p=EEPROM.read(i);
  boxNo=boxNo+p;
}
}
void loop()
{
        if(EEPROM.read(64) == 0)
        {
                Serial.println("in loop");
                while(row<9)
                {
                  
                  if((row%2==0) && !homeStart)
                  {
                    
                    Serial.println("even row");
                    Serial.println(column);
                      while(column>1)
                      {
                        line1:
                        digitalWrite(13,HIGH);    // indicate start line following
                        while( (!digitalRead(ERs)) && (!digitalRead(ELs)) )
                        {  line_following();  }    // do line following
                       
                        digitalWrite(13,LOW);      // indicate stop line following

                        
                        if( (digitalRead(ELs)) && (digitalRead(Ms)) && (digitalRead(ERs)) )
                        {
                          Simplenode1:
                          column--;
                          Serial.print("row = ");
                          Serial.println(row);
                          Serial.print("column = ");
                          Serial.println(column);
                          MotorControl(1,1);
                          delay(200);
                          gridMap[row-1][column-1]=2;
                          Serial.println("SimpleNode");
                        }
                        else if( (digitalRead(ELs)) && !(digitalRead(Ms)) && (digitalRead(ERs)) )
                          {
                              Blockingnode1:
                              column--;
                              Serial.print("row = ");
                              Serial.println(row);
                              Serial.print("column = ");
                              Serial.println(column);
                           
                              MotorControl(1,1);
                              delay(200);
                              gridMap[row-1][column-1]=1;
                              Serial.println("BlockingNode");
                          }
                         else if( ((digitalRead(ELs))  &&  (digitalRead(Ms))   &&  !(digitalRead(ERs))) )  // LEFT LADDER  
                          {
                            MotorControl(1,1);
                            delay(100);
                            if( (digitalRead(ELs))  &&  (digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Simplenode1;
                            }
                            if( (digitalRead(ELs))  &&  !(digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Blockingnode1;
                            }
                            if( !(digitalRead(ELs))  &&  (digitalRead(Ms))   &&  !(digitalRead(ERs)))
                            {
                              goto line1;
                            }
                            else
                            {
                              Serial.println("Right Ladder ");
                              MotorControl(1,1);
                              delay(100);
                              digitalWrite(13,HIGH);    // indicate start line following
                              while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
                              {  line_following();  }
                              digitalWrite(13,LOW);    // indicate stop line following
                              
                               if( (digitalRead(ELs)) && (!digitalRead(Ms)) && (digitalRead(ERs)) )
                                {
                                    column--;
                                    gridMap[row-1][column-1]=1;
                                    Serial.println("BlockingNode");
                                }
                                else  
                                {
                                    column--;
                                    gridMap[row-1][column-1]=4;
                                    Serial.println("SimpleNode");
                                    while( (digitalRead(ELs)) || (digitalRead(ERs)) )    {  line_following();  }
                                }                  
                              Serial.print("row = ");
                              Serial.println(row);
                              Serial.print("column = ");
                              Serial.println(column);
                            }
                            MotorControl(1,1);
                            delay(250);
                          }
                       else if( ( !(digitalRead(ELs))  &&  (digitalRead(Ms))   &&  (digitalRead(ERs)))) //RIGHT LADDER  
                          {
                            MotorControl(1,1);
                            delay(100);
                            if( (digitalRead(ELs))  &&  (digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Simplenode1;
                            }
                            if( (digitalRead(ELs))  &&  !(digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Blockingnode1;
                            }
                            if( !(digitalRead(ELs))  &&  (digitalRead(Ms))   &&  !(digitalRead(ERs)))
                            {
                              goto line1;
                            }
                            else
                            {
                              Serial.println("Left Ladder");
                              MotorControl(1,1);
                              delay(100);
                              digitalWrite(13,HIGH);    // indicate start line following
                              while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
                              {  line_following();  }
                              digitalWrite(13,LOW);    // indicate stop line following
                              
                               if( (digitalRead(ELs)) && (!digitalRead(Ms)) && (digitalRead(ERs)) )
                                {
                                    column--;
                                    gridMap[row-1][column-1]=1;
                                    Serial.println("BlockingNode");
                                }
                                else  
                                {
                                    column--;
                                    gridMap[row-1][column-1]=3;
                                    Serial.println("SimpleNode");
                                    while( (digitalRead(ELs)) || (digitalRead(ERs)) )    {  line_following();  }
                                }                  
                              Serial.print("row = ");
                              Serial.println(row);
                              Serial.print("column = ");
                              Serial.println(column);
                            }
                            MotorControl(1,1);
                            delay(250);
                          }
                        line_following();
                      }
                      MotorControl(0,0);
                      if(row==8)
                      {
                        
                        for(int i=0;i<8;i++)
                        {
                          for(int j=0;j<8;j++)
                          {
                            Serial.print(gridMap[i][j]);
                            Serial.print("  ");
                            digitalWrite(13,HIGH); 
        
                            delay(50);
                            digitalWrite(13,LOW);
                            delay(50);
                          }
                          Serial.println();
                          Serial.println();
                        }
                        EEPROM.write(64,1);
                        rom=0;
                        for(int i=0;i<8;i++)
                        {
                          for(int j=0;j<8;j++)
                          {
                            
                            EEPROM.write(rom,gridMap[i][j]);
                            rom++;
                            digitalWrite(13,HIGH); 
        
                            delay(50);
                            digitalWrite(13,LOW);
                            delay(50);
                          }
                        }
                        while(1);
                      }
                       
                      changeRow(row,south);
                 }
                else
                    {
                      Serial.println("odd row");
                      while(column<8)
                        {
                          line:
                          if(homeStart)
                          {
                          homeStart=false;
                          row++;
                          }
                          digitalWrite(13,HIGH);    // indicate start line following
                          while( (!digitalRead(ERs)) && (!digitalRead(ELs)) )
                          {  line_following();  }    // do line following
                          
                          if( (digitalRead(ELs)) && (digitalRead(Ms)) && (digitalRead(ERs)) )
                          {
                              Simplenode:
                              column++;
                              Serial.print("row = ");
                              Serial.println(row);
                              Serial.print("column = ");
                              Serial.println(column);
                           
                            MotorControl(1,1);
                            delay(300);
                            gridMap[row-1][column-1]=2;
                            Serial.println("SimpleNode");
                          }
                          else if( (digitalRead(ELs)) && !(digitalRead(Ms)) && (digitalRead(ERs)) )
                          {
                              Blockingnode:
                              column++;
                              Serial.print("row = ");
                              Serial.println(row);
                              Serial.print("column = ");
                              Serial.println(column);
                           
                              MotorControl(1,1);
                              delay(300);
                              gridMap[row-1][column-1]=1;
                              Serial.println("BlockingNode");
                          }
                          else if( ((digitalRead(ELs))  &&  (digitalRead(Ms))   &&  !(digitalRead(ERs))) ) //LEFT LADDER  
                          {
                            MotorControl(1,1);
                            delay(100);
                            if( (digitalRead(ELs))  &&  (digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Simplenode;
                            }
                            if( (digitalRead(ELs))  &&  !(digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Blockingnode;
                            }
                            if( !(digitalRead(ELs))  &&  (digitalRead(Ms))   &&  !(digitalRead(ERs)))
                            {
                              goto line;
                            }
                            else
                              {
                                Serial.println("Left ladder");
                                if(gridMap[row-1][column-1]==2)
                                {
                                gridMap[row-1][column-1]=3;
                                }
                            
                              }
                            MotorControl(1,1);
                            delay(250);
                          }
                        else if( (!(digitalRead(ELs))  &&  (digitalRead(Ms))   &&  (digitalRead(ERs))) ) //RIGHT LADDER  
                          {
                            MotorControl(1,1);
                            delay(100);
                            if( (digitalRead(ELs))  &&  (digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Simplenode;
                            }
                            if( (digitalRead(ELs))  &&  !(digitalRead(Ms))   &&  (digitalRead(ERs)))
                            {
                              goto Blockingnode;
                            }
                            if( !(digitalRead(ELs))  &&  (digitalRead(Ms))   &&  !(digitalRead(ERs)))
                            {
                              goto line;
                            }
                            else
                              {
                                Serial.println("Right ladder");
                                if(gridMap[row-1][column-1]==2)
                                {
                                gridMap[row-1][column-1]=4;
                                }
                            
                              }
                            MotorControl(1,1);
                            delay(250);
                          }  
                          
                          
                        line_following();
                        }  
                  MotorControl(0,0);
                  Serial.print("Dir= ");
                  Serial.println(myDir);
                  changeRow(row,north);
                  }
                }
        }
        else
        {
           Serial.println("Reconstructing map");
           Serial.println();
           for (int i=0; i<8; i++)
              {
                  for (int j=0; j<8; j++)
                  {
                      Serial.print(EEPROM.read(i*8+j),DEC);
                      Serial.print("  ");
                      gridNavigation[i][j]=EEPROM.read(i*8+j),DEC;
                  }
                  Serial.println();
                  Serial.println();
              }
              Serial.println();
            homeRun(north);
            
            renew:
            Serial.println();
            if(boxNo==3)
            {
              digitalWrite(13,HIGH);    // indicate start line following
            while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
            {  line_following();  }
              MotorControl(0,0);  //when the last sensors are on white stop
            digitalWrite(13,LOW);    // indicate stop line following
            
            while ( (digitalRead(ELs)) || (digitalRead(ERs)) )	{  MotorControl(1,1);  }		// skip current node
            delay(50);  	        // Stop bot and pause
            }
            Serial.println("renewed");
            while(!digitalRead(obsSensor));
             MotorControl(0,0);
            delay(1700);
            MotorControl(1,1);
            delay(500);
            gripperControl(gripperClose);
            gripperControl(gripperStop);
            
            digitalWrite(13,HIGH);    // indicate start line following
            while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
            {  line_following();  }
              MotorControl(0,0);  //when the last sensors are on white stop
            digitalWrite(13,LOW);    // indicate stop line following
            
            MotorControl(1,1);
            delay(350);
            change_Dir (myDir, west);		//change dir from south to east
            myDir = west;
            MotorControl(0,0);
            delay(100);
            
         if(digitalRead(obsSensor) && !digitalRead(obsSensor2))
      {
        Serial.println("black");
        goto black;
      }
   int x,y,z;
   x=EEPROM.read(65),DEC;
   y=EEPROM.read(66),DEC;
   z=EEPROM.read(67),DEC;
   Serial.print("x= ");
   Serial.println(x);
   Serial.print("y= ");
   Serial.println(y);
   Serial.print("z= ");
   Serial.println(z);    
         if(x==0)
          {   
         rescueRun(0,7,west);
         Serial.println("found 0,7");
         MotorControl(1,1);
                delay(250);
         gripperControl(gripperOpen);
         gripperControl(gripperStop);       
         back_run();
         EEPROM.write(65,1);
         myDir=east;
         boxNo++;
         EEPROM.write(68,1);
         goto renew;
          }
        else if(y==0)
          {   
         rescueRun(7,7,west);
         Serial.println("found 7,7");
         MotorControl(1,1);
                delay(250);
         gripperControl(gripperOpen);
         gripperControl(gripperStop);              
         back_run();
         myDir=east;
         EEPROM.write(66,1);
         boxNo++;
         EEPROM.write(69,1);
         goto renew;
          }
         else if(z==0)
          {
            black:
            if(gridNavigation[4][3]>1)   
           { 
           Serial.println("going 4 3");  
         rescueRun(4,3,west);
         Serial.println("found 4,3");
         
           }
          else if(gridNavigation[3][3]>1)   
           {  
            Serial.println("going 3 3"); 
             rescueRun(3,3,west);
             Serial.println("found 3,3");
           }
           else if(gridNavigation[4][4]>1)   
           {   
             Serial.println("going 4,4");
             rescueRun(4,4,west);
             Serial.println("found 4,4");
           }
           else if(gridNavigation[3][4]>1)   
           {   
             Serial.println("going 3 4");
             rescueRun(3,4,west);
             Serial.println("found 3,4");
           }
           
           
         MotorControl(1,1);
                delay(550);
         gripperControl(gripperOpen);
         gripperControl(gripperStop);
         MotorControl(2,2);
         delay(350);         
         back_run();
         EEPROM.write(67,1);
         myDir=east;
         boxNo++;
         EEPROM.write(70,1);
         goto renew;
          } 
        }
}


