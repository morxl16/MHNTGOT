/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_Fingerprint.h>
#include "Servo.h"

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
#include <SoftwareSerial.h>
#define BEATTIME 200 //Length of the generated tone (msec)
#define SPEAKER 12 //Pin number of the speaker
#define LED_DELAY 3 //The delay between the led (msec)
Servo myservo;
int speakerPin = 12;
int greenLed = 11;
int redLed = 10;
int electricPin = 4;
int servopin = 5;
int length = 15; // the number of notes
char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
const int tempo = 200;
boolean electricityStatus = false;



SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  //chargeElectrcity(electricPin);
  stopElectrcity(electricPin);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    //stopElectrcity(electricPin);
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
 pinMode(speakerPin, OUTPUT);
 pinMode(greenLed, OUTPUT);
 pinMode(redLed, OUTPUT);
 pinMode(electricPin, OUTPUT);
 pinMode(servopin, OUTPUT);

}

void loop()                     // run over and over again
{
  myservo.attach(servopin);
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match
  tone(SPEAKER,262,BEATTIME) ; // Do
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)
  {
    //this shty function always runs
    return -1;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
  {
    Serial.print("Not found #2 \n");
    tone(SPEAKER,330,BEATTIME) ; // Mi
    delay(BEATTIME) ;
    tone(SPEAKER,330,BEATTIME) ; // Mi
    delay(BEATTIME) ;
    return -1;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
    Serial.print("Not found #3 \n");
//    tone(SPEAKER,330,BEATTIME) ; // Mi
//    delay(BEATTIME) ;
//    tone(SPEAKER,330,BEATTIME) ; // Mi
//    delay(BEATTIME) ;
    dimLedHighest(redLed);
    Serial.print("Light started \n");
    start(); 
    dimLedLowest(redLed);
    Serial.print("Light stopped \n");    
    return -1;
  }
  
  // found a match!
  dimLedHighest(greenLed);
  tone(SPEAKER,262,BEATTIME) ; // Do  
  delay(BEATTIME) ;
  tone(SPEAKER,294,BEATTIME) ; // Re
  delay(BEATTIME) ;
  tone(SPEAKER,330,BEATTIME) ; // Mi
  delay(BEATTIME) ;
  tone(SPEAKER,349,BEATTIME) ; // Fa
  delay(BEATTIME) ;
  tone(SPEAKER,392,BEATTIME) ; // So
  delay(BEATTIME) ;
  tone(SPEAKER,440,BEATTIME) ; // La
  delay(BEATTIME) ;
  tone(SPEAKER,494,BEATTIME) ; // Si
  delay(BEATTIME) ;
  tone(SPEAKER,523,BEATTIME) ; // Do
  delay(BEATTIME) ;
  dimLedLowest(greenLed);
  
  
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}



//////////////////////////////////////////////////////////

void chargeElectrcity(int pinNumber){
  Serial.print("##charge electricity \n");
  electricityStatus = true;
//  digitalWrite(pinNumber, HIGH);
//  analogWrite(pinNumber, 20);
}

void stopElectrcity(int pinNumber){
  Serial.print("##stop electricity \n");  
  electricityStatus = false;
//  digitalWrite(pinNumber, LOW);
//  analogWrite(pinNumber, 1);
}

void dimLedHighest(int pinNumber){
  int i=0;
  for(;i<=255;i++){
    delay(LED_DELAY);
    analogWrite(pinNumber, i);
  }
  digitalWrite(pinNumber, HIGH);
}

void dimLedLowest(int pinNumber){
  for(int i=255;i>=0;i--){
    delay(LED_DELAY);
    analogWrite(pinNumber, i);
  }
}

void start(){
  int temp_tempo = tempo;
  for ( int j=0; j<3; j++){
  temp_tempo -= 50;   
 
   for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
          delay(beats[i] * temp_tempo); // rest
        } else {
          playNote(notes[i], beats[i] * temp_tempo);
        }
    
    // pause between notes
    delay(temp_tempo / 2); 
        if (j==2 && i==(length-2)){
        Serial.print("Electricity started \n");        
        StartAndStopElectricity(5000);
        Serial.print("Electricity Stopped \n");    
        }
    }
    
  }
  
}



void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void StartAndStopElectricity(int sleep){
//  myservo.write(0);  // set servo to starting-point
//  Serial.print("##init servo location \n");
  delay(100);
  myservo.write(0);  // set servo to starting-point
  Serial.print("##change servo location \n");  
  delay(sleep);
  myservo.write(90);  // set servo to mid-point
  Serial.print("##finished servo movement \n");  
}





