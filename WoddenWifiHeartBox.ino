#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>  // include library for real-time clock module
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino resetpin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int maxLength = 63;

int motorPin = 5;
int ledPin = 2;
int switchPin = 12;  // digital input pin for magnetic switch
int buttonPin = 27;
bool runProt1 = false;

int waitTime = 3600000000;//3600000000//10*1000000

RTC_DS1307 rtc;  // create object for real-time clock module
char *stringMorningBank[] = {"Buenos dias mi amor <3, te amo", "OOOLLLAAAA BounGioRnO", "Pov: hoy tendras una mana bonita", "Ojala sea sabado hoy", "BONISHAAAAAAA, primer mensaje del dia :)", "teee quierroooo y amo, gud morning", "Buenos dias Rafaela - 'la caja de madera 2023'", "WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOW buenos dias ;p", "un nuevo dia bonito para la mas bonita"};
char *stringBank[] = {"te amo","Hola Mi amor!!!!! Te amo mucho, espero que tu dia te este llendo hermoso hoy :)",
"Olaaaa sabes, creo que tu eres la mas hermosa de este mundo",
"MIII RAFIIIIIIIIIIIIII.......   Teamo jeje",
"Que le dijo un enamorado al otro? . . . TEAMOMAS... ja ja ja. no enserio, te amo mas",
"HEyeyYyYyYyy, no se cuando vas a leer esto... PEROOOOO espero que tu dia sea hermoso hoy",
"Today is a good day :)",
"Amor, eres mi amor JAJAJAJAJA",
"ERROR ERROR ERROR: jk no hay ningun error, jeje TE AMO",
"Historia 1: Sabes cuando primero te vi en nuestro primer date, recuerdo que lo que primero me di cuenta era de lo pequenita que eras jejeje",
"Creo que despues de escribir todas estos mensajes voy a aver escrito mas que un essay jejeje, Pof tu nobio es un English Major",
"Se que esto te pueda parecer un toque cringie, pero enverdad eres mi mundo entero (^^)'",
"'(^^)'-[<3] !",
"OLAAAAAA",
"OLAAAAA espero que hoy tengas un dia hermoso :)",
"Oyeee, pero si no es mi nobia la mas sexc, intelligente, hermosa, prechiosa, carinosa, amadora, suave, rica, hermosa, preciosa, y prefecta ;) wachu up too?",
"Knock Knock, buenos DIAS BONISHAAA!!!!!!!!!!",
"qUE ORA ES? hmmmmmmm SON LAS TE AMO EN PUNTO ;0",
"SABES te amo mucho, Y espero que este mensaje te haga el dia hoy :D!!!!!!",
"IlobeuMore<3",
"bONISHAAA bonishaaaa, te amo :))))",
"*Historia 1* Jejeje sabias que cuando primero te conosi en nuestro primer date, lo que primero me di cuenta es de lo pequene que eras jejeje",
"AMORRRRRRRR BESAMEEE",
"olaaaAAA bonisha!!! Si vees esto llamame :)",
"*CUPON 1* UN SOLO USO: Mandame este numero en txt 1223443ASDWRERF343",
"*cOOL FACT* Buenossss diasss prechiosa, sabias que yo te amo mas ;)... no?! bueno ahora sabes jeje",
"Ding Dong! Es un mensaje: Espero que hoy tengas un dia hermoso :3",
"WOOOOOOOOOOOOOOOF... perdon, Coco queria que te mandare eso.. se supone que dice OLA? who knows jeje",
"BONISAHAasasdhsdiufhwieufdywyefdghhjd, llamame ;)",
"*Historia 2* Ya conoses esta, pero yo trate de verte a los labios como millll veces en nuestras primeras dates para ver si me besabas JAJAJAAJ",
"DIIINGGGDONGGGG ES TU BONISHO MANDANOTE UN BESO!!! SUERTE HOYYYY",
"Ola amor :) Nose que pasa hoy, pero siento que este mensaje va a salir cuando mas nessesites. You got this <3 te amo",
"*CUPON 2* MANDAME UN TEXTO QUE DICE 'JAJAJA GANE' y vamos a salir al restaurante de tuy choice, yo invito ;)",
"*Cupon TRESSS* Secreto jejejeje, ;0 mandame una foto de este mensaje si lo haces rapido ganas una sorpresa especial",
"*Historia 3* No te voy a mentir, tu comida es divina, de verdad divina y me enamora... PERO tu hot chocolate sabe a agua JEJEJE TE AMO AMOR",
"OLAAAAAAAAAAAAAAAAAAAAA, HOY ES TU DIA D ELA SUERTE! HAVE FUNNNN",
"Ola bonisha, te extrano :)",
"Te amo <3",
"*Historia 4* sabes, tienes suerte que no pueda poner emojies aqui, sino WOw, lo llenaria con emojies jeje",
"pob tu nobio te programo esto para decirte que te quiero y ama mucho, mandale una foto de ti, te extrana probablemente",
"*Historia 5* Esta es para que no te olvides que te tiraste dos pedos la primera noche que dormimos juntos, la primera jejeje",
"Espero que este mensaje salga bien porque TE AMOOOOOOOOOOOOOO",
"FELIZZZZZ DIAAAAAAAAAAAAAAAAA WOOOWWWWW",
"Pob, llamame si quieres que ponga mas mensajes jejejej",
"*CUPON 4* foto sexc gratis cuando quiera jejeje ;)",
"RAFIIIIIIIIIII, te amo jejeje espero que tengas un hermoso dia",
"Besame",
"te adoro",
"mi hermosa",
"te amo MASSSS",
"BONISHAAA ATRAPE A COCO AQUI MIRA *WROOOOFWROOOF*...ronca, send help",
"Pob estoy atrapado aqui, te amo, help, jejeje jkjk",
"abrazme ",
"TAMQNEEMYQBYAPTLNAQNQD",
"Sabias que te estoy escribiendo todo esto Enero 1, jejeje te amo amor y siempre te amare",
"OLAAAAA BELLLAAAAAA dame un bethzo :3",
"<Te amo mas3",
"<<<<<<<33333333333333",
"Quiero decirte que te amo ",
"OLAAAA MI REINA, TEN UN HERMOSO DIA",
"I love you more :)<3"};



void setup()
{
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  //Wire.begin(21, 22);
  delay(4000);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer.
  display.clearDisplay();
  displayMessage("");
  delay(2000); 
  display.clearDisplay();
  delay(2000);

  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);  // set digital input pin for magnetic switch as input
  //pinMode(buttonPin, INPUT);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterruptHandler2, CHANGE);
  
  firstTurnTest(8900);
  turnLedOn();
  delay(200);
  turnLedOff();

  // Initialize real-time clock module
  //Wire.begin(18, 19); 
  
}
void loop() {
  // Check if the box is closed
  bool isClosed = digitalRead(switchPin);
  
  Serial.println(isClosed);
  
//  if(runProt1 == true){
//    receivedMessage();
//    chooseMsg();
//    runProt1 = false;
//  }
  while(!isClosed){
    
    isClosed = digitalRead(switchPin);
    turnLedOn();
    delay(2000);
    turnLedOff();
    delay(1000);
    displayMessage("hola! porfavor cierrame :)");
    Serial.println(isClosed);

    Serial.println("DENTRO DE LOOOOPP");///////////////////////
  }
  turnLedOn();
  delay(200);
  turnLedOff();
  delay(100);
  turnLedOn();
  delay(200);
  turnLedOff();
  delay(100);
  turnLedOn();
  delay(200);
  turnLedOff();
  delay(100);
  Serial.print("EXITED BOX");//////////////////////////////////////
  // Get the current time from the real-time clock module
  DateTime now = rtc.now();
  Serial.println(now.hour());
  // Check if it is currently between 11pm and 11am
  if (now.hour() < 11 || now.hour() >= 23) {//now.hour() < 11 || now.hour() >= 23
    // Go to deep sleep and do not do anything
    
    Serial.println("DENTRO DE relojWait");///////////////////////
    
    display.setCursor(0, 5);
    display.println("");//63
    display.display();
    ESP.deepSleep(waitTime);
  }else{
      if(now.hour() <= 12 && now.hour() >= 10){
        displayAndCheckMorning(now.day());
      }
      // Generate a random number between 0 and 100
      int r = random(0, 100);
    
      // If the random number is less than 25, enter "received message mode"
      if (r < 10) {
            // Turn on the motor for 7 seconds
    Serial.println("DENTRO DE recievbed message ");///////////////////////
        EEPROM.write(199, now.day());
        receivedMessage();
        chooseMsg();
        displayMessage("Ningun mensaje por ahora, vuelve luego!");
        ESP.deepSleep(waitTime);
      }else{//missed

//        if(now.hour() > 21 || now.hour() < 24){//emergencyR
//          emergencyR(now.day());
//        }
        displayMessage("Ningun mensaje por ahora, vuelve luego!");
        Serial.println("DENTRO DE esperafinal ");///////////////////////
        delay(100);
        ESP.deepSleep(waitTime);
        

      }

  }//else
}//loop

void emergencyR(int dayy){

    if( EEPROM.read(199) != dayy){

      receivedMessage();
      chooseMsg();
    }

  return;
}
void displayAndCheckMorning(int dayy){//now.day()

  if( EEPROM.read(200) != dayy){
    
    EEPROM.write(200, dayy);
    receivedMessage();
    morningRoutine();
    return;
  }else{
    return;
  }
}//displayAndCheckMorning

void morningRoutine(){

  String msg = "";
  int r = random(0,10);

  displayMessage(stringMorningBank[r]);
  delay(40000);
  
  displayMessage(msg);
}//morningRoutine

void receivedMessage(){
unsigned long startTime = millis();
unsigned long currentMillis = startTime;
turnLedOn();
while(digitalRead(switchPin)){

  currentMillis = millis();
  if( (currentMillis - startTime) >= 120000){
  turnMotorOn();
  
  delay(8900);
  turnMotorOff();
  
  }else{
    startTime = currentMillis;
   
  }//timeLoop
  


  
}//while

turnLedOn();
delay(100);
turnLedOff();
delay(100);
turnLedOn();
delay(50);
turnLedOff();


  
}

void turnMotorOn(){
  digitalWrite(motorPin, HIGH);
}//turnMotorOn

void turnMotorOff(){
  digitalWrite(motorPin, LOW);
}//turnMotorOff

void turnLedOn(){
  digitalWrite(ledPin, HIGH);
}//turnLedOn
void turnLedOff(){
  digitalWrite(ledPin, LOW);
}//turnLedOff

void firstTurnTest(int timeMilli){
  turnMotorOn();
  delay(timeMilli);
  turnMotorOff();
}

void displayMessage(String msg){
  display.setTextSize(1);//AT SIZE 2 UPTO J, AT SIZE 1 3 T
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  int lengthh = msg.length();


  
  String message = "";
  if (lengthh > maxLength){
    int amounts = (lengthh/63) - 1;
    int count = 0;
    
    for(int i = 0; i < amounts; i++){
      count = i;
      message = msg.substring(63*i, (63 + (63*i)) );
      display.clearDisplay();
      display.println(message);//63
      display.display();

      delay(6000);
      display.setCursor(0, 5);
    }
    message = msg.substring((63 + (63*count)) );
    display.clearDisplay();
    display.setCursor(0, 5);
    display.println(message);//63
    display.display();
    delay(6000);
    
  }else{
    display.clearDisplay();
    display.println(msg);
    display.display();
  }
}

void chooseMsg(){
  int r = chooseNum();
  insertToMem(r);

  displayMessage(stringBank[r]);
  delay(40000);
  
}

int chooseNum(){

  int num = random(1,60);
  clearProt();
  for(int i = 0; i < 512; i++){
    if(EEPROM.read(i) == num){
      return num = chooseNum();
      
    }
  }//for
  return num;
}//chooseNum

void clearProt(){
   int count = 0;
   for(int i = 0; i < 512; i++){
    int red = EEPROM.read(i);

    if(red != 0){
      count = count + 1;
    }
  }

  if(count >= 59){
    eraseEEPROM();
  }

  
}//clearProt
void insertToMem(int num){
  for(int i = 0; i < 512; i++){
    int red = EEPROM.read(i);

    if(red == 0){
      
    }else{
      EEPROM.write(i, num);
      return;
    }
  }
}

void buttonInterruptHandler() {
  receivedMessage();
  chooseMsg();
}
void buttonInterruptHandler2() {
  runProt1 = true;
  loop();
}
void eraseEEPROM(){


  for (int i = 0; i < 512; i++) {
 EEPROM.write(i, 0);
 }
EEPROM.commit();
delay(500);
}
