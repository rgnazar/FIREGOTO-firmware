#include <AccelStepper.h>
#include <Arduino.h>
#include <math.h>
#include <Time.h>
#include <DueTimer.h>
#include <DueFlashStorage.h>

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


/*valores maximo para o passo (Valor ideal 1286400)
#define MaxPassoAlt 1906036  //valor de resolucao AR = Passo * MicroPasso * reducao ex(200*16*402)/4    (16*200*(117/11)*56)
#define MaxPassoAz 1906036  //valor de resolucao AR = Passo * MicroPasso * reducao ex(200*16*402)   (16*200*(118/11)*57)
#define MinTimer 150
// Location ----------------------------------------------------------------------------------------------------------------
double latitude  = -25.40;
double longitude = -49.20;
int UTC = 0;
setTime(22, 00, 00, 23, 03, 2014);
*/


DueFlashStorage dueFlashStorage;

// The struct of the configuration.
struct Configuration {
  int32_t MaxPassoAlt;
  int32_t MaxPassoAz;
  int32_t MinTimer;
  uint32_t DataHora;
  double latitude;
  double longitude;
  int32_t UTC;
  char* Local;
};
Configuration configuration;
Configuration configurationFromFlash; // create a temporary struct


int MaxPassoAlt;
int MaxPassoAz;
int MinTimer;
double latitude;
double longitude;
int UTC;



int fractime;
unsigned long currentMillis, previousMillis, PCommadMillis, calculaRADECmountMillis = 0;


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
int AtivaBack = 1;
int dirAlt, dirAz, dirAltant, dirAzant;

//Variaveis globais de posiÃ§Ã£o fisica do telescopio  ----------------------------------------------------------------------------------------------------------------
double eixoAltGrausDecimal = 0.0;
double eixoAzGrausDecimal = 0.0;
double ResolucaoeixoAltGrausDecimal = 0.0;
double ResolucaoeixoAzGrausDecimal = 0.0;
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
double ErroAlt = 0.0;
double ErroAz = 0.0;


int statusmovimentacao = 0;
int ativaacom = 0;
int gotomount = 0;
//limites da montagem
int HorizonteLimite = 0;
int AltitudeLimite = 90;

//Ajuste fino do tempo
int Segundo;
double Microssegundo = 0 , SegundoFracao = 0.0, MilissegundoSeg = 0.0, MilissegundoI = 0.0;



void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  /* Flash is erased every time new code is uploaded. Write the default configuration to flash if first time */
  // running for the first time?
  uint8_t codeRunningForTheFirstTime = dueFlashStorage.read(0); // flash bytes will be 255 at first run
  Serial.print("Primeira Execucao: ");
  if (codeRunningForTheFirstTime) {
    Serial.println("yes");
    /* OK first time running, set defaults */
    configuration.MaxPassoAlt = 1856000;
    configuration.MaxPassoAz = 1856000;
    configuration.MinTimer = 180;
    configuration.latitude = -25.40;;
    configuration.longitude = -49.20;
    setTime(22, 00, 00, 23, 03, 2015);
    MilissegundoSeg = second();
    configuration.DataHora = now();
    configuration.UTC = 0;
    configuration.Local = "Minha Casa";
    // write configuration struct to flash at adress 4
    byte b2[sizeof(Configuration)]; // create byte array to store the struct
    memcpy(b2, &configuration, sizeof(Configuration)); // copy the struct to the byte array
    dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
    // write 0 to address 0 to indicate that it is not the first time running anymore
    dueFlashStorage.write(0, 0);
  }
  else {
    Serial.println("no");
  }
  byte* b = dueFlashStorage.readAddress(4); // byte array which is read from flash at adress 4
  memcpy(&configurationFromFlash, b, sizeof(Configuration)); // copy byte array to temporary struct
  MaxPassoAlt = configurationFromFlash.MaxPassoAlt;
  MaxPassoAz = configurationFromFlash.MaxPassoAz;
  MinTimer = configurationFromFlash.MinTimer;
  latitude = configurationFromFlash.latitude;
  longitude = configurationFromFlash.longitude;
  UTC = configurationFromFlash.UTC;
  setTime(configurationFromFlash.DataHora);
  iniciapmotores();
  SerialPrint("00:00:00#"); //RTA para leitura do driver ASCOM da MEADE autostar I
  delay (200);
  previousMillis = millis();
  PCommadMillis = previousMillis;
  ErroAlt = ErroAz = 44.0;
  ResolucaoeixoAltGrausDecimal = 360.0 / MaxPassoAlt ;
  ResolucaoeixoAzGrausDecimal = 360.0 / MaxPassoAz ;
}



void loop() {
  currentMillis = millis();
  CalcPosicaoPasso();
  if (PCommadMillis < currentMillis)
  {
    PrintLocalHora();
    Serial.println(String(Hora2DecHora(hour(), minute(), SegundoFracao), 10)) ;
    PCommadMillis = PCommadMillis + 1497;
  }

  if (calculaRADECmountMillis < currentMillis)
  {
    calculaRADECmountMillis = calculaRADECmountMillis + 500;
    calculaRADECmount();
  }



  // print the string when a newline arrives:
  // protegemount();
  if (ativaacom != 0)
  {
    if (previousMillis < currentMillis)
    {
      setaccel();
      previousMillis = previousMillis + 200;
    }
    SetPosition();
    acompanhamento();
  }
  else
  {
    previousMillis = millis();
  }


}




