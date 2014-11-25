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
  Timer3.start(MinTimer);

}

void PIDCalc()
{
  if (timerpid + tt < millis())
  {
    intervalpid = millis() - timerpid;
    timerpid = millis();
    Palt = erroalt * kP;
    Paz = erroaz * kP;
    Ialt = Ialt + (Palt * intervalpid) * kI;
    Iaz = Iaz + (Palt * intervalpid) * kI;
    Dalt = (erroalt - erroaltprevious) / intervalpid * kD;
    Daz = (erroaz - erroazprevious) / intervalpid * kD;
    PIDaz = Paz + Iaz + Daz + PIDaz;
    PIDalt = Palt + Ialt + Dalt + PIDalt;
    PIDalt = PIDalt /2;
    PIDaz = PIDaz /2;
  }
}

void acionamotor() {
  erroazprevious = erroaz;
  erroaz = AZmount -  AZmountAlvo;
  erroaltprevious = erroalt;
  erroalt = ALTmount -  ALTmountAlvo;

  /////////////////////////AZ MOV
  if (PIDaz == 0)
  {
    if (micros() > intervalpulseaz)
    {
      intervalpulseaz = Accelaz + micros();
      gotoAz();
    }
  }
  else
  {
    if (micros() > intervalpulseaz)
    {
      if (Accelaz < MaxPassoAz / abs(PIDaz))
      {
        Accelaz = MaxPassoAz / abs(PIDaz);
      }
      else
      {
        if (Accelaz > (MaxPassoAz/500)) {
          Accelaz = (MaxPassoAz/500);
        }
        Accelaz = (Accelaz * 0.9995);
      }
      if (Accelaz < (3 * MinTimer))
      {
        Accelaz = 3 * MinTimer;
      }
      intervalpulseaz = Accelaz + micros();
      gotoAz();
    }

  }
  /////////////////////////ALT MOV
  if (PIDalt == 0)
  {
    if (micros() > intervalpulsealt)
    {
      intervalpulsealt = Accelalt + micros();
      gotoAlt();
    }
  }
  else
  {
    if (micros() > intervalpulsealt)
    {
      if (Accelalt < MaxPassoAlt / abs(PIDalt))
      {
        Accelalt = MaxPassoAlt / abs(PIDalt);
      }
      else
      {
        if (Accelalt > (MaxPassoAlt/500)) {
          Accelalt = (MaxPassoAlt/500);
        }
        Accelalt = (Accelalt * 0.9995);
      }
      if (Accelalt < (3 * MinTimer))
      {
        Accelalt = 3 * MinTimer;
      }
      intervalpulsealt = Accelalt + micros();
      gotoAlt();
    }

  }

}



int gotoAlt()
{

  if (PIDalt > 0) {
    digitalWrite(DirAltpino, HIGH);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer / 3);        // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount--;
    return abs(erroalt);
  }
  if (PIDalt < 0) {
    digitalWrite(DirAltpino, LOW);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer / 3);        // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount++;
    return abs(erroalt);
  }
  if (PIDalt = 0) {
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer / 3);        // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    if (PassoAltpino == HIGH)
    {
      ALTmount--;
    }
    else
    {
      ALTmount++;
    }
    return abs(erroalt);
  }
}


int gotoAz()
{

  if (PIDaz > 0) {
    digitalWrite(DirAzpino, HIGH);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer / 3);          // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount--;
    return abs(erroaz);
  }
  if (PIDaz < 0) {
    digitalWrite(DirAzpino, LOW);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer / 3);          // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount++;
    return abs(erroaz);

  }
  if (PIDaz == 0) {
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer / 3);          // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    if (DirAzpino == HIGH)
    {
      AZmount--;
    }
    else
    {
      AZmount++;
    }
    return abs(erroaz);
  }
}

int paramotors()
{
  AZmountAlvo = AZmount;
  ALTmountAlvo = ALTmount;
  return (1);

}

void movimentamotor()
{
  if (sul != 0)
  {
    ALTmountAlvo = ALTmountAlvo + veloc;
  }
  if (leste != 0)
  {
    AZmountAlvo = AZmountAlvo + veloc;
  }
  if (oeste != 0)
  {
    AZmountAlvo = AZmountAlvo - veloc;
  }
  if (norte != 0)
  {
    ALTmountAlvo = ALTmountAlvo - veloc;
  }
}

void  CalcPosicaoPasso()
{
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




