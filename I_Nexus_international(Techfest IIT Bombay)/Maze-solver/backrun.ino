void back_run()
{
  byte navigate1[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,255,255,255,255};
  boolean abc=false;
  int c=0;
  int y=0;
for(int i=20;i>=0;i--)
{
  
  while(navigate[i]>250)
  {
  i--;
  }
  Serial.println(i);
  
  
  if(navigate[i]==9)
  y=9;
  else if(navigate[i]==1)
  y=3;
  else
  {
  int x=navigate[i]-2;
  int z=x*x;
   y=sqrt(z);
  }
  navigate1[c]=y;
  c++;
}
navigate1[c]=east;

    Serial.println();
    for(int i=0;i<20;i++)
    {
        Serial.print(navigate1[i],DEC);    Serial.println();
    }



    
        
     counter =0;
    
        myDir = change_Dir(myDir, navigate1[counter]);
        Serial.print("turned ");
        Serial.println(myDir);
        counter++;    // next node
        
        
    while(navigate1[counter] < 250)
        {
           if(navigate1[counter] != 9)
           {
             Serial.println("no ladder");
                     digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
                    {  line_following();  }
                    digitalWrite(13,LOW);
             
           }
           
           line_following();
           
           if(!digitalRead(ELs) && !digitalRead(ERs) );
           
           else
           {
             
             if(navigate1[counter] == 9)
             {
                digitalWrite(13,HIGH);    // indicate start line following
                while( (!digitalRead(ELs)) && (!digitalRead(ERs)) )
                {  line_following();  }
                digitalWrite(13,LOW);
                MotorControl(1,1);
               delay(300);

                ladder=true;
               change_Dir(myDir, south);
               myDir=south;
               counter++;
                   
             }
                   
             
             MotorControl(1,1);
             delay(100);
             state=true;
             if(digitalRead(ELs) && digitalRead(ERs))
             {
               
               
               Serial.println("l1");
                MotorControl(1,1);
                delay(400);
                
                //turn 90
                change_Dir(myDir, navigate1[counter]);
                myDir=navigate1[counter];
                counter++;
              
                MotorControl(1,1);
                delay(200);
               
                if(!digitalRead(ELs) && !digitalRead(ERs) );
                {
                  if(navigate1[counter] < 255)
                    state=false;
                }
              }
             
             
             
           
               if(!digitalRead(ELs) && !digitalRead(ERs) );
                {
                  if(navigate1[counter] < 255)
                    state=false;
                }
              Serial.println("dir is ");
              Serial.println(myDir); 
              }
              
        }
        Serial.println("turned ");
        MotorControl(0,0);
                
        
    }



