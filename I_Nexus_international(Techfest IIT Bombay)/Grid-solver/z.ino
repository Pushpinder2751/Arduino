 void conn()
{
  turn=0;
                     while(1)
                    {
                       
                        Serial.print("turn count =");
                        Serial.println(turn);

                        digitalWrite(13,HIGH);    // indicate start line following
                        while( (!digitalRead(ERs)) && (!digitalRead(ELs)) )
                        {  line_following();  }    // do line following
                                 //when the last sensors are on white stop
                        digitalWrite(13,LOW);
                        delay(50);
                        Serial.println("m out");
                        if( !(digitalRead(ELs)) && (digitalRead(Ms)) && (digitalRead(ERs)) )
                        {
                          MotorControl(1,1);
                          delay(150);
                          MotorControl(0,0);
                          delay(100);
                          MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                          while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
			  while(digitalRead(Ms));
                          delay(50);
                          MotorControl(0,0);
                          delay(100);
                          MotorControl(1,1);
                          delay(150);
                          turn++;
                        }
                        else if( (digitalRead(ELs)) && (digitalRead(Ms)) && !(digitalRead(ERs)) )
                        {
                          MotorControl(1,1);
                          delay(150);
                          MotorControl(0,0);
                          delay(100);
                          MotorControl(2,1);	//delay(600);	//turn right ...blind turn
                          while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
			  while(digitalRead(Ms));
                          delay(50);
                          MotorControl(0,0);
                          delay(100);
                          MotorControl(1,1);
                          delay(150);
                          turn++;
                        }
                        
                        
                        if(turn==6)
                        {
                            MotorControl(1,1);
                            delay(150);
                                digitalWrite(13,HIGH);    // indicate start line following
                                while( (!digitalRead(ERs)) && (!digitalRead(ELs)) )
                                {  line_following();  }    // do line following
                                         //when the last sensors are on white stop
                                digitalWrite(13,LOW);
                            MotorControl(2,2);
                            delay(450);
                            gripperControl(gripperOpen);
                            gripperControl(gripperStop);
                            MotorControl(2,2);
                            delay(250);
                            
                          MotorControl(1,2);	
      		          delay(200);
                          while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
			  while(digitalRead(Ms));
                          delay(50);  
      		          MotorControl(0,0);	delay(100);
                          Serial.println("turn complete");

                            
                        }
                        if(turn==12)
                        {
                            digitalWrite(13,HIGH);    // indicate start line following
                        while( (!digitalRead(ERs)) && (!digitalRead(ELs)) )
                        {  line_following();  }    // do line following
                                 //when the last sensors are on white stop
                        digitalWrite(13,LOW);
                         goto backToGrid2;    
                        }
                    
                    }
                         
                        
                    
                    
          backToGrid2:
           delay(1);         
}                   
                    
                    
                    

/* ///////// --> define these at the very beginning of the code below #includes
#define STD_LOOP_TIME  4
int lastLoopUsefulTime = STD_LOOP_TIME;
unsigned long loopStartTime = 0;

  
//////////--> goes inside void loop()   // --> last syntax before ending the loop
// *********************** loop timing control **************************
    lastLoopUsefulTime=0;
    loopStartTime = millis();
    while(lastLoopUsefulTime<STD_LOOP_TIME)  
    {
       line_follow();
       lastLoopUsefulTime = millis()-loopStartTime;
    }                    
    
 */   
