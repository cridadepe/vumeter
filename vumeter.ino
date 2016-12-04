#include <FreqMeasure.h>

#define NUM_PINS 5
int R[] = {2,5,17, 11, 14};
int G[] = {3,6,18, 12, 15};
int B[] = {4,7,19, 13, 0};

int red;
int green;
int blue;

int freqs[12][7] = {
  {65,131,262,523,1047,2090,4186},
  {69,139,277,554,1108,2217,4435},
  {73,147,294,587,1175,2349,4699},
  {78,156,311,622,1245,2489,4978},
  {82,165,330,659,1319,2637,5274},
  {87,175,349,699,1397,2794,5588},
  {93,185,370,740,1480,2960,5920},
  {98,196,392,784,1568,3136,6272},
  {104,208,415,831,1661,3322,6645},
  {110,220,440,880,1760,3520,7040},
  {117,233,466,932,1865,3729,7459},
  {124,247,494,988,1976,3951,7902}
};

int colores[12][3] = {
  {255,255,0},
  {0, 0, 255},
  {255,0,0},
  {0,152,116},
  {125,33,129},
  {0,255,0},
  {0,0,64},
  {255,164,32},
  {0,255,255},
  {195,16,58},
  {0,120,0},
  {80,0,80}
};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  for(int i = 0; i<NUM_PINS; i++){
    pinMode(R[i], OUTPUT);
    pinMode(G[i], OUTPUT);
    pinMode(B[i], OUTPUT);
  }
  FreqMeasure.begin();
  pinMode(A2, INPUT);
}

double sum=0;
int count=0;
int sample;

// the loop function runs over and over again forever
void loop() {

  sample = analogRead(A2);
  Serial.println(sample);

  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 25) {
      float frequency =  FreqMeasure.countToFrequency(sum / count);
      int color = determinarColor(frequency);
      red = colores[color][0];
      green = colores[color][1];
      blue = colores[color][2];
      int vol = random(1,6);
      volumen(vol);
      //Serial.println(frequency);
      sum = 0;
      count = 0;
    }
  }
  
}

int determinarColor(int freq){
  int fila = 0;
  int columna = 0;
  for(int i=0;i<7;i++){
    if(freq>freqs[0][i]){
      columna =i;
    }
  }
  for(int i=0;i<12;i++){
    if(freq>freqs[i][columna]){
      fila=i;
    }
  }
  return fila;
}

void volumen(int volumen){
  for(int i=0;i<volumen;i++){
    prender(i);
    delay(18);
  }
  delay(48);
  for(int i=4;i>=0;i--){
    apagar(i);
    delay(18);
  }
  delay(48);
} 

void prender(int posicion){
  analogWrite(R[posicion],red);
  analogWrite(G[posicion],green);
  analogWrite(B[posicion],blue); 
}

void apagar(int posicion){
  analogWrite(R[posicion],0);
  analogWrite(G[posicion],0);
  analogWrite(B[posicion],0); 
}
