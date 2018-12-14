#include <stdio.h>//librerias de transformacion 
#include <stdlib.h>//librerias de transformacion 
/*  UTN FICA CIERCOM SISTEMAS MICROPOROCESADOS
 * Laboratorio 
 * comdiciones 
 * 
  1.Desarrolle un sistema que permita la visualización  en dos display multiplexados el valor de voltaje en decimales.
  2.Con interrupciones de encendido y apagado. 
  3.El límite se lo ingresa por Cx serial.
Nombres :
            Farinago Luis
            Herdoiza Adriana
            Quintana Karen
*/
int digito1 = 8;//variable que encendera el display del dígito 1
int digito2 = 9;//variable que encendera el display del dígito 2
int led = 10;//variable que encendera un led de prueba
int cont = 0;//varible para contador
float conversor;//variable que recibe el CAD recibido por el pot
float dato;//variable donde se guardara el dato recibido
int  dat1;//variable donde se guardara el primer dígito del dato recibido por el pot
int  dat2;//variable donde se guardara el segundo dígito del dato recibido por el pot
String dt;// varaiable donde se guardara el dato limite ingresado por Cx
char conversion[3];//vector de tamaño 3 para la conversion del dato recibido por el pot
int comp1;//variable donde se guardara el primer dígito del dato recibido por el CX
int comp2;//variable donde se guardara el segundo dígito del dato recibido por el Cx
int funcionamiento = 0; //variable interrupció 0
void setup() {//********************************************************************************************
  pinMode(digito1, OUTPUT);//declaración de entradas y salidas 
  pinMode(digito2, OUTPUT);//declaración de entradas y salidas 
  pinMode(led, OUTPUT);//declaración de entradas y salidas 
  Serial.begin(9600);//inicio de CX
  for (int i = 3; i <= 6; i++) { // inicializacion de los pines de salida para los bits respectivos
    pinMode(i, OUTPUT);//declaración de entradas y salidas 
  }
  attachInterrupt(0, sistema, FALLING);//inicialización de la Interrupción del sistema
}
void encendido1(int cont)//********************************************************************************************
{ //metodo para encendido de displays,entra la variable cont que sera el contador
  for (int i = 3; i <= 6; i++) { //recorre las posiciones de los pines antes declarados
    digitalWrite(i, cont % 2); //en la posicion del contador realiza la operacion modulo de los numeros provenientes del contador para activar los pines correspondienntes
    cont = cont / 2;//operaciones 
  }//fin de metodo
  delay(25);
}
void encendido2(int cont)//********************************************************************************************
{ //metodo para encendido de displays,entra la variable cont que sera el contador
  for (int i = 3; i <= 6; i++) { //recorre las posiciones de los pines antes declarados
    digitalWrite(i, cont % 2); //en la posicion del contador realiza la operacion modulo de los numeros provenientes del contador para activar los pines correspondienntes
    cont = cont / 2;//operaciones 
  }//fin de metodo
  delay(25);
}
void sistema() //acciones a realizar en la interrupción del sistema 
{//********************************************************************************************
  //  //presiona una vez SISTEMA ON
  //  // pres 2 veces RECIBE DATO SERIAL
  //  //pres 3 veces SISTEMA COMPARA
  //  //pres 4 veces SISTEMA OFF
  switch (funcionamiento) {//diferentes situaciones para la variable funcionamiento
    case 0://condicion de inicio de sistema 
      Serial.println("Sistema ON");
      funcionamiento ++;//aumento de contador 
      break;
    case 1://condición para ingresar datos 
      Serial.println("Ingrese Dato");//impresión de información
      funcionamiento ++;//aumento de contador 
      break;
    case 2://condición que permite realizar las operaciones del sistema 
      Serial.println("Sistema compara:");//impresión de información
      funcionamiento ++;//aumento de contador 
      if (dt.length() > 3 && dt.charAt(1) != '.')//validación del tamaño de los numeros ingresados asi como el punto
      {
        Serial.println("numero no permitido");//impresión de información
      }
      break;
    case 3://condicion que apaga el sistema 
      Serial.println("Sistema OFF");//impresión de información
      funcionamiento = 0;//contador  cero para comenzar de nuevo el ciclo 
      digitalWrite(digito1, LOW);//apagado de displays 
      digitalWrite(digito2, LOW);//apagado de displays 
      break;
  }//fin de la interrupcion 
}
void loop() {//********************************************************************************************
  //si 5v es a 1023 entonces que tendre en x
  //5v--->1023
  //x--->conversor

  conversor = analogRead(0); //lectura del dato  del potenciometro
  delay(300);//retraso del sistema
  if (conversor > 0)//condición para saber si el potenciometro bota información 
  { delay(25);//retraso del sistema
    dato = (5 * conversor) / 1023; //transformar el valor para obtener el voltaje
    dtostrf(dato, 3, 2, conversion);//conversion de float a vector 
    dat1 = (int)conversion[0] - 48;//inicializacion de primer digito del pot mediante las conversiones correspondientes 
    digitalWrite(digito1, HIGH);//alimentacion de displays 
    digitalWrite(digito2, LOW);//alimentacion de displays 
    encendido1(dat1);//encendido de display del primer dígito
    delay(25);//retraso del sistema 
    dat2 = (int)conversion[2] - 48;//inicializacion de segundo digito del pot mediante las conversiones correspondientes
    digitalWrite(digito2, HIGH);//alimentacion de displays
    digitalWrite(digito1, LOW);//alimentacion de displays
    encendido2(dat2);//encendido de display del segundo  dígito
    delay(25);
  }
  if (funcionamiento == 2) {//condición para la lectura de los datos de Cx
    delay(300);//retraso del sistema 
    if (Serial.available() > 0) {//comprobacion de comunicacion serial
      dt = Serial.readString();//lectura de los datos ingresados por Cx
      if (dt.charAt(1) == '.' && dt.length() == 3) {//validación de tamaño y el punto decimal del dato ingresado
        comp1 = (dt.substring(0, 1)).toInt();//extracción del primer digito recibido por CX
        comp2 = (dt.substring(2, 3)).toInt();//extracción del segundo digito recibido por CX
      }
    }
  } if (funcionamiento != 2)//condicion que comparara los datos del pot y Cx
  { if (dat1 > comp1)// Si el dato del primer digito del potenciometro es mayor al dato del primer digito ingresado por serial
    {
      digitalWrite(led, HIGH);// led encendido
      //Serial.println("ALARMA");}
    }
    else if (dat1 == comp1&&dat2 > comp2)//si el dato primero de potenciometro es igual al dato del primer digito de serial
    { //if (dat2 > comp2)// compara el segundo digito del portenciometro y serial y si es mayor
      { digitalWrite(led, HIGH);// el led se prende 
      }
    }
    else {
      digitalWrite(led, LOW);// el led se apaga
    }
  }else{//condición para encender los displays siempre
      digitalWrite(digito1, HIGH);//no se debe activar el display de unidades
      digitalWrite(digito2, LOW);//alimentacion del display correspondiente a decenas
      encendido1(dat1);//llamado del metodo para apagar el display
      delay(25);//retraso para no sobrecargar el sistema
      digitalWrite(digito1, LOW);//alimentacion del display correspondiente a unidades
      digitalWrite(digito2, HIGH);//no se debe activar el display de decenas
      encendido2(dat2);//llamado del metodo para apagar el display
      delay(25);//retraso del sistema
      }

}
