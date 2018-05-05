//***************************************/
//Program 1 for generating sound using the tone function
//***************************************/
#define BEATTIME 200 //Length of the generated tone (msec)
#define SPEAKER 12 //Pin number of the speaker
void setup() {
}
void loop() {
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
}
