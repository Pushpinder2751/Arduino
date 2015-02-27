void homeRun(int currentDir)
{
    int homeCount = 1;
    MotorControl(1,1);	delay(150);
    
    
    currentDir = change_Dir(currentDir, east);
    
        while(homeCount)
        {
            currentDir = change_Dir(currentDir, east);
            
            digitalWrite(13,HIGH);    // indicate start line following
            while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
            {  line_following();  }
              MotorControl(0,0);  //when the last sensors are on white stop
            digitalWrite(13,LOW);    // indicate stop line following
            
            while ( (digitalRead(ELs)) || (digitalRead(ERs)) )	{  MotorControl(1,1);  }		// skip current node
            delay(50);  	        // Stop bot and pause
            
            homeCount--;    // next node
        }
    
    // Code execution beyond this indicates that the bot has reached 0,0 (i.e., home location)
                          
                            
                            
                            lastLoopUsefulTime=0;
                            loopStartTime = millis();
                            while(lastLoopUsefulTime<STD_LOOP_TIME)  
                            {
                               line_following();
                               lastLoopUsefulTime = (millis())-loopStartTime;
                            }
    MotorControl(0,0);    delay(50);
    myDir = east;       // update robot's current direction
}
