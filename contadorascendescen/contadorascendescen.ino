/*
   Deber
  Realizar un programa que medienta un pulsador se aumente el valor de
  un contador (1 al 40) y mediante otro pulsador se reste ese valor.
  Configuracion
  Nombre: Luis Farinango
  Estructuras de programacion
  pinMode(pin,MODO),PIN 0-13
          MODO.INPUt Y OUTPUT
  delay
*/
int pulsaplus = 8 ; //pin para pulsador de aumento
int pulsaminus = 9 ; //pin  para pulsador de decremento
int j;//varible para contador
int i;//variable para contador
int dec = 11;//pines de control de cambio de unidades
int uni = 10;//pines de control de cambio de unidades
int cent = 12; //pines de control de cambio de unidades
int decenas;//variables auxiliares para cambio de unidades
int unidades ;//variables auxiliares para cambio de unidades
int centenas ;//variables auxiliares para cambio de unidades
void setup() {//-----------------------------------------------------------------------------------------------------------------------------------------------------
  for (int i = 2; i <= 6; i++) { // inicializacion de los pines de salida para los bits respectivos
    pinMode(i, OUTPUT);
  }// inicializacion de los pines de salida para los bits respectivos
  i = 0;//se inicializa el contador en cero
  j = 0;//se inicializa el recorrido de bits  en cero
  pinMode(dec, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(uni, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(cent, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(pulsaplus, INPUT);//pin de entrada para aumentar valores
  pinMode(pulsaminus, INPUT);//pin de entrada  para disminuir valores
}
void encendido(int cont)// ---------------------------------------------------------------------------------------------------------------------------------------------
{ //metodo para encendido de displays,entra la variable cont que sera el contador
  for (int i = 2; i <= 6; i++) {//recorre las posiciones de los pines  declarados
    digitalWrite(i, cont % 2);//en la posicion del contador realiza la operacion modulo de los numeros provenientes del contador para activar los pines correspondienntes
    cont = cont / 2;//divide cont sobre dos para la siguente posicion
  }
}//fin del metodo
void apagado(int cont) {//metodo para apagado de displays,entra la variable cont que sera el contador
  for (int i = 2; i <= 6; i++) {//recorre las posiciones de los pines  declarados
    digitalWrite(i, cont % 2);//en la posicion del contador realiza la operacion modulo de los numeros provenientes del contador para activar los pines correspondienntes
    cont = cont / 2;//divide cont sobre dos para la siguente posicion
  }
}//fin del metodo
void loop() {//----------------------------------------------------------------------------------------------------------
  //###########################################################################
  if (digitalRead(pulsaplus) == HIGH) {//condicion para cuando se presiona el pulsador que aumentara el contador
    if (j < 40) {//se continuara el ciclo hasta que el contador llegue a 40
      j++;//si se cumple la condicon se aumenta el numero del contador
      decenas = j / 10; //calculo de las decenas
      unidades = (j - decenas * 10); //calculo de unidades
      digitalWrite(uni, HIGH);//alimentacion del display correspondiente a unidades
      digitalWrite(dec, LOW);//no se debe activar el display de decenas
      encendido(unidades);//llamado del metodo para encender el display
      delay(200);//retraso para no sobrecargar el sistema
      digitalWrite(uni, LOW);//no se debe activar el dispaly de unidades
      digitalWrite(dec, HIGH);//alimentacion del display correspondente a decenas
      encendido(decenas);//llamado del metodo para encender el display
      delay(200);//retraso para no sobrecargar el sistema
    }
    else {//instrucciones para cuando el contador sobrepase el 40 o llegue a ese numero
      j = j;//se mantiene el numero en el contador
      unidades = unidades;//se mantiene el numero en las unidades
      decenas = decenas;// se mantiene el numero en las decenas
    }
  }
  //###################################################################################################
  if (digitalRead(pulsaminus) == HIGH) {//condicion para cuando se presiona el puslador que decrementara el contador
    if (j > 0 && j <= 40) {//el intervalo donde se restara sera cuando el contador este entre mayor que 0 y 40
      j--;//el contador dismuinira
      decenas = j / 10; //calculo de las decenas
      unidades = (j - decenas * 10); //calculo de unidades
      digitalWrite(uni, HIGH);//alimentacion del display correspondiente a unidades
      digitalWrite(dec, LOW);//no se debe activar el display de decenas
      apagado(unidades);//llamado del metodo para apagar el display
      delay(200);//retraso para no sobrecargar el sistema
      digitalWrite(uni, LOW);//no se debe activar el display de unidades
      digitalWrite(dec, HIGH);//alimentacion del display correspondiente a decenas
      apagado(decenas);//llamado del metodo para apagar el display
      delay(200);//retraso para no sobrecargar el sistema
    }
    else {//instrucciones para cuando el contador llegue a cero
      j = 0;// se iguala a cero para terminar el ciclo
      unidades = 0;// se iguala a cero para terminar el ciclo
      decenas = 0;// se iguala a cero para terminar el ciclo
    }
  }
}
