/*
   UTN -FICA -CIERCOM
   SISTEMAS MICROPROCESADOS
   DEBER
   Nombre :
           Luis Farinango
      Realizar un programa que permita que el conversor análogo digital configure al perro guardían a 10,20,30 y 40 segundos.
      Este proceso se visualiza en una lcd.
         Instrucciones para trabajo
          timeout<<<<tiempo de configuracion para generar el reinicio
          WDTO_15MS
          WDTO_30MS
          WDTO_60MS
          WDTO_120MS
          WDTO_250MS
          WDTO_500MS
          WDTO_1S
          WDTO_2S
          WDTO_4S
          WDTO_8S
*/
#include <EEPROM.h>
#include <avr/wdt.h>//libreria de watch dog 
#include <MsTimer2.h>
#include <LiquidCrystal.h>//librerá de pantalla lcd
LiquidCrystal LCD(3, 4, 5, 6, 7, 8); //pines de habilitacion RS,E,D4,D5,D6,D7
float valvol;
int cont ;
int resp = 0;
int funS;
int est;
int act;
String str;
void control() {

  switch (funS)//interrupcion
  { case 0://condicion 0
      Serial.println("BIENVENIDO ");//impresion de mensaje
      funS++;//aumento de la variable contador
      act = 0;
      est = 0;
      break;
    case 1:
      funS++;//aumento de la variable contador
      Serial.println("INGRESO DE VALOR DE DGW");//impresion de mensaje
      break;
    case 2:
      funS++;//aumento de la variable contador
      Serial.println("LECTURA DE DATOS ");//impresion de mensaje
      break;
    case 4 :
      if (str.length() == 0)
      {
        Serial.println("valor no valido");
        funS = 0;
      }
      Serial.println("INICIO DGW");
      break;
    case 5:
      break;
  }
}
void reset ()
{ valvol = (analogRead(0) * 5.0) / 1023.0;
  LCD.setCursor(5, 1);
  LCD.print(valvol);
 if (valvol < 2.5)
    { switch (act)
      {
        case 1:
          Serial.println("ALERTA");
          EEPROM.write(0, valvol);
          wdt_enable(WDTO_1S);
          break;
        case 2:
          Serial.println("ALERTA");
          EEPROM.write(0, valvol);
          wdt_enable(WDTO_2S);
          Serial.println("ddddddddddddddddd");
          break;
        case 3:
          Serial.println("ALERTA");
          EEPROM.write(0, valvol);
          wdt_enable(WDTO_4S);
          break;
        case 4:
          Serial.println("ALERTA");
          EEPROM.write(0, valvol);
          wdt_enable(WDTO_8S);
          break;
      }

    } else {
      LCD.clear();
      LCD.setCursor(5, 1);
      LCD.print("SIN PROBM");
    }
  

}
void setup() {
  cont = EEPROM.read(0);
  LCD.begin(16, 2); //inicializar lcd
  LCD.setCursor(0, 0);
  Serial.begin(9600);
  MsTimer2::set(5000, reset);
  MsTimer2::start();
  Serial.println("RESET");
  attachInterrupt(0, control, FALLING); //interrupcion de sistema para control general

}

void loop() {
  cont++;
  delay(500);
    if (est == 1)
  {}
  if (funS == 2)
  { if (Serial.available() > 0) {//comprobaciond de C.x
      str = Serial.readString();//Recibe en caracteres//ingreso de la cadena

      funS = 4;
    }
  }
  if (funS == 4)
  { est = 1;
    if (str.toInt() == 10 || str.toInt() == 20 || str.toInt() == 30 || str.toInt() == 40)
    { switch (str.toInt())
      {
        case 10:
          act = 1;
          LCD.setCursor(0, 0);
          LCD.print("DGW");
          LCD.setCursor(6, 0);
          LCD.print(str);
          break;
        case 20:
          act = 2;
          LCD.setCursor(0, 0);
          LCD.print("DGW");
          LCD.setCursor(6, 0);
          LCD.print(str);
          break;
        case 30:
          act = 3;
          LCD.setCursor(0, 0);
          LCD.print("DGW");
          LCD.setCursor(6, 0);
          LCD.print(str);
          break;
        case 40:
          act = 4;
          LCD.setCursor(0, 0);
          LCD.print("DGW");
          LCD.setCursor(6, 0);
          LCD.print(str);
          break;
      }

    }
  }
  //Serial.println(cont);

}
