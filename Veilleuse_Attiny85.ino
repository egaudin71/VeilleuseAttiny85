/* Attiny85 led pour veilleuse

*/
/*
  int Rouge = 0; // pin 5
  int Vert = 1;//pin 6
  int Bleu = 2;// pin 7
*/


#define ROUGE 2 // pin 7 NUMERIC
#define VERT 1//pin 6 PWM
#define BLEU 0// pin 5 PWM
#define BRUIT 3 // pin 2
#define BRUIT_LEVEL 2 // pin3
#define timedealy 50

int x = 0;
int xmax = 128;
int increment = 2;
int valbruit = 0;
int valseuil = 0;
int SeuilBruit = 400;


void setup() {

  pinMode(ROUGE, OUTPUT);
  pinMode(VERT, OUTPUT);
  pinMode(BLEU, OUTPUT);

}

void loop() {

  valseuil = analogRead(BRUIT_LEVEL);
  valbruit = analogRead(BRUIT);
  if (valbruit > valseuil) {

    for (x = 0 ; x < xmax; x += increment) {
      digitalWrite(ROUGE, HIGH);
      analogWrite(BLEU, x);
      delay(timedealy);
      analogWrite(VERT, x);
      //digitalWrite(ROUGE, HIGH);
      delay(timedealy);
    }
    for (x = xmax ; x > 0; x -= increment) {
      digitalWrite(ROUGE, HIGH);
      analogWrite(BLEU, x);
      delay(timedealy);
      analogWrite(VERT, x);
      //digitalWrite(ROUGE, HIGH);
      delay(timedealy);
    }
  }
  else {
    digitalWrite(ROUGE, LOW);
    analogWrite(BLEU, 0);
    analogWrite(VERT, 0);
  }

}
