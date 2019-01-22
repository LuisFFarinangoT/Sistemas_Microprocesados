/*
   UTN -FICA -CIERCOM
   PRUEBA
   Nombre :Luis Farinango



  Se necesita emular el funcionamiento de un control de auto ChevyStar. Para ello, se tienen las siguientes características.
  • Se cuenta con 4 botones, uno máster y 3 para la contraseña.
  • La contraseña es de 5 dígitos que debe ser la combinación de los 3 botones.
  • El sistema al presionar una vez (solo botón máster) y sin contraseña envía por comunicación serial el mensaje de activado o desactivado.
  • Si es digitada la contraseña es correcta (se presiona la combinación de los 3 botones y luego el máster),
  envía por mensaje serial que se puede encender el carro. Caso contrario, se tendrá hasta 2 intentos más para acertar a la contraseña.
  Si no es el caso, el control se reinicia y genera otra contraseña de forma aleatoria de la combinación de los pulsadores.
  La nueva contraseña se envía por comunicación serial.

*/
#include <EEPROM.h>
#include <avr/wdt.h>//libreria de watch dog 
#include <MsTimer2.h>
#include <LiquidCrystal.h>//librerá de pantalla lcd
LiquidCrystal LCD(3, 4, 5, 6, 7, 8); //pines de habilitacion RS,E,D4,D5,D6,D7
int val1 = 9;
int val2 = 10;
int val3 = 11;
int funS;
int contfallos;
int contingre;
int est = 3;
String ingreso;
String p1 ;
String  p2;
String  p3;
String  p4;
String  p5;
String contra ;

void setup() {
  LCD.begin(16, 2); //inicializar lcd
  LCD.setCursor(0, 0);////impresion en LCD
  LCD.print("INICIO");
  Serial.begin(9600);//inicio de CX
  //  MsTimer2::set(5000, reset);//inicializacion de timer
  // MsTimer2::start();//inicio de timer
  Serial.println("RESET");//impresion de mensaje
  attachInterrupt(0, master, FALLING); //interrupcion de sistema para control general
  pinMode(val1, INPUT);
  pinMode(val2, INPUT);
  pinMode(val3, INPUT);
  //  EEPROM.update(1,1);
  //  EEPROM.update(2,2);
  //  EEPROM.update(3,3);
  //  EEPROM.update(4,1);
  //  EEPROM.update(5,2);
  p1 = EEPROM.read(1);
  p2 = EEPROM.read(2);
  p3 = EEPROM.read(3);
  p4 = EEPROM.read(4);
  p5 = EEPROM.read(5);
  Serial.print(p1);
  Serial.print(p2);
  Serial.print(p3);
  Serial.print(p4);
  Serial.print(p5);
  contra = p1 + p2 + p3 + p4 + p5;
  Serial.println("------------");
  Serial.println(contra);
}
void master () {//****************************************************************************************************
  switch (funS)//interrupcion
  { case 0://condicion 0
      Serial.println("--------------");
      Serial.println("BIENVENIDO ");//impresion de mensaje
      funS++;//aumento de la variable contador
      break;
    case 1:
      Serial.println("--------------");
      Serial.println("INGRESO DE CONTRASEÑA ");//impresion de mensaje
      funS++;//aumento de la variable contador

      break;
    case 2:
      Serial.println("--------------");
      Serial.println("LECTURA DE CONTRASEÑA ");//impresion de mensaje
      funS++;//aumento de la variable contador
      break;
    case 3:
      if (ingreso.length() == 0)//se valida que se ingrese un valor
      {
        Serial.println("valor no valido");//impresion de mensaje
        funS = 0;//se regresa al inicio

      }
      else if (ingreso.length() >= 6)
      {
        Serial.println("valor excedido");
        funS = 0;

      } else {
        funS = 4;
      }

      break;

    case 4 :
      Serial.println("comprobacion");
      if (est == 1) {
        Serial.println("--------------");
        Serial.println("CARRO ACTIVADO");
      }
      else
      { contfallos++;
        Serial.println("fallos");
        Serial.println(contfallos);
        funS = 0;
      }
    case 5:
      if (contfallos > 3)
      { EEPROM.update(1, random(1,3));
        EEPROM.update(2, random(1,3));
        EEPROM.update(3, random(1,3));
        EEPROM.update(4, random(1,3));
        EEPROM.update(5, random(1,3));
        Serial.println("la nueva contraseña es" );
        Serial.print(EEPROM.read(1)+EEPROM.read(2)+EEPROM.read(3)+EEPROM.read(4)+EEPROM.read(5));
        Serial.println("cambio de contra");

      }
      break;
  }
}
void loop() {

  if (funS == 2)
  {    {
      if (digitalRead(val1) == LOW)

      {
        delay(300);
        Serial.print("1");
        ingreso = ingreso + "1"  ;

      }
      if (digitalRead(val2) == LOW)
      {
        delay(300);
        Serial.print("2");
        ingreso = ingreso + "2" ;
      }
      if (digitalRead(val3) == LOW)
      { delay(300);

        Serial.print("3");
        ingreso = ingreso + "3" ;
      }
    }
  }
  if (funS == 3)//ingreso de datos
  {
    Serial.println(contra);
    if (ingreso.charAt(0) == contra.charAt(0) && ingreso.charAt(1) == contra.charAt(1) && ingreso.charAt(2) == contra.charAt(2) && ingreso.charAt(3) == contra.charAt(3) && ingreso.charAt(4) == contra.charAt(4)) //condiciones de reconocimiento de vocales
    {
      est = 1;
      //funS++;
    }
    else {
      est = 0;

    }

  }

}
