
/*void lebuffercomand()
{
  if (pontBufferold != pontBuffer)
  {

    inputcmd[pontCommand] = buffercmd[pontBufferold];
    if (inputcmd[pontCommand] == ':' && inputcmd[1] != 'S')
    {
      pontCommand = 0;
      inputcmd[pontCommand] = buffercmd[pontBufferold];
      //  printe();
    }
    if (inputcmd[pontCommand] == ' ' )
    {
      pontCommand = pontCommand - 1;
    }

    if (inputcmd[pontCommand] == '#' )
    {
      cmdComplete = true;
      pontCommand = 0;
      //     printe();
    }
    pontBufferold = pontBufferold + 1;
    pontCommand = pontCommand + 1;
    if (pontBufferold > 29)
    {
      pontBufferold = 0;
    }

  }
}*/
void SerialPrint(String str)
{
  Serial.print(str);
  Serial2.print(str);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar != ' ' )
    {
      pontBuffer = pontBuffer + 1;
      buffercmd[pontBuffer] = inChar;
    }
    if (inChar == ':' && buffercmd[1] != 'S')
    {
      pontBuffer = 0;
      buffercmd[pontBuffer] = inChar;
    }
    if (inChar == '#' &&  pontBuffer > 0 )
    {
      cmdComplete = true;
      pontBuffer = pontBuffer + 1;
      buffercmd[pontBuffer] = inChar;
      memcpy(inputcmd, buffercmd, pontBuffer);
      pontBuffer = 0;
      buffercmd[1] = '@';
      executecommand();
    }
    if (pontBuffer > 29)
    {
      pontBuffer = 0;
    }
  }
}
void serialEvent2() {
  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    if (inChar != ' ' )
    {
      pontBuffer = pontBuffer + 1;
      buffercmd[pontBuffer] = inChar;
    }
    if (inChar == ':' && buffercmd[1] != 'S')
    {
      pontBuffer = 0;
      buffercmd[pontBuffer] = inChar;
    }
    if (inChar == '#' &&  pontBuffer > 0 )
    {
      cmdComplete = true;
      pontBuffer = pontBuffer + 1;
      buffercmd[pontBuffer] = inChar;
      memcpy(inputcmd, buffercmd, pontBuffer);
      pontBuffer = 0;
      buffercmd[1] = '@';
      executecommand();
    }
    if (pontBuffer > 29)
    {
      pontBuffer = 0;
    }
  }
}

