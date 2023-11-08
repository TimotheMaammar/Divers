// Projet IOT101 - Timothé MAAMMAR
// Véhicule à deux roues motrices qui avance et évite des obstacles

// Ressources : 
//  https://www.tinkercad.com/things/21wkkOyuRIS 
//  https://www.tinkercad.com/things/2DWqYHClSqc-utilisation-du-capteur-de-distance 
//  https://www.tinkercad.com/things/7HT6gZ2NhGp-capteur-de-distance-par-ultrasons-ecran-lcd 
//  https://www.tinkercad.com/things/4ffwTzW9TRm-6-2-capteur-infrarouge-passif 
//  https://www.tinkercad.com/embed/gujZgO1X9Ur

// ==================================================
// Partie capteurs

// Ultrasons
long readUltrasonicDistance(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);

  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);

  return pulseIn(pin, HIGH);
}

// Infrarouge
int infrarouge = 2;
int valeur = -1;
// ==================================================



// ==================================================
// Partie voiture 

int Droite_IO = 3;
int Gauche_IO = 6;
int Droite_I = 5;
int Droite_O = 4;
int Gauche_I = 8;
int Gauche_O = 7;

// Cette fonction sert aussi à freiner si on passe 0 en argument
void avancer(int vitesse) {
  Serial.print("Avancer à ");
  Serial.print(vitesse);
  Serial.println(" KMH");

  vitesse = map(vitesse, 0, 100, 0, 255);
  analogWrite(Droite_IO, vitesse);
  analogWrite(Gauche_IO, vitesse);
  digitalWrite(Droite_I, HIGH);
  digitalWrite(Droite_O, LOW);
  digitalWrite(Gauche_I, HIGH);
  digitalWrite(Gauche_O, LOW);
}

void reculer(int vitesse) {
  Serial.print("Reculer à ");
  Serial.print(vitesse);
  Serial.println(" KMH");

  vitesse = map(vitesse, 0, 100, 0, 255);
  analogWrite(Droite_IO, vitesse);
  analogWrite(Gauche_IO, vitesse);
  digitalWrite(Droite_I, LOW);
  digitalWrite(Droite_O, HIGH);
  digitalWrite(Gauche_I, LOW);
  digitalWrite(Gauche_O, HIGH);
}

void tournerADroite(int vitesse) {
  Serial.println("Tourner à droite");
  vitesse = map(vitesse, 0, 100, 0, 255);
  analogWrite(Droite_IO, vitesse);
  analogWrite(Gauche_IO, 0);
  digitalWrite(Droite_I, HIGH);
  digitalWrite(Droite_O, LOW);
  digitalWrite(Gauche_I, LOW);
  digitalWrite(Gauche_O, LOW);
}

void tournerAGauche(int vitesse) {
  Serial.println("Tourner à gauche");
  vitesse = map(vitesse, 0, 100, 0, 255);
  analogWrite(Droite_IO, 0);
  analogWrite(Gauche_IO, vitesse);
  digitalWrite(Droite_I, LOW);
  digitalWrite(Droite_O, LOW);
  digitalWrite(Gauche_I, HIGH);
  digitalWrite(Gauche_O, LOW);
}
// ==================================================



// ==================================================
// Partie simulation

// Instructions exécutées au démarrage
void setup() {
  Serial.begin(9600);
  pinMode(Droite_IO, OUTPUT);
  pinMode(Droite_I, OUTPUT);
  pinMode(Droite_O, OUTPUT);
  pinMode(Gauche_IO, OUTPUT);
  pinMode(Gauche_I, OUTPUT);
  pinMode(Gauche_O, OUTPUT);
}

// Instructions exécutées en continu
void loop() {
  scenario2();
}

// ==================================================



// ==================================================
// Scénarios de test 

void scenario1() {

  // On avance tant que le capteur à ultrasons ne détecte pas d'obstacle
  // Si on détecte un obstacle, on tourne jusqu'à ce que le capteur à ultrasons ne détecte plus de présence
  // Valeur 19 000 mesurée en faisant des tests sur le capteur

  while (readUltrasonicDistance(A5) > 19000) {
    avancer(50);
  }

  Serial.println("OBSTACLE DÉTECTÉ");
  // Si on sort de la première boucle, c'est qu'un obstacle a été détecté
  avancer(0);
  delay(10);

  while (readUltrasonicDistance(A5) < 19000) {
    tournerAGauche(30);
  }

  avancer(0);
  delay(10);
}



void scenario2() {

  valeur = digitalRead(infrarouge);

  // On recule tant que le capteur infrarouge ne détecte pas d'obstacle
  // Si on détecte un obstacle, on tourne jusqu'à ce que le capteur ne détecte plus de présence
  // Le capteur infrarouge vaut 0 si il ne détecte rien et 1 si un obstacle entre dans le spectre

  while (valeur == 0) {
    reculer(30);
    valeur = digitalRead(infrarouge);
  }

  Serial.println("OBSTACLE DÉTECTÉ");
  // Si on sort de la première boucle, c'est qu'un obstacle a été détecté
  reculer(0);
  delay(10);

  while (valeur == 1) {
    tournerAGauche(30);
    valeur = digitalRead(infrarouge);
  }

  reculer(0);
  delay(10);
}
