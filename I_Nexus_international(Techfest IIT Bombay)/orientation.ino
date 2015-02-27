void changeRow(int row_count, int dir)
{
    
    MotorControl(1,1);	delay(150);		// blind forward movement
    int r = (row_count%2);
    
    if(r==0)	 				// i.e row is even
    {
	///FIRST TURN
        dir = change_Dir (dir, east);		//change dir from south to east
        myDir = dir;                            // update mydir
	///FIRST TURN COMPLETE	
	row++;
	digitalWrite(13,HIGH);    // indicate start line following
        while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
        {  line_following();  }
        MotorControl(0,0);    //when the last sensors are on white stop
        digitalWrite(13,LOW);    // indicate stop line following
        
        if( (digitalRead(ELs)) && (!digitalRead(Ms)) && (digitalRead(ERs)) )
        {
            digitalWrite(13,HIGH);    // indicate start line following
            while( (digitalRead(ELs)) || (digitalRead(ERs)) )    {  MotorControl(1,1);  }
            delay(50);    MotorControl(0,0);
            digitalWrite(13,LOW);    // indicate start line following
            gridMap[row-1][column-1]=1;
            Serial.println("BlockingNode");
        }
        else  
        {
            gridMap[row-1][column-1]=2;
            Serial.println("SimpleNode");
            while( (digitalRead(ELs)) || (digitalRead(ERs)) )    {  line_following();  }
        }
	MotorControl(1,1);	delay(350);	// blind forward movement // 300 here works correct 
						// 200 causes the bot to not cross the node and reach a sufficient distance so as to take a proper turn
        
	///SECON TURN
        dir = change_Dir (dir, north);		//change dir from east to north
        myDir = dir;                            // update mydir
	///SECON TURN COMPLETE
    }
	
    else	 			// i.e row is odd
    {
	///FIRST TURN
        dir = change_Dir (dir, east);		//change dir from south to east
        myDir = dir;                            // update mydir
	///FIRST TURN COMPLETE	
        row++;
	digitalWrite(13,HIGH);    // indicate start line following
        while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
        {  line_following();  }
        MotorControl(0,0);    //when the last sensors are on white stop
        digitalWrite(13,LOW);    // indicate stop line following
        
        if( (digitalRead(ELs)) && (!digitalRead(Ms)) && (digitalRead(ERs)) )
        {
            digitalWrite(13,HIGH);    // indicate start line following
            while( (digitalRead(ELs)) || (digitalRead(ERs)) )    {  MotorControl(1,1);  }
            delay(50);    MotorControl(0,0);
            digitalWrite(13,LOW);    // indicate start line following
            gridMap[row-1][column-1]=1;
            Serial.println("BlockingNode");
        }
        else  
        {
            gridMap[row-1][column-1]=2;
            Serial.println("SimpleNode");
            while( (digitalRead(ELs)) || (digitalRead(ERs)) )    {  line_following();  }
        }
	MotorControl(1,1);	delay(400);	// blind forward movement // 300 here works correct 
						// 200 causes the bot to not cross the node and reach a sufficient distance so as to take a proper turn
        
	///SECON TURN
        dir = change_Dir (dir, south);		//change dir from east to south
        myDir = dir;                            // update mydir
	///SECON TURN COMPLETE
    }
	
}

/*
 * Call this function to change the orientation of the robot
 * takes 2 input paremeters, current_direction & next_direction
 * returns changed direction
 * Dependencies:
 * -->  MotorControl (int driveL, int driveR);
*/
int change_Dir (int my_Dir, int next_dir)

{
	if (my_Dir == north)
	{
////////////////////////////
			switch (next_dir)
			{
				case (east):
					MotorControl(1,2);	////delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(1,2);
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
                                        {
                                        while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					while(digitalRead(Ms));
					delay(100);		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
					
				case (south):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
					{
                                            
          			            delay(1300);
                                        }  		//while middle pin is not on white...turn right
										
					  		//while middle pin is not on white...turn right
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
					
				case (west):
					MotorControl(2,1);	//delay(600);	//turn left ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(2,1);
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
                                        {
                                          while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms));   		//while middle pin is not on white...turn right
					  delay(100);   		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
					
				default: break;
			}
	}
////////////////////////////
	if (my_Dir == east)
	{
			switch (next_dir)
			{
				case (south):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(1,2);
                                      	delay(300);
                                        ladder=false;
                                        }
                                        else
                                        {
                                          while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms));
					  delay(100);  		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;

				case (west):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
					delay(600);   		//while middle pin is not on white...turn right
					delay(70);    MotorControl(0,0);	delay(90);
                                        
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
					delay(700);   		//while middle pin is not on white...turn right
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
                                        
				case (north):
					MotorControl(2,1);	//delay(600);	//turn left ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(2,1);
                                        while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
					while(digitalRead(Ms));
				        delay(100);
                                        ladder=false;
                                        }
                                        else
                                        {
                                          while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms));
					  delay(100);   		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
                                        
				default: break;
			}
	}
////////////////////////////
	if (my_Dir == south)
	{
			switch (next_dir)
			{
				case (west):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(1,2);
                                        while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					while(digitalRead(Ms));
			                delay(100);
                                        ladder=false;
                                        }
                                        else
                                        {
                                          while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms));
					  delay(100);   		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
                                        
				case (north):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					while(digitalRead(Ms));		//while middle pin is not on white...turn right
                                        delay(100);
                                        my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
                                        
				case (east):
					MotorControl(2,1);	//delay(600);	//turn left ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(2,1);
                                        while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
					while(digitalRead(Ms));  
			                delay(100);   	
                                        ladder=false;
                                        }
                                        else
                                        {
                                          while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms));  
					  delay(100);   		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;	
                                        
				default: break;
			}
	}
////////////////////////////
	if (my_Dir == west)
	{
			switch (next_dir)
			{
				case (north):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(1,2);
                                        while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					while(digitalRead(Ms)); 
				        delay(100);
                                        ladder=false;
                                        }
                                        else
                                        {
                                          while(!digitalRead(ERs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms)); 
					  delay(100);   		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;
                                        
				case (east):
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
					delay(600);   		//while middle pin is not on white...turn right
					delay(70);    MotorControl(0,0);	delay(90);
                                        
					MotorControl(1,2);	//delay(600);	//turn right ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        ladder=false;
                                        }
                                        else
					delay(700);   		//while middle pin is not on white...turn right
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;

				case (south):
					MotorControl(2,1);	//delay(600);	//turn left ...blind turn
                                        if(ladder)
                                        {
                                        delay(300);
                                        ladder=false;
                                        MotorControl(1,1);
                                        delay(1200);
                                        MotorControl(2,1);
                                        delay(300);
                                        }
                                        else
                                        {
                                          while(!digitalRead(ELs));   		//while middle pin is not on white...turn right
					  while(digitalRead(Ms));
					  delay(100);  		//while middle pin is not on white...turn right
                                        }
					my_Dir = next_dir;  // update current Dir
					delay(70);    MotorControl(0,0);	delay(90);
					break;	
	
				default: break;
			}
	}
        
	return (my_Dir); // return updated direction to calling function
}




