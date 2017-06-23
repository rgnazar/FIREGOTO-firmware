void RotinadeSetup() //:HSETUPON#
{
  SerialPrint("\n ######################################################################### \n");
  if (setupflag == 0)
  {
    SerialPrint(" \n Rotina inicial de Setup \n ");
    digitalWrite(MotorALT_M2, LOW);
    digitalWrite(MotorALT_M1, LOW);
    digitalWrite(MotorALT_M0, HIGH);
    digitalWrite(MotorAZ_M2, LOW);
    digitalWrite(MotorAZ_M1, LOW);
    digitalWrite(MotorAZ_M0, HIGH);
  }
  setupflag = 2;

  SerialPrint(" \n O valor atual timer e: ");
  SerialPrint(String(MinTimer - 200));
  SerialPrint(" (:HST00000# -> Quanto menor mais rapido ate o limite do motor ambos motores) \n");
  delay(1000);

  SerialPrint(" \n O Sentido do motor RA/Alt e: ");
  if (SentidoRA == 0)
  {
    SerialPrint("Horario (:HSSRA0# -> Horario // :HSSRA1# -> AntiHorario)\n");
  }
  else
  {
    SerialPrint("Anti-Horario (:HSSRA0# -> Horario // :HSSRA1# -> AntiHorario)\n");
  }
  delay(1000);

  SerialPrint(" \n Acionamento do motor RA/ALT em velocidade maxima \n ");
  AzMotor.setSpeed(0);
  AltMotor.setSpeed(MinTimer * MinTimer);
  delay(6000);
  AltMotor.setSpeed(0);


  SerialPrint(" \n O Sentido do motor DEC/AZ e: ");
  if (SentidoDEC == 0)
  {
    SerialPrint("Horario (:HSSDEC0# -> Horario // :HSSDEC1# -> AntiHorario)\n");
  }
  else
  {
    SerialPrint("Anti-Horario (:HSSDEC0# -> Horario // :HSSDEC1# -> AntiHorario)\n ");
  }
  delay(1000);

  SerialPrint(" \n Acionamento do motor DEC/AZ em velocidade maxima \n ");
  AltMotor.setSpeed(0);
  AzMotor.setSpeed(MinTimer * MinTimer);
  delay(6000);
  AzMotor.setSpeed(0);

  AzMotor.setSpeed(0);
  AltMotor.setSpeed(0);
  SerialPrint(" \n Total da Relacao de engrenagens de RA/ALT: ");
  SerialPrint(String(MaxPassoAlt));
  SerialPrint(" (:HSAL0000000# -> reducao * numero passos * micropasso)\n");
  SerialPrint(" \n Total da Relacao de engrenagens de DEC/AZ: ");
  SerialPrint(String(MaxPassoAz));
  SerialPrint(" (:HSAZ0000000# -> reducao * numero passos * micropasso) \n");

  SerialPrint(" \n Para sair :HSETUPOFF# ");
  setupflag = 1;
}

void RotinadeSetupOff() //:HSETUPOFF#
{
  setupflag = 0;
}

