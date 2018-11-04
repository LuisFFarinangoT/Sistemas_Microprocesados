/*
  Contador del 1 al 200 con display con multiplexacion de displays
  el contador se iniciara sin la intervencion del usuario
  Configuracion
  Nombre: Luis Farinango
  Estructuras de programacion
  pinMode(pin,MODO),PIN 0-13
          MODO.INPUt Y OUTPUT
  delay
  metodo(variable de entrada o salida ){intrucciones }
  for(condiciones){instrucciones}
  digitalWrite(pin,Estado)
  variable%cantidad=modulo de tal cantidad de la variable 
*/

int j;//varible para contador
int i;//variable para recorrer los bits 
int dec = 11;//pines de control de cambio de unidades
int uni = 10;//pines de control de cambio de unidades
int cent = 12; //pines de control de cambio de unidades
int decenas;//variables auxiliares para cambio de unidades
int unidades ;//variables auxiliares para cambio de unidades
int centenas ;//variables auxiliares para cambio de unidades
void setup(){//-------------------------------------------------------------------------------------------------------------------------------------------------------
for(int i=2;i<=6;i++){ // inicializacion de los pines de salida para los bits respectivos 
pinMode(i, OUTPUT);}// inicializacion de los pines de salida para los bits respectivos 
j = 0;//se inicializa el contador en cero
  pinMode(dec, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(uni, OUTPUT);//pines de salida para control multiplexado de display
  pinMode(cent, OUTPUT);//pines de salida para control multiplexado de display
}
void encendido(int cont)//----------------------------------------------------------------------------------------------------------------------------------------------
{//metodo para encendido de displays,entra la variable cont que sera el contador 
for(int i=2; i<=6; i++){ //recorre las posiciones de los pines antes declarados 
digitalWrite(i, cont%2); //en la posicion del contador realiza la operacion modulo de los numeros provenientes del contador para activar los pines correspondienntes
cont=cont/2;//divide cont sobre dos para la siguente posicion 
}//fin de metodo
}
void loop() {//--------------------------------------------------------------------------------------------------------------------------------------------------------
    if (j <200) {// condicion para aumentar la varible j que tendra los valores de 0-200
      j++;//se inicializo j en 0 por lo que comenzara a aumentar 
      centenas=j/100;//calculo de centenas 
      decenas=(j-centenas*100)/10; //calculo de las decenas 
      unidades=(j-centenas*100-decenas*10); //calculo de unidades  
  }
   else {//si sobrepasa la cantidad se realizan las operaciones siguientes 
     j = 1;//j regresa a uno para cumplir la condicion de que el contador repita de 1 a 200 y comenzar de nuevo el ciclo
     unidades=1;// unidades regresa a uno para cumplir la condicion de que el contador repita de 1 a 200 y comenzar de nuevo el ciclo
     decenas=0;//decenas regresa a 0 para comenzar de nuevo el ciclo
     centenas=0;//centenas  regresa a 0 para comenzar de nuevo el ciclo
  }
  // instrucciones para el encendido de displays 
  digitalWrite(uni,HIGH);//alimentacion del display correspondiente a unidades
  digitalWrite(dec,LOW);//no se debe activar el display de decenas 
  digitalWrite(cent,LOW);//no se debe activar el display de centenas 
  encendido(unidades);//llamado del metodo encendido para comenzar el conteo en el display de unidades
  delay(200);//retraso para no saturar el sistema
  digitalWrite(uni,LOW);//no se debe encender el display de unidades
  digitalWrite(dec,HIGH);//alimentacion del display correspondiente a decenas 
  digitalWrite(cent,LOW);//no se debe activar el display de centenas 
  encendido(decenas);//llamado del metodo encendido para comenzar el conteo en el display de decenas 
  delay(200);//retraso para no saturar el sistema
  digitalWrite(uni,LOW);//no se debe encender el display de unidades
  digitalWrite(dec,LOW);//no se debe activar el display de decenas 
  digitalWrite(cent,HIGH);//alimentacion del display correspondiente a centenas 
  encendido(centenas);//llamado del metodo encendido para comenzar el conteo en el display de unidades
  delay(200);//retraso para no saturar el sistema

}
