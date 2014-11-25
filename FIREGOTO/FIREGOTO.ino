

#include <Arduino.h>
#include <math.h>
#include <Time.h>
#include <DueTimer.h>




//valores maximo para o encoder

//Criacao dos motores


#define MicroPassoAltpino 5
#define MicroPassoAzpino 9
#define DirAltpino 7
#define DirAzpino 11
#define PassoAltpino 6
#define PassoAzpino 10
#define MinTimer 47

//valores maximo para o passo (Valor ideal 1286400)
#define MaxPassoAlt 1286400  //valor de resolucao AR = Passo * MicroPasso * reducao ex(200*16*402)/4
#define MaxPassoAz 1286400  //valor de resolucao AR = Passo * MicroPasso * reducao ex(200*16*402)

int veloc;
int currentMillis, previousMillis;
int sul = 0, leste = 0, oeste = 0, norte = 0;


// Location ----------------------------------------------------------------------------------------------------------------
double latitude  = -25.40;
double longitude = -49.20;
int UTC = 0;

//Variaveis de controle para ler comandos LX200  ----------------------------------------------------------------------------------------------------------------
boolean cmdComplete = false, doispontos = true; // whether the string is complete
char buffercmd[20];
char inputcmd[20];// a string to hold incoming data
int pontBuffer = 0;
int pontCommand = 0;
int pontBufferold = 0;


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
double AZmountAlvo = 0.0;
double ALTmountAlvo = 0.0;


//PID Variaveis
float Palt = 0, Paz = 0;
float Ialt = 0, Iaz = 0;
float Dalt = 0, Daz = 0;
float Accelalt = MaxPassoAlt, Accelaz = MaxPassoAz;
float kP = 1;
float kI = 0;
float kD = 0;
double erroaltprevious, erroalt, erroazprevious, erroaz, PIDalt=0, PIDaz=0;
double intervalpid = millis();
double timerpid = millis();
double intervalpulseaz = intervalpid, intervalpulsealt = intervalpid;
double tt=100;


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
  Timer3.attachInterrupt(acionamotor);  // initialize serial:
  Serial.begin(9600);
  Serial2.begin(9600);
  iniciapmotores();
  CalcPosicaoPasso();
  setTime(22, 00, 00, 23, 03, 2014);
  SerialPrint("00:00:00#"); //RTA para leitura do driver ASCOM da MEADE autostar I
  delay (200);
}



void loop() {
  PIDCalc();
  CalcPosicaoPasso();
  // print the string when a newline arrives:
 // protegemount();
  if (ativaacom != 0)
  {
    acompanhamento();
  }
  else
  {
    movimentamotor();
  }
  if (cmdComplete) {
    executecommand();
    inputcmd[1] = 'Y';
  } else
  {
    lebuffercomand();
  }
}



