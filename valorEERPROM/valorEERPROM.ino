#include <EEPROM.h>

/*
    UTN -FICA -CIERCOM
    Nombre :Luis Farinango
    Deber 
    Realice un sistema que guarde en una posición de la memoria EEPROM solo cuando su valor exceda a la anterior lectura.
*/


int valingre;//variable para guardar el valor que se ingresa por serial
int valremm;//variable para guardar el valor que se tiene en memoria 
String Str;//String para guardar los valores ingresados 
int funS;//variable para interrupcion 
void setup() {
  //EEPROM.update(0,0); linea de codigo para vaciar la pos en memoria
  valremm = EEPROM.read(0);//lectura de la posicion 0 de la EEPROM
  attachInterrupt(0, ingreso, FALLING); //interrupcion de sistema para control general
  Serial.begin(9600);//inicio de comunicacion serial 

}
void ingreso() {
  switch (funS)//interrupcion 
  { case 0://condicion 0
      Str = "";//se vacia la cadena que guarda los datos ingresados 
      Serial.println("Ingrese el valor a guardar en la EEPROM");//impresion de mensaje 
      funS++;//aumento de la variable contador
      break;
    case 1:
      funS++;//aumento de la variable contador
      Serial.println("Datos Ingresados");//impresion de mensaje 
      break;
    case 2:
      funS++;//aumento de la variable contador
      Serial.println("comparacion de datos ");//impresion de mensaje 
      break;
    case 3:
      funS++;//aumento de la variable contador
      if (Str.length() <= 3) { //validación de tamaño  del dato ingresado
        valingre = Str.toInt();//se transforma a ese valor a un dato del tipo entero
              if (valingre >= 0 && valingre < 255)//se valida el tamaño maximo del dato ingresado
      { Serial.println("valor ingresado valido");//impresion de mensaje 
        if (valingre > valremm)//se comprueba que el dato ingresado sea mayor a dato que se tiene en memoria 
        { EEPROM.update(0, valingre);//se ingresa el valor en memoria 
          Serial.println("valor actualizado");//impresion de mensaje 
          Serial.println(valingre);//impresion de datos 
        } else {
          Serial.println("el valor no supera al anterior");//impresion de mensaje 
        }
      } else {
        Serial.println("valor ingresado no valido");//impresion de mensaje 
        Str = "";//se vacia la cadena 
        valingre = 0;//se vacia el dato 
      }
      }
      else{Serial.println("valor no valido");}
      Serial.print(EEPROM.read(0));

      break;
    case 4:
      funS = 0;//reinicio de la variable de contador para iniciar de nuevo el ciclo
      Serial.println("fin ");//impresion de mensaje 
      break;
  }
}

void loop() {
  if (funS == 2) {//lectura de datos 
    if (Serial.available() > 0) {//comprobacion de comunicacion serial
      Str = Serial.readString();//lectura de los datos ingresados por Cx

    }
  }

}
