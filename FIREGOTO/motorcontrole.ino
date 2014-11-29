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
  double microsfixo = micros();

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
    if (PIDaz == 0 ) {
      PIDaz = Paz + Iaz + Daz;
    } else {
      if (abs(PIDaz) > 15)
      {
        PIDaz = (Paz + Iaz + Daz + (4 * PIDaz)) / 5;
      }
      else
      {
        PIDaz = (Paz + Iaz + Daz + (99 * PIDaz)) / 100;
      }
    }
    if (PIDalt == 0 ) {
      PIDalt = Palt + Ialt + Dalt;
    } else {
      if (abs(PIDalt) > 15)
      {
        PIDalt = (Palt + Ialt + Dalt + (4 * PIDalt)) / 5;
      }
      else
      {
        PIDalt = (Palt + Ialt + Dalt + (99 * PIDalt)) / 100;
      }
    }
  }
}

void acionamotor() {
  erroazprevious = erroaz;
  erroaz = AZmount -  AZmountAlvo;
  double microsfixo = micros();
  erroaltprevious = erroalt;
  erroalt = ALTmount -  ALTmountAlvo;

  /////////////////////////AZ MOV
  if (microsfixo > intervalpulseaz)
  {


    /////Accelaz
    if (Accelaz < MaxPassoAz / abs(PIDaz))
    {
      Accelaz = MaxPassoAz / abs(PIDaz);
    }
    else
    {
      if (Accelaz > (MaxPassoAz / 250)) {
        Accelaz = (MaxPassoAz / 250);
      }
      Accelaz = (Accelaz * 0.999);
    }


    if (Accelaz < (3 * MinTimer))
    {
      Accelaz = 3 * MinTimer;
    }
    if (Accelaz > MaxPassoAz)
    {
      Accelaz = MaxPassoAz;
    }


    intervalpulseaz = Accelaz + microsfixo;
    gotoAz();
  }
  /////////////////////////ALT MOV
  if (microsfixo > intervalpulsealt)
  {


    /////Accelalt
    if (Accelalt < MaxPassoAlt / abs(PIDalt))
    {
      Accelalt = MaxPassoAlt / abs(PIDalt);
    }
    else
    {
      if (Accelalt > (MaxPassoAlt / 250)) {
        Accelalt = (MaxPassoAlt / 250);
      }
      Accelalt = (Accelalt * 0.999);
    }
    if (Accelalt < (3 * MinTimer))
    {
      Accelalt = 3 * MinTimer;
    }
    if (Accelalt > MaxPassoAlt)
    {
      Accelalt = MaxPassoAlt;
    }




    intervalpulsealt = Accelalt + microsfixo;
    gotoAlt();
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




