
#define obsSensor  2
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

#define STD_LOOP_TIME  2
int lastLoopUsefulTime = STD_LOOP_TIME;
unsigned long loopStartTime = 0;

# define PotPinNo  A5
int PotDATA = 0; 

boolean gripperFlag = true;

int row=1,column=1;
int myDir = 0;
int turn=0;
int time=0;


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
  digitalWrite (El,LOW);
  digitalWrite (Er,LOW);
  
 PotDATA = analogRead(PotPinNo);    // perform analog reading on the defined pin and store value to analogPinData  
   
  int pwm = map(PotDATA,0,1023,0,255);    // map the ADC range of 0-1023 to
                                             // Motor PWM range of -127 to +127
 analogWrite( El, pwm );        // Add PWM input
 analogWrite( Er, pwm ); 
  // set sensors pins to inputs
  pinMode (ERs, INPUT);  
  pinMode (Rs, INPUT);
  pinMode (Ms, INPUT);
  pinMode (Ls, INPUT);
  pinMode (ELs, INPUT);
  pinMode (switchPin, INPUT);
  pinMode (obsSensor, INPUT);
  
  pinMode (G1, OUTPUT);
  pinMode (G2, OUTPUT);

  
  // internally pullups are disabled in arduino firmware.
  // to use pullup, enable manually
    digitalWrite (obsSensor,HIGH);
    digitalWrite (switchPin,HIGH);
  //cancelled this
  
  // indication of code start
  for(int i=0; i<20; i++)
  {
    digitalWrite(13,LOW);
    delay(50);
    digitalWrite(13,HIGH);
    delay(50);
  }
  
  // wait for user to indicate start by momentarily triggering obstracle sensor
  while(!digitalRead(obsSensor));
  while(digitalRead(obsSensor));
  delay(1000);

}


void loop ()  
{

        Serial.println("in loop");
        while(row<9)
        {
          
          if(row%2==0)
          {
            
            Serial.println("even row");
              while(column>1)
              {
                
                if( (digitalRead(ELs)) && (digitalRead(Ms)) && (digitalRead(ERs)) )
                {
                  column--;
                  Serial.print("row = ");
                  Serial.println(row);
                  Serial.print("column = ");
                  Serial.println(column);
                  MotorControl(1,1);
                  delay(200);
                }
                
                if(digitalRead(obsSensor))
                  {
                    MotorControl(0,0);
                    delay(50);
                    gripperControl(gripperClose);
                    gripperControl(gripperStop);
                    
                     digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
                    {  line_following();  }
                    MotorControl(0,0);    //when the last sensors are on white stop
                    digitalWrite(13,LOW);
                    column--;
                    MotorControl(1,1);
                    delay(200);
                    
                    deliver(row,column,2,1);
                    
                    conn();
                                         
                    myDir=north;
                    
                    row++;
                    
                    
                    digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                    {  line_following();  }    // do line following                  
                    digitalWrite(13,LOW);      // indicate stop line following
                    MotorControl(1,1);
                    delay(200);
                    if(row==9)
                       {
                         Serial.print("scan again");
                         goback(2,1,1,1);
                         row=1;
                         column=1;
                         goto odd_row;
                         
                       }
                    column=1;
                    goback(2,1,row,1);
                    Serial.print("row = ");
                    Serial.println(row);
                    Serial.print("column = ");
                    Serial.println(column);
                    goto odd_row;
                  } 
              
              line_following();
              }
              MotorControl(0,0);
             
        Serial.println("loopfinish");
             if(row==8)
             {
               goback(row,column,1,1);
               row=1;
               column=1;
               goto odd_row;
               
             }
        
              changeRow(row,south);
         }
        else
            {
              Serial.println("odd row");
              while(column<8)
                {
                  odd_row:
                  
                  if( (digitalRead(ELs)) && (digitalRead(Ms)) && (digitalRead(ERs)) )
                  {
                      column++;
                      Serial.print("row = ");
                      Serial.println(row);
                      Serial.print("column = ");
                      Serial.println(column);
                   
                    MotorControl(1,1);
                    delay(200);
                  }
                  
                  if(digitalRead(obsSensor))
                  {
                    MotorControl(0,0);
                    delay(50);
                    gripperControl(gripperClose);
                    gripperControl(gripperStop);
                   
                    digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ELs)) && (!digitalRead(ERs)) )
                    {  line_following();  }
                    MotorControl(0,0);    //when the last sensors are on white stop
                    digitalWrite(13,LOW);
                    column++;
                    MotorControl(1,1);
                    delay(200);
                   
                    deliver(row,column,2,1); 
                    
                    conn();
                                         
                    myDir=north;
                    
                    
                    
                    digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                    {  line_following();  }    // do line following                  
                    digitalWrite(13,LOW);      // indicate stop line following
                    MotorControl(1,1);
                    delay(200);
                    
                    column=1;
                    Serial.print("row = ");
                    Serial.println(row);
                    Serial.print("column = ");
                    Serial.println(column);
                    
                    goback(2,1,row,column);
                     
                     
                     
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


