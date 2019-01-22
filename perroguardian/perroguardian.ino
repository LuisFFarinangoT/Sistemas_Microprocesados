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
float valvol;//variable que guarda el valor del voltaje
int cont ;//variable para contador
int resp = 0;//variable de control
int funS;//variable de interrupcion
int est;//variable de control
int act;//variable de control
String str;//variable que guarda el valor del tiempo ingresado
void control() {//****************************************************************************************************
  //interrupcion que controla el sistema
  switch (funS)//interrupcion
  { case 0://condicion 0
      Serial.println("BIENVENIDO ");//impresion de mensaje
      funS++;//aumento de la variable contador
      act = 0;//reseteo de las variables
      est = 0;//reseteo de las variables
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
      if (str.length() == 0)//se valida que se ingrese un valor
      {
        Serial.println("valor no valido");//impresion de mensaje
        funS = 0;//se regresa al inicio
      }
      Serial.println("INICIO DGW");//impresion de mensaje
      break;
    case 5:
      break;
  }
}
void reset ()//*************************************************************************************************
{ valvol = (analogRead(0) * 5.0) / 1023.0;//CAD
  LCD.setCursor(5, 1);//impresion en LCD
  LCD.print(valvol);//impresion en LCD
  if (valvol < 3)//se toma en cuenta un valor minimo
  { switch (act)//la variable de control que se asigna en base a los valores ingresados
    {
      case 1:
        cont++;//inicio de contador
        Serial.println("ALERTA");//impresion en LCD
        EEPROM.write(0, valvol);//impresion en LCD
        if (cont == 2) {//el contador controla el WTD
          wdt_enable(WDTO_8S);//inicio de WTD
          cont = 0;//reseteo de contador
        }

        break;
      case 2:
        cont++;//inicio de contador
        Serial.println("ALERTA");//impresion en LCD
        EEPROM.write(0, valvol);//impresion en LCD
        if (cont == 12) {//el contador controla el WTD
          wdt_enable(WDTO_8S);//inicio de WTD
          cont = 0;//reseteo de contador
        }
        break;
      case 3:
        cont++;//inicio de contador
        Serial.println("ALERTA");//impresion en LCD
        EEPROM.write(0, valvol);//impresion en LCD
        if (cont == 22) {//el contador controla el WTD
          wdt_enable(WDTO_8S);//inicio de WTD
          cont = 0;//reseteo de contador
        }
        break;
      case 4:
        cont++;//inicio de contador
        Serial.println("ALERTA");//impresion en LCD
        EEPROM.write(0, valvol);//impresion en LCD
        if (cont == 32) {//el contador controla el WTD
          wdt_enable(WDTO_8S);//inicio de WTD
          cont = 0;//reseteo de contador
        }
        break;
    }

  } else {
    LCD.clear();//limieza de LCD
    LCD.setCursor(8, 1);//impresion en LCD
    LCD.print("SIN PROBM");//impresion en LCD
  }


}
void setup() {
  LCD.begin(16, 2); //inicializar lcd
  LCD.setCursor(0, 0);////impresion en LCD
  Serial.begin(9600);//inicio de CX
  MsTimer2::set(5000, reset);//inicializacion de timer
  MsTimer2::start();//inicio de timer
  Serial.println("RESET");//impresion de mensaje
  attachInterrupt(0, control, FALLING); //interrupcion de sistema para control general

}

void loop() {

  if (funS == 2)//ingreso de datos
  { if (Serial.available() > 0) {//comprobaciond de C.x
      str = Serial.readString();//Recibe en caracteres//ingreso de la cadena

      funS = 4;//se cambia la variable de interrupcion
    }
  }
  if (funS == 4)//lectura de los datos ingresados
  { est = 1;//se cambia una variable de estado
    if (str.toInt() == 10 || str.toInt() == 20 || str.toInt() == 30 || str.toInt() == 40)//se valida los valores ingresados
    { switch (str.toInt())//se toma el valor ingresado
      {
        case 10://para cuando sean 10 s
          delay(500);//retraso del sistema
          act = 1;//asignacion de variable de control
          LCD.setCursor(0, 0);//impresion en LCD
          LCD.print("DGW");//impresion en LCD
          LCD.setCursor(6, 0);//impresion en LCD
          LCD.print(str);//impresion en LCD
          break;
        case 20://para cuando sean 20 s
          delay(500);//retraso del sistema
          act = 2;//asignacion de variable de control
          LCD.setCursor(0, 0);//impresion en LCD
          LCD.print("DGW");//impresion en LCD
          LCD.setCursor(6, 0);//impresion en LCD
          LCD.print(str);//impresion en LCD
          break;
        case 30://para cuando sean 30 s
          delay(500);//retraso del sistema
          act = 3;//asignacion de variable de control
          LCD.setCursor(0, 0);//impresion en LCD
          LCD.print("DGW");//impresion en LCD
          LCD.setCursor(6, 0);//impresion en LCD
          LCD.print(str);//impresion en LCD
          break;
        case 40://para cuando sean 40 s
          act = 4;//asignacion de variable de control
          delay(500);//retraso del sistema
          LCD.setCursor(0, 0);//impresion en LCD
          LCD.print("DGW");//impresion en LCD
          LCD.setCursor(6, 0);//impresion en LCD
          LCD.print(str);//impresion en LCD
          break;
      }

    }
  }

}
