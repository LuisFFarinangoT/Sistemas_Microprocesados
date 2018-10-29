/*
  leds secuenciales
  Nombres:
  Farinango Luis
  Herdoiza Adriana
  Quintana Karen 
  Deber:
    1.- Realizar un programa que permita activar 4 juegos de luces diferentes con un dipswicth de 4 posiciones
    2.- Realizar un contador binario de 6 bits que se active de forma secuencial con un pulsador
  Estructuras de programacion
  pinMode(pin,MODO),PIN 0-13
          MODO.INPUt Y OUTPUT
  digitalWrite(pin,Modo)---pin =0-13
                MODO=HIGH O LOW
                switch (variable de control){case ()variable de control){codigo a realizar}}
  delay
*/
int leds[6] = {8, 9, 10, 11, 12, 13};
int pos0 = 2; // variable  de poscion del primer switch--------control de luces
int pos1 = 3; // variable de posicion del segundo switch------control de luces
int pos2 = 4; //varaible de poscion del tercer switch ------control de luces
int pos3 = 5; //variable de poscion del cuarto switch ------control de luces
int pulsa = 6; //variable de poscion del pulsador  ------control de contador
int  i = 0; //variable de recorrido del vector
int control = 0; //variable que permitira cintrolar los swtichs
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int btn = 7;
void setup() {
  for (; i < 6; i++) //configuracion de pines de forma grupal
  { pinMode(leds[i], OUTPUT); //configuraciones los pines del vector como salidas
  }
  i = 0; //reseteo de la variable de conteo
  //declaracion de las entradas de acuerdo a los pines
  pinMode(pos0, INPUT);
  pinMode(pos1, INPUT);
  pinMode(pos2, INPUT);
  pinMode(pos3, INPUT);
  pinMode(pulsa, INPUT);
}
void loop() {
  if (digitalRead(pos0) == HIGH) //condicion que cambiara la varaiable de control para el primer switch
    control = 1;
  if (digitalRead(pos1) == HIGH) //condicion que cambiara la varaiable de control para el segundo switch
    control = 2;
  if (digitalRead(pos2) == HIGH) //condicion que cambiara la varaiable de control para el tercer switch
    control = 3;
  if (digitalRead(pos3) == HIGH) //condicion que cambiara la varaiable de control para el cuarto switch
    control = 4;
  if (digitalRead(pulsa) == HIGH) //condicion que cambiara la varaiable de control para el cuarto switch
    control = 5;
  if (digitalRead(pos3) == LOW && digitalRead(pos2) == LOW && digitalRead && (pos1) == LOW && digitalRead(pos0) == LOW)
    //condicion que controlara que cuando se apagen todos los switchs el sistema se apague
    control = 5;
    //-------------------------------------------------------------------------------------------
  switch (control) //se utiliza un ciclo switch con una variable de control para cada juego de luces
  {
    case 1 ://juego de luces impares
      if (digitalRead(pos0) == LOW) {
        control = 0;
      }
      //condicion que controla el estado de on of del pulsador ,si lee que se tiene estado bajo saldra del ciclo sin realizar accion alguna
      else {
        for (; i < 6; i++)
        {
          if (i % 2 == 1) //condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a uno pasa a encender los leds
          { digitalWrite(leds[i], HIGH); //encendido de leds segun la condicion
            delay(200);
          }
        }
        //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
        for (; i >= 0; i--) //
        {
          if (i % 2 == 1) //condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a uno pasa a apagar  los leds
          { digitalWrite(leds[i], LOW);
            delay(200);
          }
        }
        i = 0; //reinicio de la variable de conteo para repetir el ciclo de nuevo

      }
      break;//----------------------------------------------------------------------------------
    case 2://juego de luces pares
      if (digitalRead(pos1) == LOW) {
        control = 0;
      }
      //condicion que controla el estado de on of del pulsador ,si lee que se tiene estado bajo saldra del ciclo sin realizar accion alguna
      else {
        //si el pulsador esta activado se activa el respectivo codigo
        for (; i < 6; i++)
        {
          if (i % 2 == 0) //condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a cero pasa a encender los leds
          { digitalWrite(leds[i], HIGH); //encendido de leds segun la condicion
            delay(200);
          }
        }
        //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
        for (; i >= 0; i--) //
        {
          if (i % 2 == 0) //condicion que verificara el residuo de la dividir la posicion entre 2,si dicho residuo es iguala a cero pasa a apagar  los leds
          { digitalWrite(leds[i], LOW);
            delay(200);
          }
        }
        i = 0; //reinicio de la variable de conteo para repetir el ciclo de nuevo
        break;
      }//-----------------------------------------------------------------------------------------
    case 3 ://juego de luces aleatorias
      if (digitalRead(pos2) == LOW) {
        control = 0;
      }
      //condicion que controla el estado de on of del pulsador ,si lee que se tiene estado bajo saldra del ciclo sin realizar accion alguna
      else {
        //si el pulsador esta activado se activa el respectivo codigo
        for (; i < 6; i++)
        { long  alea = random(6); //
          digitalWrite(leds[alea], HIGH); //encendido de leds segun la condicion
          delay(200);
        }
        //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
        for (; i >= 0; i--) //
        {
          //long  alea = random(6);
          digitalWrite(leds[i], LOW); //encendido de leds segun la condicion
          delay(200);
        }
        i = 0;
        break;
      }//------------------------------------------------------------------------------------------------------------
    case 4 ://juego normal de luces
      if (digitalRead(pos3) == LOW) {
        control = 0;
      }
      //condicion que controla el estado de on of del pulsador ,si lee que se tiene estado bajo saldra del ciclo sin realizar accion alguna
      else {
        //si el pulsador esta activado se activa el respectivo codigo
        for (; i < 6; i++)
        {
          digitalWrite(leds[i], HIGH); //encendido de leds segun la condicion
          delay(200);
        }
        //no se reinicia la variable de conteo ya que sera necesaria para apagar los leds
        for (; i >= 0; i--) //
        {
          digitalWrite(leds[i], LOW);
          delay(200);
        }
        i = 0; //reinicio de la variable de conteo para repetir el ciclo de nuevo
      }
      break;//--------------------------------------------------------------------------------------------------------------------
    case 5 ://Contador Binario
       //contador version 1
      if (digitalRead(pulsa) == LOW) {
        control = 0;
        //while (digitalRead(pulsa)==LOW){}
      } 
      //condicion que controla el estado de on of del pulsador ,si lee que se tiene estado bajo saldra del ciclo sin realizar accion alguna
      else {
        //si el pulsador esta activado se activa el respectivo codigo
        if (digitalRead(pulsa) == HIGH) { //Lectura del estado del botón
          delay(300);
          i++; //Suma 1 al bit menos significativo
        }
        // Primer Bit
        if (i == 0) { //Si no hay nada en el primer bit se queda apagado
          digitalWrite(13, LOW);
        }
        else if (i == 1) { //Si se sumó uno se enciende el led
          digitalWrite(13, HIGH);
        }
        else if (i == 2) { //1+1= 0 y llevo un bit(acarreo)
          digitalWrite(13, LOW);
          i = 0; //El primer bit vuelve a cero luego de la suma
          b++; //Acarreo del bit por la suma de 1+1
          // Segundo Bit
          if (b == 0) { //Si no he acarreado nada permanece apagado
            digitalWrite(12, LOW);
          }
          else if (b == 1) { //Si acarrea un bit se enciende
            digitalWrite(12, HIGH);
          }
          else if (b == 2) { //1+1= 0 y llevo un bit(acarreo)
            digitalWrite(12, LOW);
            b = 0; //Vuelve a cero porque 1+1=0
            c++; //Acarreo de la suma
            // Tercer Bit
            if (c == 0) {
              digitalWrite(11, LOW);
            }
            else if (c == 1) {
              digitalWrite(11, HIGH);
            }
            else if (c == 2) {
              digitalWrite(11, LOW);
              c = 0;
              d++;
              // Cuarto Bit
              if (d == 0) {
                digitalWrite(10, LOW);
              }
              else if (d == 1) {
                digitalWrite(10, HIGH);
              }
              else if (d == 2) {
                digitalWrite(10, LOW);
                d = 0;
                e++;
                // Quinto Bit
                if (e == 0) {
                  digitalWrite(9, LOW);
                }
                else if (e == 1) {
                  digitalWrite(9, HIGH);
                }
                else if (e == 2) {
                  digitalWrite(9, LOW);
                  e = 0;
                  f++;
                  // Sexto Bit
                  if (f == 0) {
                    digitalWrite(8, LOW);
                  }
                  else if (f == 1) {
                    digitalWrite(8, HIGH);
                  }
                  else if (f == 2) {
                    digitalWrite(8, LOW);
                    f = 0;
                  }
                }
              }
            }
          }
        }
       // --------------------------------------
        
        break;
      default :
        //en caso de no presentarse ninguna de las condciones la variable de control pasara a cero y no se realizara acccion alguna
        if (digitalRead(pos0) == LOW)
          control = 0;
        if (digitalRead(pos1) == LOW)
          control = 0;
        if (digitalRead(pos2) == LOW)
          control = 0;
        if (digitalRead(pos3) == LOW)
          control = 0;
        break;
      }
  }
}
