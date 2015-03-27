void iniciapmotores()
{
  pinMode(MicroPassoAzpino, OUTPUT);
  pinMode(MicroPassoAltpino, OUTPUT);
  pinMode(DirAltpino, OUTPUT);
  pinMode(DirAzpino, OUTPUT);
  pinMode(PassoAltpino, OUTPUT);
  pinMode(PassoAzpino, OUTPUT);
  digitalWrite(MicroPassoAzpino, HIGH);
  digitalWrite(MicroPassoAltpino, HIGH);
  digitalWrite(DirAltpino, HIGH);
  digitalWrite(DirAzpino, HIGH);
  AltMotor.setPinsInverted(true);
  AzMotor.setPinsInverted(true);
  AltMotor.setMaxSpeed(20000.0);
  AltMotor.setAcceleration(5000.0);
  AzMotor.setMaxSpeed(20000.0);
  AzMotor.setAcceleration(5000.0);
  Timer3.start(MinTimer);
}

void setaccel()
{
  AltMotor.setMaxSpeed(abs(AltMotor.distanceToGo() / 2) + 1);
  AzMotor.setMaxSpeed(abs(AzMotor.distanceToGo() / 2) + 1);
}

void setaccel(int Accel)
{
  AltMotor.setMaxSpeed(Accel);
  AzMotor.setMaxSpeed(Accel);
}



void syncro()
{
  AltMotor.setCurrentPosition((int)ALTmountAlvo);
  AzMotor.setCurrentPosition((int)AZmountAlvo);
  CalcPosicaoPasso();
}

void SetPosition()
{
  AltMotor.moveTo((int)ALTmountAlvo);
  AzMotor.moveTo((int)AZmountAlvo);
}

void acionamotor() {
  AltMotor.run();
  AzMotor.run();
}



int paramotors()
{
  AZmountAlvo = AZmount;
  ALTmountAlvo = ALTmount;
  return (1);
}

void  CalcPosicaoPasso()
{
  ALTmount = AltMotor.currentPosition();
  AZmount = AzMotor.currentPosition();
  eixoAltGrausDecimal = 360.0 / MaxPassoAlt * ALTmount;
  eixoAzGrausDecimal = 360.0 / MaxPassoAz * AZmount;
}

void  protegemount()
{
  if ((eixoAltGrausDecimal < 1 ) || (eixoAltGrausDecimal > 90))
  {
    paramotors();
    ativaacom = 0;
  }


  if ((eixoAzGrausDecimal < 1) || (eixoAzGrausDecimal > 360))
  {
    paramotors();
    ativaacom = 0;
  }
}




