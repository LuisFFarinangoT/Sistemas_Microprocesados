/*
 *leds secuenciales 
 *Nombres: Luis Farinango
 *Deber:
    1.- Realizar un juego de luces que se prendan secuencialmente los leds impartes (1,3,5).
    2.- Realizar un programa que se enciendan uno por uno los leds pares (0,2,4). 
    3.- Realizar un juego que se enciendan y apaguen los leds de forma aleatoria. 
 *Estructuras de programacion
 *pinMode(pin,MODO),PIN 0-13
 *        MODO.INPUt Y OUTPUT 
 *digitalWrite(pin,Modo)---pin =0-13
 *              MODO=HIGH O LOW
 *delay
 *SECCIONES DEL PROGRAMA 
 *  1.-librerias y variables 
 *  2.-configuracion del sistema(void_setup)
 *  3.-funcionamiento del sistema(void-loop)
 *  4.-subrutinas(funcionamiento especial)
 */
  int leds[6]={8,9,10,11,12,13};
  int  i=0;//variable de recorrido del vector
void setup() {
    for(;i<6;i++)//configuracion de pines de forma grupal
  { 
    pinMode(leds[i],OUTPUT);//configuraciones los pines del vector como salidas
    }
    i=0;//reseteo de la variable de conteo 
  // put your setup code here, to run once:

}

void loop() {
  /*
  *leds secuenciales en las posisciones impares 
  *
  */
  for(;i<6;i++)
{
  if(i%2==1)//condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a uno pasa a encender los leds
  {digitalWrite(leds[i],HIGH);//encendido de leds segun la condicion 
  delay(200);}
  }
  //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
  for(;i>=0;i--)//
  {
  if(i%2==1)//condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a uno pasa a apagar  los leds
  {digitalWrite(leds[i],LOW);
  delay(200);}
    }
    i=0;//reinicio de la variable de conteo para repetir el ciclo de nuevo 
 /*
  *leds secuenciales en las posisciones pares
  *
  */
  for(;i<6;i++)
{
  if(i%2==0)//condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a cero pasa a encender los leds
  {digitalWrite(leds[i],HIGH);//encendido de leds segun la condicion 
  delay(200);}
  }
  //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
  for(;i>=0;i--)//
  {
  if(i%2==0)//condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a cero pasa a apagar  los leds
  {digitalWrite(leds[i],LOW);
  delay(200);}
    }
    i=0;//reinicio de la variable de conteo para repetir el ciclo de nuevo 
  /*
  *leds secuenciales en posiciones aleatorios
  *
  *
  */

  for(;i<6;i++)//encendido
{  long  numale=random(6);//creacion de un numero random con un rango de 0 a 5 segun la variale random
  digitalWrite(leds[numale],HIGH);//encendido de leds segun la condicion 
  delay(200);
  }
  
  //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
  for(;i>=0;i--)//apagado 
  {
    long  numale=random(6);//creacion de un numero random con un rango de 0 a 5 segun la variale random
  digitalWrite(leds[numale],LOW);//apagado de leds segun la condicion 
  delay(200);
  
  
    }
    i=0;//reinicio de la variable de conteo para repetir el ciclo de nuevo 
}
