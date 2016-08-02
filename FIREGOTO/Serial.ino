//updates
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
  Serial3.print(str);
}

/*
void serialEvent3() {
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
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
*/

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar != ' ' )
    {
      pontBuffer = pontBuffer + 1;
      Command[pontCommand][pontBuffer] = inChar;
    }
    if (inChar == ':' && Command[1][pontCommand] != 'S')
    {
      pontBuffer = 0;
      Command[pontCommand][pontBuffer] = inChar;
    }
    if (inChar == '#' &&  pontBuffer > 0 )
    {
      pontBuffer = pontBuffer + 1;
      Command[pontCommand][pontBuffer] = inChar;
      pontBuffer = 0;
      pontCommand = pontCommand+1;
      if (pontCommand > 14 )
      {
        pontCommand=0;
      }
      Command[pontCommand][pontBuffer]  = '@';
    }
    if (pontBuffer > 29)
    {
      pontBuffer = 0;
    }
  }
}

void SerialPrintDebug(String str)
{
  if (flagDebug == 1)
  {
  Serial.print(str);
  }
}

