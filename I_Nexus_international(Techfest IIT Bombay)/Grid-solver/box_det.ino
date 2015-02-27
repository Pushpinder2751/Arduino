

void deliver(int int_row,int int_col,int dest_row,int dest_col)
{
  int r=0;
  int c=0;
  
  r= int_row-dest_row;
  c= int_col-dest_col;
  if(r>0 && c>0)
    {
      Serial.println("west then south");
      Serial.println("loop1");
      change_Dir(myDir,west);
      myDir=west;
      while(r>0)
        {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                r--;
                Serial.print("r= ");
                Serial.println(r);
        }
      Serial.println("reached dest. row");
      change_Dir(myDir,south);
      myDir=south;
      while(c>0)
        {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                c--;
                Serial.print("c= ");
                Serial.println(c);
        }
      Serial.println("reached dest. col");
    }
    
    else if(r<0 && c>0)
    {
      Serial.println("loop3");
      Serial.println("east then southt");
      change_Dir(myDir,east);
      myDir=east;

      while(r<0)
      {
           digitalWrite(13,HIGH);    // indicate start line following
           while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
            {  line_following();  }    // do line following                  
           digitalWrite(13,LOW);      // indicate stop line following
           MotorControl(1,1);
           delay(200);
           r++;
           Serial.print("r= ");
           Serial.println(r);
      }
      Serial.println("reached dest. row");
      change_Dir(myDir,south);
      myDir=south;
            while(c>0)
      {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                c--;
                Serial.print("c= ");
                Serial.println(c);
      }
      Serial.println("reached dest. col");
    }
    else if(r>0 && c==0)
    {
      Serial.println("west then ");
      Serial.println("loop5");
        if(int_row%2==0)
          {
            change_Dir(myDir,west);
            myDir=west;
            while(r>0)
            {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                r--;
                Serial.print("c= ");
                Serial.println(c);
            }
            
            Serial.println("reached dest. row");
            MotorControl(1,1);
            delay(300);
            change_Dir(myDir,south);
            myDir=south;
          }
        else
          {
            change_Dir(myDir,west);
            myDir=west;
            while(r>0)
            {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                r--;
                Serial.print("r= ");
                Serial.println(r);
            }
            
            Serial.println("reached dest. row");
            MotorControl(1,1);
            delay(300);
            change_Dir(myDir,south);
            myDir=south;
          }
    }
    else if(r==0 && c>0)
    {
      Serial.println("loop6");
        while(c>0)
          {
                    digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                    {  line_following();  }    // do line following                  
                    digitalWrite(13,LOW);      // indicate stop line following
                    MotorControl(1,1);
                    delay(200);
                    c--;
                    Serial.print("c= ");
                    Serial.println(c);
          }
      Serial.println("reached dest. col");
    }
    
    
}

void goback(int int_row,int int_col,int dest_row,int dest_col)
{
  int r=0;
  int c=0;
  
  r= int_row-dest_row;
  c= int_col-dest_col;
  
    if(r>0 && c==0)
    {
      Serial.println("west then north");
      Serial.println("loop5");
            change_Dir(myDir,west);
            myDir=west;
            while(r>0)
            {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                r--;
                Serial.print("c= ");
                Serial.println(c);
            }
            
            Serial.println("reached dest. row");
            MotorControl(1,1);
            delay(50);
            change_Dir(myDir,north);
            myDir=north;
          
        
    }  
    else if(r<0 && c==0)
    {
        Serial.println("east then north");
        Serial.println("loop8");
        change_Dir(myDir,east);
        myDir=east;
        while(r<0)
            {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ERs)) || (!digitalRead(ELs)) )
                {  line_following();  }    // do line following                  
                digitalWrite(13,LOW);      // indicate stop line following
                MotorControl(1,1);
                delay(200);
                r++;
                Serial.print("r= ");
                Serial.println(r);
            }
           change_Dir(myDir,north);
            myDir=north; 
    }
   
}

