int rescueRun(int res_row,int res_col, int orient)
{
  // navigation parameter initialization
    int ro=4,col=0; 
    counter=0;
    int destCol=res_col, destRow=res_row;
    
    
    for(int i=0;i<20;i++)
    navigate[i]=255;
    int previousTurn = 0;
    
        // path planning and trajectory
    // reading Grid navigation Map from EEPROM
   
    while( (ro != destRow) || (col != destCol) )
    {
      Serial.println("I am in");
      
        if(ro<destRow)
        {
            if ( (gridNavigation[ro][col+1] > 1) && (col+1<8) )//used
            {
                Serial.println("loop1");
                navigate[counter] = north;
                previousTurn = navigate[counter];
                col++;  counter++;
                Serial.print("row = ");
                Serial.println(ro);
                Serial.print("column = ");
                Serial.println(col);
            }
            else
            {
                if (col>destCol)
                {  
                    if ( (gridNavigation[ro-1][col] > 1) && (ro-1>=0) && (previousTurn != east) )
                    {
                        Serial.print("loop2");
                        navigate[counter] = west;
                        previousTurn = navigate[counter];
                        ro--;  counter++;
                        Serial.print("row = ");
                        Serial.println(ro);
                        Serial.print("column = ");
                        Serial.println(col);
                    }
                    else if( (gridNavigation[ro+1][col] >1 ) && (ro+1<8) && (previousTurn != west) )
                    {
                       Serial.print("loop3");
                        navigate[counter] = east;
                        previousTurn = navigate[counter];
                        ro++;  counter++;
                        Serial.print("row = ");
                        Serial.println(ro);
                        Serial.print("column = ");
                        Serial.println(col);
                    }
                    else if ( (gridNavigation[ro][col] == 3) )
                     {
                       if(gridNavigation[ro-1][col+1] >1)
                       {
                         Serial.print("loop4");
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = west;
                         
                         previousTurn = navigate[counter];
                         
                         ro--; col++;  counter++;
                         Serial.print("row = ");
                        Serial.println(ro);
                        Serial.print("column = ");
                        Serial.println(col);
                         //forward den left ladder
                       }
                     }
                     else if( (gridNavigation[ro][col] == 4) )
                     {
                       if(gridNavigation[ro+1][col+1] >1)
                       {
                         Serial.print("loop5");
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = east;
                         previousTurn = navigate[counter];
                         
                         ro++; col++;  counter++;
                         Serial.print("row = ");
                         Serial.println(ro);
                         Serial.print("column = ");
                         Serial.println(col);
                         //forward den right ladder
                       }
                     }
                }
                else//used
                {
                  if ( (gridNavigation[ro+1][col] > 1) && (ro+1<8) )
                    {
                      Serial.print("loop6");
                        navigate[counter] = east;
                        previousTurn = navigate[counter];
                        ro++;  counter++;
                        Serial.print("row = ");
                        Serial.println(ro);
                        Serial.print("column = ");
                        Serial.println(col);
                    }
                   else if ( (gridNavigation[ro][col] == 4) )
                   {
                     if( (gridNavigation[ro+1][col+1] > 1) && (col+1<8) && (ro+1<8) )
                     {
                       Serial.print("loop7");
                       navigate[counter] =9;
                       counter++;
                       navigate[counter] = east;
                       previousTurn = navigate[counter];
                       
                       ro++; col++;  counter++;
                       Serial.print("row = ");
                        Serial.println(ro);
                        Serial.print("column = ");
                        Serial.println(col); 
                       //forward den right ladder
                     }
                   }
                    else if( (gridNavigation[ro][col] == 3) )
                     {
                       if( (gridNavigation[ro+1][col-1] > 1) )
                       {
                         Serial.print("loop8");
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = west;
                         previousTurn = navigate[counter];
                         
                         ro--; col++;  counter++;
                         Serial.print("row = ");
                         Serial.println(ro);
                         Serial.print("column = ");
                         Serial.println(col);
                         //forward den left ladder
                       }
                     }
                   
                   else
                   {
                       Serial.print("loop9");
                         navigate[counter] = west;
                         previousTurn = navigate[counter];
                         ro--;   counter++;
                         Serial.print("row = ");
                         Serial.println(ro);
                         Serial.print("column = ");
                         Serial.println(col);
                   }
                }
            }
        }
        //ro>destrow
        else
        {
            if (col>destCol)//used
            {    
                 if ( (gridNavigation[ro][col+1] > 1) && (col+1<8)  )//used
                {
                  Serial.print("loop10");
                    navigate[counter] = north;
                    previousTurn = navigate[counter];
                    col++;  counter++;
                    Serial.print("row = ");
                    Serial.println(ro);
                    Serial.print("column = ");
                    Serial.println(col);
                }              
                else if ( (gridNavigation[ro-1][col] > 1) && (ro-1>=0) && (previousTurn != east) ) 
                {
                  Serial.print("loop11");
                    navigate[counter] = west;
                    previousTurn = navigate[counter];
                    ro--;  counter++;
                    Serial.print("row = ");
                    Serial.println(ro);
                    Serial.print("column = ");
                    Serial.println(col);
                }
                else if ( (gridNavigation[ro][col] == 3) )//used
                     {
                       Serial.print("loop12");
                       if(gridNavigation[ro-1][col+1] >1)
                       {
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = west;
                         previousTurn = navigate[counter];
                         
                         ro--; col++;  counter++;
                         Serial.print("row = ");
                         Serial.println(ro);
                         Serial.print("column = ");
                         Serial.println(col);
                         //forward den left ladder
                       }
                     }
                     else if( (gridNavigation[ro][col] == 4) )//used
                     {
                       if(gridNavigation[ro+1][col+1] >1)
                       {
                         Serial.print("loop13");
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = east;
                         previousTurn = navigate[counter];
                         
                         ro++; col++;  counter++;
                          Serial.print("row = ");
                          Serial.println(ro);
                          Serial.print("column = ");
                          Serial.println(col);
                         //forward den right ladder
                       }
                     }
                else
                {
                  Serial.print("loop14");
                    navigate[counter] = east;
                    previousTurn = navigate[counter];
                    col++;  counter++;
                    Serial.print("col+");  Serial.print(col,DEC);    Serial.print("  ");
                }  
            
            }
            else 
            {
              if(col<destCol)
              {
              if ( (gridNavigation[ro-1][col] > 1) && (ro-1>=0) && (previousTurn != east) )//used
                {
                    Serial.print("loop16");
                    navigate[counter] = west;
                    previousTurn = navigate[counter];
                    ro--;  counter++;
                    Serial.print("row = ");
                    Serial.println(ro);
                    Serial.print("column = ");
                    Serial.println(col);
                }  
                
                
              
              else if ( (gridNavigation[ro][col] == 3) )//used
                     {
                       if(gridNavigation[ro-1][col+1] >1)
                       {
                         Serial.print("loop17");
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = west;
                         previousTurn = navigate[counter];
                         
                         ro--; col++;  counter++;
                         Serial.print("row = ");
                         Serial.println(ro);
                         Serial.print("column = ");
                         Serial.println(col);
                         //forward den left ladder
                       }
                     }
                    
               else if ( (gridNavigation[ro][col+1] > 1) && (col+1<8)  )//used
                {
                  Serial.print("loop15");
                    navigate[counter] = north;
                    previousTurn = navigate[counter];
                    col++;  counter++;
                    Serial.print("row = ");
                    Serial.println(ro);
                    Serial.print("column = ");
                    Serial.println(col);
                }
              }      
                     
                     
              
                
                 else if( (gridNavigation[ro][col] == 4) )//used
                     {
                       if(gridNavigation[ro+1][col+1] >1)
                       {
                         Serial.print("loop18");
                         navigate[counter] =9;
                         counter++;
                         navigate[counter] = east;
                         previousTurn = navigate[counter];
                         
                         ro++; col++;  counter++;
                          Serial.print("row = ");
                          Serial.println(ro);
                          Serial.print("column = ");
                          Serial.println(col);
                         //forward den right ladder
                       }
                     else if ( (gridNavigation[ro+1][col] >1 ) && (ro+1<8)  )//used
                        {
                          Serial.print("loop20");
                            navigate[counter] = east;
                            previousTurn = navigate[counter];
                            ro++;  counter++;
                            Serial.print("row = ");
                            Serial.println(ro);
                            Serial.print("column = ");
                            Serial.println(col);
                        }
                    }    
                else if ( (gridNavigation[ro+1][col] >1 ) && (ro+1<8)  )//used
                {
                  Serial.print("loop19");
                    navigate[counter] = east;
                    previousTurn = navigate[counter];
                    ro++;  counter++;
                    Serial.print("row = ");
                    Serial.println(ro);
                    Serial.print("column = ");
                    Serial.println(col);
                }

                    
                     
        }
        
        }
        
    }
    Serial.println();
    for(int i=0;i<20;i++)
    {
        Serial.print(navigate[i],DEC);    Serial.println();
    }
    state=false;
    counter=0;
    while(!state)
        {
           if(navigate[counter] != 9)
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
             
             if(navigate[counter] == 9)
             {
               MotorControl(1,1);
               delay(400);
               change_Dir(myDir, north);
               myDir=north;
               counter++;
                    digitalWrite(13,HIGH);    // indicate start line following
                    while( (!digitalRead(ELs)) && (!digitalRead(ERs)) )
                    {  line_following();  }
                    digitalWrite(13,LOW);
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
                change_Dir(myDir, navigate[counter]);
                myDir=navigate[counter];
                counter++;
              
                MotorControl(1,1);
                delay(200);
               
                if(!digitalRead(ELs) && !digitalRead(ERs) );
                {
                  if(navigate[counter] < 255)
                    state=false;
                }
              }
             
             else if((digitalRead(ELs) && !digitalRead(ERs)))
             {
               
               Serial.println("l2");
               Serial.println("left ladder here");
               MotorControl(1,1);
                delay(300);
                ladder=true;
                change_Dir(myDir, navigate[counter]);
                myDir=navigate[counter];
                counter++;
              
                MotorControl(1,1);
                delay(200);
             }
             else if(!digitalRead(ELs) && digitalRead(ERs))
             {
              
               Serial.println("l3");
               Serial.println("right ladder here");
               MotorControl(1,1);
                delay(300);
                
                ladder=true;
                change_Dir(myDir, navigate[counter]);
                myDir=navigate[counter];
                counter++;
              
                MotorControl(1,1);
                delay(200);
             }
             
           
               if(!digitalRead(ELs) && !digitalRead(ERs) );
                {
                  if(navigate[counter] < 255)
                    state=false;
                }
              Serial.println("dir is ");
              Serial.println(navigate[counter]); 
              }
              
        }
    
        while( (!digitalRead(ELs)) || (!digitalRead(ERs)) )
        {  line_following();  }
        MotorControl(0,0);
        
}
