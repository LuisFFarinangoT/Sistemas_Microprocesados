/*
   UTN ---FICA ---CIERCOM
   Segundo Bimestre
   Lab1
   Nombres :
            Farinago Luis
            Herdoiza Adriana
            Lopez Sofia
   Procedimiento a realizar
   Realice un reloj con un pulsador con las funciones de modificar la hora y crear la alarma.
   Otro pulsador para modificar el valor del minutero para actualizar la hora y la alarma y otro que permita actualizar el horero.
*/
#include <MsTimer2.h>//inclusion de librerias necesarias 
#include <LiquidCrystal.h>//libreria¡ de pantalla lcd
LiquidCrystal LCD(4, 5, 6, 7, 8, 9); //pines de habilitacion RS,E,D4,D5,D6,D7
int contseg = 0 ;//variabla para guardar los datos de segundos ,se inicializa en cero
int contmin = 0 ;//variabla para guardar los datos de minutos,se inicializa en cero
int conthor = 0 ;//variabla para guardar los datos de horas ,se inicializa en cero
int controlal = 1;//variable de control para la alarma
String alarmhora;//variable que guardara la hora ingresada por serial
String alarmmin;//variable que guardara los minutos  ingresada por serial
String camhora;//variable que guardara la hora ingresada por serial
String cammmin;//variable que guardara los minutos  ingresada por serial
String str;//variable que guardará la alarma ingresada por serial
int indicador = 10;//indicador para cuando se prenda la alarma
int funS = 0; //variable de control de la interrupción de alarma
int funR;//variable de control de la interrupción de control
int val2;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int val1;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int val3;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int val4;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int pulsamin = 12;//pin de pulsador que controlara la resta de variables del reloj
int pulsahor = 11;//pin de pulsador que controlara el aumento de variables de reloj
int controlinterrup1 = 3;
int controlinterrup2 = 1;
void setup() {//******************************************************************************************************************************
  Serial.begin(9600);
  attachInterrupt(0, alarma, FALLING);//interrupcion de sistema para control general
  attachInterrupt(1, control, FALLING); //interrupcion de sistema para control general
  LCD.begin(16, 2); //inicializar lcd
  Serial.begin(9600);//inicio de Cx
  MsTimer2::set(1000, rutina);//inicializacion de interrupcion de tiempo
  LCD.setCursor(4, 0);//posicion en la lcd
  LCD.print("RELOJ");//impresion de datos en LCD
  LCD.setCursor(3, 1);//posicion en la lcd
  LCD.print("00:");//impresion de datos en LCD
  LCD.setCursor(6, 1);//posicion en la lcd
  LCD.print("00:");//impresion de datos en LCD
  LCD.setCursor(9, 1);//posicion en la lcd
  LCD.print("00");//impresion de datos en LCD
  LCD.setCursor(11, 0);//posicion en la lcd
  LCD.print("AL OFF");//impresion de datos en LCD
  pinMode(indicador, OUTPUT);//declaracion de pines//impresion en LCD
  pinMode(pulsamin, INPUT);
  pinMode(pulsamin, INPUT);
  MsTimer2::start();//inicio de reloj
}
void alarma() {
  if (controlinterrup1 == 0) {
    //**************************************************************************************************************************************************
    { switch (funS)
      { //diferentes situaciones para la variable funcionamiento
        case 0://ingreso de datos
          { controlinterrup2 = 0;
            str = "";//se vacia la cadena que guarda la alarma
            LCD.setCursor(11, 0);//posicion en la lcd
            LCD.print("AL OF");//impresion de datos en LCD
            funS++;//aumento de la variable contador
            digitalWrite(indicador, LOW);//se apaga la alarma cada vez que se inicie el sistema
            Serial.println("ingrese la alarma en formato HH:MM");//impresion de mensaje para ingreso de alarma
          }
          break;
        case 1://lectura de datos
          Serial.println("lectura de datos ");//lectura de datos
          funS++;//aumento de la variable contador
          break;
        case 2://comprobacion de que existe datos ingresados
          { if (str.length() == 0)//se comprueba el tamaño de la cadena
            { funS = 0;//si no existe un dato ingresado ,se regresa al inicio
              Serial.println("no se ingreso alarma");//impresion de mensaje
            }
            else {

              Serial.println(" Alarma Ingresada correctamente");
              LCD.setCursor(11, 0);//posicion en la lcd
              LCD.print("AL ON");//impresion de datos en LCD
              funS++;//aumento de la variable contador
            }
            Serial.println("verificacion completa");//impresion de mensaje
            
          }
          break;
        case 3://se comprobrara los datos de la alarma y su sincronia con el reloj
          {
            funS++;//aumento de la variable contador
            
          }
          break;
        case 4://se termina el proceso
          { 
            Serial.println("Fin");//impresion de mensaje de fin de ciclo
            funS = 0;//se iguala la variable de interrupcion a cero para seguir con el ciclo    
          }
          break;
      }
    }
  }

}
void actualizacion()
{
  if (funR == 2)//condicion de interrupcion para la lectura de datos
  { //se controla con dos pulsadores ,el aumento o decremento de la variaable escogido ya sea horas o min
    if (digitalRead(pulsamin) == HIGH) {//si el pulsador de suma se pulsa ,se aumenta los valores de la variable dada
      delay(300);//retraso del sistema para la lectura de datos
      if (conthor < 23)//se condiciona el numero maximo de las horas
      { conthor++;//si es menor comienza a actura
        String aux4 = String(conthor);//variable que guarda los segundos en una cadena
        if (aux4.length() == 1)//se comprueba el tamaño de la cadena que guarda los segundos
        { //si los segundos se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
          LCD.setCursor(3, 1);//posicion en la lcd
          LCD.print('0');//impresion de datos en LCD
          LCD.setCursor(4, 1);//posicion en la lcd
          LCD.print(conthor);//impresion de datos en LCD
        }
        else
          //si los segundos se encuentran en el rango de 10 a 59 se imprime en un lugar de la pant LCD
        { LCD.setCursor(3, 1);//posicion en la lcd
          LCD.print(conthor);//impresion de datos en LCD
        }
      }
      else
      { conthor = 0;//se iguala la variable a cero
        LCD.setCursor(3, 1);//posicion en la lcd
        LCD.print("00:");//impresion de datos en LCD
      }

    } else if (digitalRead(pulsahor) == HIGH) //se comprueba el estado del pulsador
    { delay(300);//retraso del sistema para la lectura de datos
      if (conthor > 0)//se condiciona el num minimo que acepta la variable
      { conthor--;//se resta cada vez que se presione el pulsador
        String aux5 = String(conthor);//variable que guarda los segundos en una cadena
        if (aux5.length() == 1)//se comprueba el tamaño de la cadena que guarda los segundos
        { //si los segundos se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
          LCD.setCursor(3, 1);//posicion en la lcd
          LCD.print('0');//impresion de datos en LCD
          LCD.setCursor(4, 1);//posicion en la lcd
          LCD.print(conthor);//impresion de datos en LCD
        }
        else
          //si los segundos se encuentran en el rango de 10 a 59 se imprime en un lugar de la pant LCD
        { LCD.setCursor(3, 1);//posicion en la lcd
          LCD.print(conthor);//impresion de datos en LCD
        }
      }
      else
      { conthor = 0;//si no se cumplen las condiciones se iguala la variable a cero
        LCD.setCursor(3, 1);//posicion en la lcd
        LCD.print("00:");//impresion de datos en LCD
      }
    }
  }
  if (funR == 3)//condicion de interrupcion para modificar la hora
  { if (digitalRead(pulsamin) == HIGH) //se comprueba el estado del pulsador
    { delay(300);//retraso del sistema para la lectura de datos
      if (contmin < 59)//se condiciona el num maximo  que acepta la variable
      { contmin++;//se aumenta la variable de contador
        String aux6 = String(contmin);//variable que guarda los segundos en una cadena
        if (aux6.length() == 1)//se comprueba el tamaño de la cadena que guarda los segundos
        { //si los segundos se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
          LCD.setCursor(6, 1);//posicion en la lcd
          LCD.print('0');//impresion de datos en LCD
          LCD.setCursor(7, 1);//posicion en la lcd
          LCD.print(contmin);//impresion de datos en LCD
        }
        else
          //si los segundos se encuentran en el rango de 10 a 59 se imprime en un lugar de la pant LCD
        { LCD.setCursor(6, 1);//posicion en la lcd
          LCD.print(contmin);//impresion de datos en LCD
        }
      }
      else
      { contmin = 0;//si no se cumplen las condiciones se iguala la variable a cero
        LCD.setCursor(6, 1);//posicion en la lcd
        LCD.print("00:");//impresion de datos en LCD
      }

    } else if (digitalRead(pulsahor) == HIGH)//se comprueba el estado del pulsador
    {
      delay(300);//retraso del sistema para la lectura de datos
      if (contmin > 0)//se condiciona el numero maximo al que llegara el contador
      { contmin--;// se resta el contador
        String aux7 = String(contmin);//variable que guarda los segundos en una cadena
        if (aux7.length() == 1)//se comprueba el tamaño de la cadena que guarda los segundos
        { //si los segundos se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
          LCD.setCursor(6, 1);//posicion en la lcd
          LCD.print('0');//impresion de datos en LCD
          LCD.setCursor(7, 1);//posicion en la lcd
          LCD.print(contmin);//impresion de datos en LCD
        }
        else
          //si los segundos se encuentran en el rango de 10 a 59 se imprime en un lugar de la pant LCD
        { LCD.setCursor(6, 1);//posicion en la lcd
          LCD.print(contmin);//impresion de datos en LCD
        }
      }
      else
      { contmin = 0;//si no se cumplen las condicicones se vacia el contador
        LCD.setCursor(6, 1);//posicion en la lcd
        LCD.print("00:");//impresion de datos en LCD
      }
    }
  }
}
void control()
{ //ciclo de control de las configuraciones del reloj
  if (controlinterrup2 == 1)
  {
    switch (funR)//se toma los diferentes valores de la variable
    { case 0:
        MsTimer2::stop();//se detiene el reloj cuando se va a configurar el reloj
        controlinterrup1 = 1; //se asigna una variable de control para cuando se detiene el reloj
        //variable de control para evitar que las dos interrupciones de ejecuten ala vez
        funR++;//aumento de contador
        Serial.println("Configuraciones de reloj");//impresion de datos en Serial
        break;
      case 1://configuraciones de hora
        funR++;//aumento de contador
        Serial.println("Configuraciones de hora ");//impresion de datos en Serial
        break;
      case 2://configuraciones de min
        Serial.println("Configuraciones de min ");//impresion de datos en Serial
        funR++;//aumento de contador
        break;
      case 3://Se actualiza los datos que se ingresaron
        Serial.println("Actualizacion de datos ");//impresion de datos en Serial
        MsTimer2::start();//se inicia de nuevo el reloj cuando se ingresaron los datos
        controlinterrup1 = 0; //se cambia la variable de control para permitir que funcione la puesta de alarma
        Serial.println(contmin);
        funR++;//aumento de contador
        break;
      case 4:
        funR = 0; //se iguala a cero para que el clclo comience de nuevo
        break;
    }
  }



}
void rutina()
{{ //*************************************************************************************************************************************************
    if (contseg < 59)//se comprueba el valor de los segundos
    {
      contseg ++;//se aumenta el valor hasta que llegue a 59
      String aux1 = String(contseg);//variable que guarda los segundos en una cadena
      if (aux1.length() == 1)//se comprueba el tamaño de la cadena que guarda los segundos
      { //si los segundos se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
        LCD.setCursor(9, 1);//posicion en la lcd
        LCD.print('0');//impresion de datos en LCD
        LCD.setCursor(10, 1);//posicion en la lcd
        LCD.print(contseg);//impresion de datos en LCD
      }
      else
        //si los segundos se encuentran en el rango de 10 a 59 se imprime en un lugar de la pant LCD
      { LCD.setCursor(9, 1);//posicion en la lcd
        LCD.print(contseg);//impresion de datos en LCD
      }
    }
    else if (contseg == 59)//cuando se llega a 59 se imprime ceros en la variable segundos
    { LCD.setCursor(9, 1);//posicion en la lcd
      LCD.print("00");//impresion de datos en LCD

      if (contmin < 59)//condicion de conteo para los minutos
      {
        contseg = 0;//se iguala a cero para hacer la transicion de 1 min =60s
        contmin++;//aumento de la variable de contador
        String aux2 = String(contmin);//se comprueba el tamaño de la cadena que guarda los minutos
        if (aux2.length() == 1)
          //si los minutos  se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
        { LCD.setCursor(6, 1);//posicion en la lcd
          LCD.print('0');//impresion de datos en LCD
          LCD.setCursor(7, 1);//posicion en la lcd
          LCD.print(contmin);//impresion de datos en LCD
        }
        else
          //si los minutos  se encuentran en el rango de 10 a 59 se imprime en un lugar de la pant LCD
        { LCD.setCursor(6, 1);//posicion en la lcd
          LCD.print(contmin);//impresion de datos en LCD
        }
      }
    }
    if (contmin == 59 && contseg == 59)//cuando se llega a 59 se imprime ceros en la variable segundos y minutos
    { LCD.setCursor(6, 1);//posicion en la lcd
      LCD.print("00:");//impresion de datos en LCD
      LCD.setCursor(9, 1);//posicion en la lcd
      LCD.print("00");//impresion de datos en LCD

      if ( conthor < 23)//condicion para el aumento de horas
      {
        conthor++;//se aumenta el valor de horas
        Serial.println(conthor);
        contmin = 0;//se iguala a cero para hacer la transicion de 60 min =1h
        contseg = 0;//se iguala a cero para hacer la transicion de 1 min =60s
        String aux3 = String(conthor);
        if (aux3.length() == 1)//se comprueba el tamaño de la cadena que guarda las horas
          //si las horas  se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
        { LCD.setCursor(3, 1);//posicion en la lcd
          LCD.print('0');//impresion de datos en LCD
          LCD.setCursor(4, 1);//posicion en la lcd
          LCD.print(conthor);//impresion de datos en LCD
        }
        else
          //si las horas   se encuentran en el rango de 10 a 23 se imprime en un lugar de la pant LCD
        { LCD.setCursor(3, 1);//posicion en la lcd
          LCD.print(conthor);//impresion de datos en LCD
        }
      } else {//si el contador de horas llega a 23
        conthor = 0;//se iguala a cero para repetir el ciclo
        LCD.setCursor(3, 1);//posicion en la lcd
        LCD.print("00:");//impresion de datos en LCD
      }
    }
  }
}
void loop() {
  if (contmin == 59 && contseg == 59 && conthor == 23)//condicion para cuando se alcanza el valor maximo de las variables del reloj
  { conthor = 0;//se iguala a cero para repetir el proceso
    LCD.setCursor(3, 1);//posicion en la lcd
    LCD.print("00:");//impresion de datos en LCD
    contmin = 0;//se iguala a cero para repetir el proceso
    contseg = 0;//se iguala a cero para repetir el proceso
  }
  if (contmin == 59 && contseg == 59 && conthor == 22)//condicion para cuando se alcanzan los valores maximos
  { conthor = 0;////se iguala la variable de interrupcion a cero para seguir con el ciclo
    LCD.setCursor(3, 1);//posicion en la lcd
    LCD.print("00:");//impresion de datos en LCD
    contmin = 0;//se iguala la variable a cero para seguir con el ciclo
    contseg = 0;//se iguala la variable a cero para seguir con el ciclo
  }
  if (funS == 1) {//condicion de la interrupcio para leer los datos
    if (Serial.available() > 0) {//comprobaciond de C.x
      str = Serial.readString();//Recibe en caracteres//ingreso de la cadena
      int tam = str.length();//tamaÃ±o de la cadena ingresada para calculos futuros
      if (str.charAt(2) == ':' && str.length() == 5)//se valida la cadena asi como su tamaño
      { Serial.println("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
        for (int i = 0; i < tam; i++) { //recorrido de la cadena
          if (str.charAt(i) == ':') //condiciones de reconocimiento de vocales
          {
            alarmhora = str.substring(0, i );//se obtiene la subcadena de horas
            alarmmin = str.substring(i + 1, str.length());//se obtiene la subcadena de min
          }
        }
        val3 = alarmhora.toInt(); //se transforma los datos obtenidos  enteros
        val4 = alarmmin.toInt(); //se transforma los datos obtenidos  enteros
      } else {//si no se cumple los valores se regresa al inicio
        Serial.println("VALOR INVALIDO");//impresion de valor en serial
        str = "";//se vacia la variable  para seguir con el ciclo
        funS = 0;//se iguala la variable a cero para seguir con el ciclo
      }

      if (val3 > 23)//validacion de numeros mayores a 24
      { Serial.println("VALOR DE HORA EXCEDIDO");//impresion de valor en serial
        funS = 0;//se iguala la variable a cero para seguir con el ciclo
        str = "";//se vacia la variable  para seguir con el ciclo
        alarmmin = "";//se vacia la variable  para seguir con el ciclo
        alarmhora = "";//se vacia la variable  para seguir con el ciclo
      }
      if (val4 > 59)//validacion de numeros mayores a 60
      { Serial.println("VALOR DE MIN EXCEDIDO");//impresion de valor en serial
        funS = 0;//se iguala la variable a cero para seguir con el ciclo
        str = "";//se vacia la variable  para seguir con el ciclo
        alarmmin = "";//se vacia la variable  para seguir con el ciclo
        alarmhora = "";//se vacia la variable  para seguir con el ciclo
      }
    }
  }
  if (funS == 3)//condicion para la comparacion de los datos de la alarma ingresao con la alarma
  {
    val1 = alarmmin.toInt();//se transforma los datos obtenidos  enteros
    val2 = alarmhora.toInt();//se transforma los datos obtenidos  enteros
    if (contmin == val1 && conthor == val2)//se compara los valores en min y horas con los ingresados por serila
    { Serial.println("------------------------");
      controlal = 1;//se cambia el valor de la variable de control
      alarmmin = "";//se vacia la variable  para seguir con el ciclo
      str = "";//se vacia la variable  para seguir con el ciclo
      alarmhora = "";//se vacia la variable  para seguir con el ciclo
      funS = 0;//se iguala la variable a cero para seguir con el ciclo
      val1 = 0;//se iguala la variable a cero para seguir con el ciclo
      val2 = 0;//se iguala la variable a cero para seguir con el ciclo
    } else {//condicion para cuando la alarma no ha sonado
      controlal = 0; //se iguala la variable a cero para seguir con el ciclo
    }
    if (controlal == 1)//condicion de la variable de control,1 es para alarma encendida
    {
      digitalWrite(indicador, HIGH);//se enciende el indicador de alarma
      funS = 0;//se iguala la variable a cero para seguir con el ciclo
      controlinterrup2 = 1;
    }
    else if (controlal == 0) {//condicion de la variable de control,1 es para alarma apagada
      digitalWrite(indicador, LOW);//se apaga el indicador
    }
  }
  actualizacion();//se llama al metodo de actualizar la hora
}
