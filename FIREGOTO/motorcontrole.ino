void iniciapmotores()
{
  //Iniciar as variaveis do motor de passo
  pinMode(MotorRA_Direcao, OUTPUT);
  pinMode(MotorRA_Passo, OUTPUT);
  pinMode(MotorRA_Sleep, OUTPUT);
  pinMode(MotorRA_Reset, OUTPUT);
  pinMode(MotorRA_M2, OUTPUT);
  pinMode(MotorRA_M1, OUTPUT);
  pinMode(MotorRA_M0, OUTPUT);
  pinMode(MotorRA_Ativa, OUTPUT);
  pinMode(MotorDEC_Direcao, OUTPUT);
  pinMode(MotorDEC_Passo, OUTPUT);
  pinMode(MotorDEC_Sleep, OUTPUT);
  pinMode(MotorDEC_Reset, OUTPUT);
  pinMode(MotorDEC_M2, OUTPUT);
  pinMode(MotorDEC_M1, OUTPUT);
  pinMode(MotorDEC_M0, OUTPUT);
  pinMode(MotorDEC_Ativa, OUTPUT);

  //Aciona os pinos por padrão
  digitalWrite(MotorRA_Direcao, HIGH);
  digitalWrite(MotorRA_Passo, LOW);
  digitalWrite(MotorRA_Sleep, HIGH);
  digitalWrite(MotorRA_Reset, HIGH);
  digitalWrite(MotorRA_M2, HIGH);
  digitalWrite(MotorRA_M1, HIGH);
  digitalWrite(MotorRA_M0, HIGH);
  digitalWrite(MotorRA_Ativa, LOW);
  digitalWrite(MotorDEC_Direcao, LOW);
  digitalWrite(MotorDEC_Passo, LOW);
  digitalWrite(MotorDEC_Sleep, HIGH);
  digitalWrite(MotorDEC_Reset, HIGH);
  digitalWrite(MotorDEC_M2, HIGH);
  digitalWrite(MotorDEC_M1, HIGH);
  digitalWrite(MotorDEC_M0, HIGH);
  digitalWrite(MotorDEC_Ativa, LOW);

  AltMotor.setPinsInverted(true);
  AzMotor.setPinsInverted(true);
  AltMotor.setMaxSpeed(dMaxSpeedAlt);
  AltMotor.setAcceleration(5000.0);
  AzMotor.setMaxSpeed(dMaxSpeedAz);
  AzMotor.setAcceleration(5000.0);
//  Timer.attachInterrupt(acionamotor);
//  Timer.start(MinTimer);

}

void setaccel()
{
  double tempdis;
  tempdis = abs(AzMotor.distanceToGo());
  AzMotor.setMaxSpeed(tempdis / 10 * tempdis / 10 );
  tempdis = abs(AltMotor.distanceToGo());
  AltMotor.setMaxSpeed(tempdis / 10 * tempdis / 10 );
}

void setaccel(int Accel)
{
  AltMotor.setMaxSpeed(Accel);
  AzMotor.setMaxSpeed(Accel);
}

void addbackslash()
{
  if (AzMotor.distanceToGo() >= 0)
  {
    dirAz = 1;
  } else {
    dirAz = 0;
  }
  if (AltMotor.distanceToGo() >= 0)
  {
    dirAlt = 1;
  } else {
    dirAlt = 0;
  }
  if (AtivaBack == 1)
  {
    AtivaBack = 0;
    if (dirAlt != dirAltant)
    {
      if (dirAlt == 0)
      {
        Serial.println("alt:0");
        AltMotor.setCurrentPosition(AltMotor.currentPosition() + RAbacklash);
      } else
      {
        AltMotor.setCurrentPosition(AltMotor.currentPosition() - RAbacklash);
        Serial.println("alt:1");

      }
    }
    if (dirAz != dirAzant)
    {
      if (dirAz == 0)
      {
        AzMotor.setCurrentPosition( AzMotor.currentPosition() + DECbacklash);
        Serial.println("az: 0 ");

      } else
      {
        AzMotor.setCurrentPosition( AzMotor.currentPosition() - DECbacklash);
        Serial.println("az: 1");

      }
    }
  }
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


  //Cria MicroSeg Virtusal
  Segundo = second();
  if (MilissegundoSeg == Segundo)
  {
    Microssegundo =  Microssegundo + MinTimer;
    if (Microssegundo > 999999)
    {
      Microssegundo = 999999;
    }
    SegundoFracao = Microssegundo * 0.000001;
    SegundoFracao = SegundoFracao + Segundo;
  }
  else
  {
    MilissegundoSeg = Segundo;
    Microssegundo = 1;
  }
}



int paramotors()
{
  AZmountAlvo = AZmount;
  ALTmountAlvo = ALTmount;
  return (1);
}

void CalcPosicaoPasso()
{
  ALTmount = AltMotor.currentPosition();
  AZmount = AzMotor.currentPosition();
  eixoAltGrausDecimal = ResolucaoeixoAltGrausDecimal * ALTmount;
  eixoAzGrausDecimal = ResolucaoeixoAzGrausDecimal * AZmount;
}

void protegemount()
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


