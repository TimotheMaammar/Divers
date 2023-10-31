// BLEU = 2
// VERT = 3 
// ORANGE = 4
// ROUGE = 5
// CAPTEUR = A0


#include <Adafruit_LiquidCrystal.h>

int sensorPin = A0;    // Entrée analogique
int ledPin2 = 2;       // Sortie 1
int ledPin3 = 3;       // Sortie 2
int ledPin4 = 4;       // Sortie 3
int ledPin5 = 5;       // Sortie 4

int sensorValue = 0;
int seconds = 0;

// Paliers de température à modifier
int palier1 = -15;
int palier2 = 0;
int palier3 = 15;
int palier4 = 30;

Adafruit_LiquidCrystal lcd_1(0);

// Instructions exécutées au démarrage de la simulation
void setup() 
{
  
  Serial.begin(9600);
  
  pinMode(ledPin2, OUTPUT);    
  pinMode(ledPin3, OUTPUT);     
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(A0, INPUT);
  
  lcd_1.begin(16, 2);
  lcd_1.print("Thermometre");
}

// Instructions exécutées après le démarrage
void loop()
{

  sensorValue = analogRead(sensorPin);

  Serial.println( sensorValue ) ;  
             
  if (sensorValue > palier1) digitalWrite(ledPin2, HIGH);
  else digitalWrite(ledPin2, LOW);  
  
  if (sensorValue > palier2) digitalWrite(ledPin3, HIGH);
  else digitalWrite(ledPin3, LOW);       
  
  if (sensorValue > palier3) digitalWrite(ledPin4, HIGH);
  else digitalWrite(ledPin4, LOW);
  
  if (sensorValue > palier4) digitalWrite(ledPin5, HIGH);
  else digitalWrite(ledPin5, LOW);
  
}
