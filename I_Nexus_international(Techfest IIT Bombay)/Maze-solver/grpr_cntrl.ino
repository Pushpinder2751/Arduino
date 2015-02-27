

void gripperControl(int drive)
{
switch (drive) {
    // gripper control parameters
    case '1':                  // CLOSE GRIPPER
      if (gripperFlag)
      {
      digitalWrite (G1,LOW);
      digitalWrite (G2,HIGH);
      delay(220);
      digitalWrite (G1,LOW);
      digitalWrite (G2,LOW);
      gripperFlag = false;
      }
      break;
    case '2':                  // OPEN GRIPPER
      if (!gripperFlag)
      {
      digitalWrite (G1,HIGH);
      digitalWrite (G2,LOW);
      delay(220);
      digitalWrite (G1,LOW);
      digitalWrite (G2,LOW);
      gripperFlag = true;
      }
      break;
    case '0':                  // STOP GRIPPER
      digitalWrite (G1,LOW);
      digitalWrite (G2,LOW);
      break;
    default: break;           // no action
  }
}
