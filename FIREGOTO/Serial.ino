
void lebuffercomand()
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
    if (pontBufferold > 19)
    {
      pontBufferold = 0;
    }

  }
}
void SerialPrint(String str)
{
  Serial.print(str);
  Serial2.print(str);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    buffercmd[pontBuffer] = inChar;
    pontBuffer = pontBuffer + 1;
    if (pontBuffer > 19)
    {
      pontBuffer = 0;
    }
  }
}
void serialEvent2() {
  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    buffercmd[pontBuffer] = inChar;
    pontBuffer = pontBuffer + 1;
    if (pontBuffer > 19)
    {
      pontBuffer = 0;
    }
  }
}

