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
  Timer3.start(Tpulso);

}



void acionamotor() {
  rampa();
  ganhoaz++;
  if (ganhoaz  >= intervalaz)
  {
    ganhoaz = 0;
    gotoAz();
  }
  ganhoalt++;
  if (ganhoalt  >= intervalalt)
  {
    ganhoalt = 0;
    gotoAlt();
  }
}


int gotoAlt()
{
  double erro = ALTmount -  ALTmountAlvo;
  if (erro > 1) {
    digitalWrite(DirAltpino, HIGH);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(Tpulso / 3);          // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount--;
    return abs(erro);

  } else
  {
    if (erro < 1) {
      digitalWrite(DirAltpino, LOW);
      digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
      delayMicroseconds(Tpulso / 3);          // wait for a second
      digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
      ALTmount++;
      return abs(erro);

    } else
    {
      return (1);
    }

  }
}

int gotoAz()
{
  double erro = AZmount -  AZmountAlvo;
  if (erro > 1) {
    digitalWrite(DirAzpino, HIGH);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(10);            // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount--;
    return abs(erro);
  } else
  {
    if (erro < 1) {
      digitalWrite(DirAzpino, LOW);
      digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
      delayMicroseconds(10);            // wait for a second
      digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
      AZmount++;
      return abs(erro);

    } else
    {
      return (1);
    }

  }
}


void rampa()
{
  currentMillis = millis();
  if (currentMillis - previousMillis >= 4)
  {
    previousMillis = currentMillis;


    accelaz++;
    intervalaz = 10000 / (accelaz);
    erroAZ = (abs)(AZmount -  AZmountAlvo);
    if (intervalaz < (10000 / erroAZ))
    {
      intervalaz = 10000 / erroAZ;
      accelaz = erroAZ;
    }

    accelalt++;
    intervalalt = 10000 / (accelalt);
    erroALT = (abs)(ALTmount -  ALTmountAlvo);
    if (intervalalt < (10000 / erroALT))
    {
      intervalalt = 10000 / erroALT;
      accelalt = erroALT;
    }
    intervalalt = incliRampa * intervalalt;
    intervalaz = incliRampa * intervalaz;
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
  eixoAltGrausDecimal = 90.0 / MaxPassoAlt * ALTmount;
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




