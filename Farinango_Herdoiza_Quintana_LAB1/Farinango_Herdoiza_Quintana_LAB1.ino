/*
Laboratorio1 Contador de personas automatico
1.  El contador debe ser de 1 al 50.
2.  Debe tener un botón de reset de conteo.
3.  Si una persona ingresa y sale se debe restar el valor de conteo.
4.  Se debe tener un led de aviso si el sistema aumenta su valor y otro led de aviso cuando haya sido restado el valor.
Nombres :
            Farinago Luis
            Herdoiza Adriana
            Quintana Karen
 Estructuras de programacion
  pinMode(pin,MODO)
          MODO.INPUt Y OUTPUT
  delay
  metodo(variable de entrada o salida ){intrucciones }
  for(condiciones){instrucciones}
  digitalWrite(pin,Estado)
  variable%cantidad=modulo de tal cantidad de la variable 
*/
int ledentra = 13; //led indicador de entrada
int ledsal = 12; //led indicador de salida
int btreset = 7; //pin para boton de reseteo
int senentra = 8 ; //pin sensor de entrada
int sensalid = 9 ; //pin  sensor de salida
int j;//varible para contador
int i;//variable para contador
int dec = 11;//pines de control de cambio de unidades
int uni = 10;//pines de control de cambio de unidades
int decenas;//variables auxiliares para cambio de unidades
int unidades ;//variables auxiliares para cambio de unidades
void setup() {//-----------------------------------------------------------------------------------------------------------------------------------------------------
  for (int i = 2; i <= 6; i++) { // inicializacion de los pines de salida para los bits respectivos
    pinMode(i, OUTPUT);
  }// inicializacion de los pines de salida para los bits respectivos
  i = 0;//se inicializa el contador en cero
  j = 0;//se inicializa el recorrido de bits  en cero
  pinMode(dec, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(uni, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(ledentra, OUTPUT);//pin de led de control de entrada de personas
  pinMode(ledsal, OUTPUT);//pin de led de control de salida  de personas
  pinMode(senentra, INPUT);//pin de entrada para aumentar valores
  pinMode(sensalid, INPUT);//pin de entrada  para disminuir valores
  pinMode(btreset, INPUT); //pin de boton de reset
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
  //#################################################################################################################################
  if (digitalRead(senentra) == HIGH && digitalRead(sensalid) == LOW) { //condicion para cuando una persona entra
    digitalWrite(ledentra, HIGH);//encendido del led de aviso de entrada cuando una persona entro
    digitalWrite(ledsal, LOW);//apagado del led de aviso de salida  cuando una persona entro
    if (j < 50) {//se continuara el ciclo hasta que el contador llegue a 40
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
  //######################################################################################################################################
  if (digitalRead(senentra) == LOW && digitalRead(sensalid) == HIGH) { //condicion para cuando una persona sale
    digitalWrite(ledentra, LOW);//apagado del led de aviso de entrada  cuando una persona salio
    digitalWrite(ledsal, HIGH);//encendido del led de aviso de salida cuando una persona salio
    if (j > 0 && j <= 50) {//el intervalo donde se restara sera cuando el contador este entre mayor que 0 y 40
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
  }//####################################################################################################################################
  if (digitalRead(btreset) == HIGH)//condicion para reseteo del sistema
  { j = 0;// se iguala a cero para reseteo del sistema
    unidades = 0;// se iguala a cero para reseteo del sistema
    decenas = 0;// se iguala a cero para reseteo del sistema
    digitalWrite(ledentra, LOW);//se apaga los leds para reseteo del sistema
    digitalWrite(ledsal, LOW);//se apaga los leds para reseteo del sistema
    encendido(0);//entrada de 0 al metodo para regresar el display al numero 0
    apagado(0);//entrada de 0 al metodo para regresar el display al numero 0
  }
}
