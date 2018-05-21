//*****************LIBRERIAS*****************

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <NewPing.h>
#include <Servo.h>

//*****************PRECONFIGURACION*****************
//SERVO
Servo myservo;  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
   
//ULTRASONIDOS
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 
//LCD
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

//*****************VARIABLES*****************
int vel = 0; 
float VOLTAJE,SENSOR;
int TEMPERATURA,MAX,condicion;
int MIN=3000;
int a;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);          
  pinMode(2,INPUT);
//Estos son movimientos que debe realizar el servo debido al rebote al conectarle tension.  
  myservo.attach(9);  
  vel = 0;
  myservo.write(vel);
  delay(230);   
  myservo.write(90);
}

void loop()
{
  Serial.println(a);
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
//Este if hace que cuando pasemos la mano por encima del ultrasonidos, se abra la tapa. 
  if ((sonar.ping_cm()<20)&&(sonar.ping_cm()>0)){
    vel = 180;
    myservo.write(vel);
    delay(180);   
    myservo.write(90);
    delay(2000);
    vel = 0;
    myservo.write(vel);
    delay(180);   
    myservo.write(90);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
  }
  delay(250);
  //Esta es la lectura del LM35 y las formulas para que nos de correctamente la temperatura.
  SENSOR=analogRead(A0);
  VOLTAJE=SENSOR/1024.0*5.0;
  TEMPERATURA=VOLTAJE*100/0.96;
  if (MAX<TEMPERATURA){
    MAX=TEMPERATURA;
  }
  if (MIN>TEMPERATURA){
    MIN=TEMPERATURA;
  }

  if (digitalRead(2)==1){
    while (digitalRead(2)==1){
      delay(50);
      Serial.println("bucle");
    }
    a++;
 }
 Serial.println(a);
 //Tenemos 3 casos posibles.
 //Con a==0 la lcd muestra la temperatura actual
  if (a==0){
    lcd.setCursor(0,0);
    lcd.print("  Temperatura:  ");  // Aqi va el mensaje
    Serial.print(TEMPERATURA);
    Serial.println(" Grados ");
    Serial.println(VOLTAJE);
    delay(500); // estabilidad de la lectura
    lcd.setCursor(3, 1);    // Ponte en la line 1, posicion 6
    lcd.print(TEMPERATURA) ;
    lcd.print(" Grados ") ;
  }
  //Con a==1 la lcd muestra la temperatura maxima que ha registrado
  if (a==1){
    lcd.setCursor(0,0);    // Ponte en la line 1, posicion 6
    lcd.print("Temperatura MAX ") ;
    lcd.setCursor(3,1);
    lcd.print(MAX);
    lcd.print(" Grados ") ;
  }
  //Con a==2 la lcd muestra la temperatura minima que ha registrado
  if (a==2){
    lcd.setCursor(0,0);    // Ponte en la line 1, posicion 6
    lcd.print("Temperatura MIN ") ;
    lcd.setCursor(3,1);
    lcd.print(MIN);
    lcd.print(" Grados ") ;
  }
  //Por ultimo reiniciamos el contador de a.
  if (a==3){
    a=0;
  }
}

