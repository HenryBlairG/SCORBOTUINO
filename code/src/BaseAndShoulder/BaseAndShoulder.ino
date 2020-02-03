#include <Servo.h>

/*
Motor Variables
*/
byte     pinMotorBase = 11;  
byte pinMotorShoulder = 6;

Servo mBase, mShoulder;


/*
Encoder Variables 
*/
volatile double     encBaseCount = 0;
volatile double encShoulderCount = 0;
byte                    pinABase = 9;
byte                    pinBBase = 8;
byte                pinAShoulder = 4;
byte                pinBShoulder = 3;

volatile int chAStateBase, chALastStateBase, chAStateShoulder, chALastStateShoulder;

/*
Home Switches
*/
byte                  pinHomeBase = 10;
byte              pinHomeShoulder = 5;

volatile int homeBaseSet, homeShoulderSet, homeBase, homeShoulder;

/*
PID Variables
*/
 
unsigned long currentTime, previousTime;
double elapsedTime;
double lastErrorBase, lastErrorShoulder;
double setPntBase, setPntShoulder;
double errorBase, errorShoulder, cumErrorBase, rateErrorBase, cumErrorShoulder, rateErrorShoulder;

/*
Utility Variables
*/
int baseRange[2] = {5, 180};
int shoulderRange[2] = {};
int motorDemo = 0;


void setup() { // put your setup code here, to run once:
  Serial.begin(9600);
  
  /*
  Base SetUp
  */
  pinMode(   pinBBase, INPUT);
  pinMode(   pinABase, INPUT);
  pinMode(pinHomeBase, INPUT);
  mBase.attach(pinMotorBase, 1000, 2000);

  chALastStateBase = digitalRead(pinABase);

  /*
  Shoulder SetUp
  */
  pinMode(   pinBShoulder, INPUT);
  pinMode(   pinAShoulder, INPUT);
  pinMode(pinHomeShoulder, INPUT);
  mShoulder.attach(pinMotorShoulder, 1000, 2000);

  chALastStateShoulder = digitalRead(pinAShoulder);

  /*
  PID SetUp
  */
  setPntBase = 30;
  setPntShoulder = 30;
  get_home_base();
  get_home_shoulder();
}

void loop() {
  if(motorDemo){
    int power;  // Demo obtenido de Pagina de SaberTooth
    for (power = 0; power <= 90; power ++){
      delay(20);
      mBase.write(power);
      mShoulder.write(power);  
    }
    // Now go back the way we came.
    for (power = 90; power >= 0; power --){
      mBase.write(power);
      mShoulder.write(power);
      delay(20);
    }
  }  
  for(int axis=1; axis <= 2; axis++){
    scorbot_update(axis);
    }
  Serial.println("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
  Serial.println(encBaseCount);
  Serial.println("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSssSS");
  Serial.println(encShoulderCount);
}


void enc_base(){
  chAStateBase = digitalRead(pinABase);
  if(chAStateBase != chALastStateBase){
    if(digitalRead(pinBBase) != chAStateBase) encBaseCount++;
    else encBaseCount--;
  }
  chALastStateBase = chAStateBase;
}

void home_base(){
  homeBase = (digitalRead(pinHomeBase) == HIGH)? 1 : 0;
}

void get_home_base(){
  home_base();
  int counter = 0;
  while(!homeBase && counter < 2000000){
    mBase.write(0);
    delay(10);
    home_base();
    counter++;
  }
  counter = 0;
  while(!homeBase && counter < 2000000){
    mBase.write(180);
    delay(10);
    home_base();
    counter++;
  }
  delay(250);
  mBase.write(90);
  encBaseCount = 0;
}


void enc_shoulder(){
  chAStateShoulder = digitalRead(pinAShoulder);
  if(chAStateShoulder != chALastStateShoulder){
    if(digitalRead(pinBShoulder) != chAStateShoulder) encShoulderCount++;
    else encShoulderCount--;
  }
  chALastStateShoulder = chAStateShoulder; 
  }

void home_shoulder(){
  homeShoulder = (digitalRead(pinHomeShoulder) == HIGH)? 1 : 0;
}

void scorbot_update(int arm){
  switch(arm){
    case 1:
      home_base();
      enc_base();
      mBase.write(scorbot_pid(1));
      break;
    case 2:
      home_shoulder();
      enc_shoulder();
      mShoulder.write(scorbot_pid(2));
      break;
    default:
      break;
  }
}

void get_home_shoulder(){
  home_shoulder();
  int counter = 0;
  while(!homeShoulder && counter < 2000000){
    mShoulder.write(0);
    delay(10);
    home_shoulder();
    counter++;
  }
  counter = 0;
  while(!homeShoulder && counter < 2000000){
    mShoulder.write(180);
    delay(10);
    home_shoulder();
    counter++;
  }
  delay(250);
  mShoulder.write(90);
  encShoulderCount = 0;
}

int scorbot_pid(int arm){
  int out;
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime); 
  switch(arm){
    case 1:  // Para la base
      double kpBase = .2;  // TODO: Por definir
      double kiBase = .5;
      double kdBase = .1;

      errorBase = setPntBase - encBaseCount;                    // Proporcional
      cumErrorBase += errorBase * elapsedTime;                   // Integral
      rateErrorBase = (errorBase - lastErrorBase)/elapsedTime;  // Derivativo

      out = (int) (kpBase * errorBase + kiBase * cumErrorBase + kdBase * rateErrorBase);  // PID
      if(out > 90) out = 90;
      else if(out < -90) out = -90;
      lastErrorBase = errorBase;
      break;
    case 2:  // Para el hombro
      double kpShoulder = .2;  // TODO: Por definir
      double kiShoulder = .5;
      double kdShoulder = .1;

      errorShoulder = setPntShoulder - encShoulderCount;                    // Proporcional
      cumErrorShoulder += errorShoulder * elapsedTime;                   // Integral
      rateErrorShoulder = (errorShoulder - lastErrorShoulder)/elapsedTime;  // Derivativo

      out = (int) (kpShoulder * errorShoulder + kiShoulder * cumErrorShoulder + kdShoulder * rateErrorShoulder);  // PID
      if(out > 90) out = 90;
      else if(out < -90) out = -90;
      lastErrorShoulder = errorShoulder;
      break;
    case 3:  // Para el Codo
      break;
    case 4:  // Para la muñeca
      break;
    case 5:  // Para el Roll de la muñeca
      break;
    case 6:  // Para la pinza
      break;
    case 7:  // Para la Rampa
      break;
    default: // Para cualquier otro caso
      break;
    }
  previousTime = currentTime;
  return out + 90;
  }
