#include <AccelStepper.h>
#include <Arduino.h>
#include <math.h>
#include <Time.h>
#include <DueTimer.h>




//valores maximo para o encoder

//Criacao dos motores


#define MicroPassoAltpino 9
#define MicroPassoAzpino 5
#define DirAltpino 11
#define DirAzpino 7
#define PassoAltpino 10
#define PassoAzpino 6

AccelStepper AltMotor(AccelStepper::DRIVER, PassoAltpino, DirAltpino);
AccelStepper AzMotor(AccelStepper::DRIVER, PassoAzpino, DirAzpino);
int accel = 1;


//valores maximo para o passo (Valor ideal 1286400)
#define MaxPassoAlt 1906036  //valor de resolucao AR = Passo * MicroPasso * reducao ex(200*16*402)/4    (16*200*(117/11)*56)
#define MaxPassoAz 1906036  //valor de resolucao AR = Passo * MicroPasso * reducao ex(200*16*402)   (16*200*(118/11)*57)
#define MinTimer 150



int veloc;
unsigned long currentMillis, previousMillis = 0;
int sul = 0, leste = 0, oeste = 0, norte = 0;
// Location ----------------------------------------------------------------------------------------------------------------
double latitude  = -25.40;
double longitude = -49.20;
int UTC = 0;
int fractime;

//Variaveis de controle para ler comandos LX200  ----------------------------------------------------------------------------------------------------------------
boolean cmdComplete = false, doispontos = true; // whether the string is complete
char buffercmd[30];
char inputcmd[30];// a string to hold incoming data
int pontBuffer = 0;
int pontCommand = 0;
int numCommand = 0;



//Variaveis globais da MEADE
double SideralRate = 60.0; //HZ
int RAbacklash = 0; //(in ArcSec)
int DECbacklash = 0; //(in ArcSec)
//Variaveis globais de posição fisica do telescopio  ----------------------------------------------------------------------------------------------------------------
double eixoAltGrausDecimal = 0.0;
double eixoAzGrausDecimal = 0.0;
double RAmount = 0.0;
double DECmount = 0.0;
double AZmount = 0.0;
double ALTmount = 0.0;
double AZmountAlvo = 0.1;
double ALTmountAlvo = 0.1;




//Alvos a serem seguidos ou sincronizado
double RAAlvo = 0.0;
double DECAlvo = 0.0;
double AzAlvo = 0.0;
double AltAlvo = 0.0;
int statusmovimentacao = 0;
int ativaacom = 0;
int gotomount = 0;
//limites da montagem
int HorizonteLimite = 0;
int AltitudeLimite = 90;


void setup() {
  Timer3.attachInterrupt(acionamotor);
  Serial.begin(9600);
  Serial2.begin(9600);
  iniciapmotores();
  setTime(22, 00, 00, 23, 03, 2014);
  SerialPrint("00:00:00#"); //RTA para leitura do driver ASCOM da MEADE autostar I
  delay (200);
}



void loop() {
  currentMillis = millis();  
  CalcPosicaoPasso();

  // print the string when a newline arrives:
  // protegemount();
  if (ativaacom != 0)
  {
     setaccel();
     CalcPosicaoPasso();
     SetPosition();
     acompanhamento();
  }
}



