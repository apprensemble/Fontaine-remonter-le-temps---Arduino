
//petit bout de programme pour faire passer une led rvb du violet au bleu selon une valeur du potard comprise entre 0 et 1024

// --------------connexion matérielles des broches(pins) ---------------
const int Potpin = 0; // analog 0 connecté au potar, pourquoi on met 0 et as A0?? sur la carte je vois les 2 connections
const int Bleupin = 13; // sortie 13 connecté a la broche bleu de la led
const int Vertpin = 12; // sortie 12 connecté a la broche verte de la led
const int Rougepin = 11; // sortie 11 connecté a la broche rouge de la led


//----------------------     variables pour debug
//debug_potar=1   -> utilisation du port série en comme entrée
//debug_potar=0   -> utilisation du potar
int debug_potar=0;
//-----
//debug_calcul=0   -> rien
//debug_calcul=0   -> utilisation du port serie pour visualistion des calculs
int debug_calcul=1;
//-------------------------------------------------------

void setup() {
  pinMode(Potpin, INPUT); //met la broche relié au potard en entrée
  pinMode(Bleupin, OUTPUT); //met la broche relié au bleu de la led en sortie
  pinMode(Vertpin, OUTPUT); //met la broche relié au vert de la led en sortie
  pinMode(Rougepin, OUTPUT); //met la broche relié au vert de la led en sortie
  Serial.begin(9600);
}



void loop(){
  //--------------------  acquisition       (potar ou port série si debug)   ------------
  int Pot;
  if (debug_potar==1){
    while (Serial.available() > 0) {// si donnée envoyé via le PC
      Pot = Serial.parseInt();
    }
  }
  else
  {
    Pot = analogRead(Potpin);    // lecture de la valeur du potar et stockage dans Pot
  }
  //-------------------------------------------------------------------------------------
 
 
  // -----------------------    calcul des valeurs r g b     -------------
  //       source adaptée de  http://blog.vermot.net/2011/11/03/generer-un-degrade-en-arc-en-ciel-en-fonction-d-une-valeur-programmatio/
  int x = (1530*Pot/1024);
  int r;
  int g;
  int b;
  if(x>=0 && x<255){
    r = 0;
    g = 255;
    b = x;
  }
  if(x>=255 && x<510){
    r = 0;
    g = 510-x;
    b = 255;
  }
  if(x>=510 && x<765){
    r = x-510;
    g = 0;
    b = 255;
  }
  if(x>=765 && x<1020){
    r = 255;
    g = 0;
    b = 1020-x;
  }
  if(x>=1020 && x<=1275){
    r = 255;
    g = x-1020;
    b = 0;
  }
  if(x>=1275 && x<=1530){
    r = 255;
    g = 0;
    b = 1530-x;
  }
//-------------------------------------------------------------------

//--------------------écriture des sorties -----------------------------
  analogWrite(Bleupin, b);  // envoi la valeur b sur la broche bleu de la led
  analogWrite(Vertpin, g);  // envoi la valeur g sur la broche vert de la led
  analogWrite(Rougepin, b);  // envoi la valeur r sur la broche rouge de la led

  if (debug_calcul==1){    //debug -> affichage des valeurs sur le moniteur série
    Serial.print("Pot=");
    Serial.print(Pot);
    Serial.print("\tR=");
    Serial.print(r);
    Serial.print("\tV=");
    Serial.print(g);
    Serial.print("\tB=");
    Serial.println(b);
  }
//--------------------------------------------------------------------------------------
 
  delay(200); // une petite tempo de 100ms pour calmer le tout
}