/*
   UTN ---FICA ---CIERCOM
   Segundo Bimestre 
   Deber 2 
   Realizar un programa de un reloj con alarma que sea ingresada por comunicacion serial.
   Nombre :
            Farinago Luis
*/
#include <MsTimer2.h>//inclusion de librerias necesarias 
#include <LiquidCrystal.h>//libreria¡ de pantalla lcd
LiquidCrystal LCD(3, 4, 5, 6, 7, 8); //pines de habilitacion RS,E,D4,D5,D6,D7
int contseg = 0 ;//variabla para guardar los datos de segundos ,se inicializa en cero
int contmin = 0 ;//variabla para guardar los datos de minutos,se inicializa en cero
int conthor = 0 ;//variabla para guardar los datos de horas ,se inicializa en cero
String alarmhora;//variable que guardara la hora ingresada por serial 
String alarmmin;//variable que guardara los minutos  ingresada por serial 
String str;//variable que guardará la alarma ingresada por serial 
int indicador = 9;//indicador para cuando se prenda la alarma 
int funS;//variable de control de la interrupción 
int control = 1;//variable de control para la alarma 
int val2;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int val1;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int val3;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
int val4;//variable para guardar datos de las transformaciones de las cadenas de alarma y reloj
void rutina()//****************************************************************************************************************
{
  if (contseg < 59)//condicion para contar los segundos 
  {
    contseg ++;//aumento de contador 
    String aux1 = String(contseg);//se obtiene una cadena con los datos de los segundos 
    if (aux1.length() == 1)//se comprueba el tamaño de la cadena 
    //si los segundos se encuentran en el rango de 0 a 9 se imprime en un lugar de la pant LCD
    { LCD.setCursor(9, 1);//posicion en la lcd
      LCD.print('0');//impresion de datos en LCD
      LCD.setCursor(10, 1);//posicion en la lcd
      LCD.print(contseg);//impresion de datos en LCD
    }
    else//cuando el valor de segundos excede el 1 digito se imprime en una posicion de la ptlla lcd
    { LCD.setCursor(9, 1);//posicion en la lcd
      LCD.print(contseg);//impresion de datos en LCD
    }
  }
  else if (contseg == 59)//cuando se alcanza el valor maximo en segundos se imprime ceros en la ptlla lcd
  { LCD.setCursor(9, 1);//posicion en la lcd
    LCD.print("00");//impresion de datos en LCD
    if (contmin < 59)//condicion para contador de min 
    {
      contseg = 0;//se vacia la variable segundos para 
      contmin++;//aumento de contador 
      String aux2 = String(contmin);////se obtiene una cadena con los datos de los minutos 
      if (aux2.length() == 1)//se compara para saber si tiene un digito se imprime en una posicion de la ptlla lcd
      { LCD.setCursor(6, 1);//posicion en la lcd
        LCD.print('0');//impresion de datos en LCD
        LCD.setCursor(7, 1);//posicion en la lcd
        LCD.print(contmin);//impresion de datos en LCD
      }
      else//si se tiene mas de dos digotos se imprime en una posicion de la ptlla lcd
      { LCD.setCursor(6, 1);//posicion en la lcd
        LCD.print(contmin);//impresion de datos en LCD
      }
    }
  }
  if (contmin == 59 && contseg == 59)//condicion para cuando se llega a valores maximos de min y seg 
  { LCD.setCursor(6, 1);//posicion en la lcd
    LCD.print("00:");//impresion de datos en LCD
    LCD.setCursor(9, 1);//posicion en la lcd
    LCD.print("00");//impresion de datos en LCD
    if ( conthor < 23)//condicion de aumento de contador
    {
      conthor++;//aumento de contador 
      contmin = 0;//se iguala a cero por la relacion 1h=60s
      contseg = 0;//se iguala a cero por la relacion 1h=60s
      String aux3 = String(conthor);//se obtiene una cadena con los datos de los minutos
      if (aux3.length() == 1)//se compara para saber si tiene un digito se imprime en una posicion de la ptlla lcd
      { LCD.setCursor(3, 1);//posicion en la lcd
        LCD.print('0');//impresion de datos en LCD
        LCD.setCursor(4, 1);//posicion en la lcd
        LCD.print(conthor);//impresion de datos en LCD
      }
      else//se compara para saber si se tiene mas de un digito y se imprime en una posicion de la ptlla lcd
      { LCD.setCursor(3, 1);//posicion en la lcd
        LCD.print(conthor);//impresion de datos en LCD
      }
    } else {//condicion para el valor maximo de horas 
      conthor = 0;//se vacia la variable para iniciar el ciclo de nuevo 
      LCD.setCursor(3, 1);//posicion en la lcd
      LCD.print("00:");//impresion de datos en LCD
    }
  }


}
void alarma()//**************************************************************************************************************************************************
{ switch (funS)
  { //diferentes situaciones para la variable funcionamiento
    case 0://ingreso de datos
      { str = "";//se vacia la cadena que guarda la alarma 
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
      { Serial.println("Fin");//impresion de mensaje de fin de ciclo
        funS = 0;//se iguala la variable de interrupcion a cero para seguir con el ciclo
      }
      break;
  }
}
void setup() {
  Serial.begin(9600);
  attachInterrupt(0, alarma, LOW);//interrupcion de sistema para control general
  LCD.begin(16, 2); //inicializar lcd
  Serial.begin(9600);//inicio de Cx
  MsTimer2::set(10, rutina);//inicializacion de interrupcion de tiempo 
  LCD.setCursor(4, 0);//posicion en la lcd
  LCD.print("RELOJ");//impresion de datos en LCD
  LCD.setCursor(3, 1);//posicion en la lcd
  LCD.print("00:");//impresion de datos en LCD
  LCD.setCursor(6, 1);//posicion en la lcd
  LCD.print("00:");//impresion de datos en LCD
  LCD.setCursor(9, 1);//posicion en la lcd
  LCD.print("00");//impresion de datos en LCD
  LCD.setCursor(11, 0);//posicion en la lcd
  LCD.print("AL OF");//impresion de datos en LCD
  pinMode(indicador, OUTPUT);//declaracion de pines//impresion en LCD
  MsTimer2::start();//inicio de reloj 
}

void loop() {
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
        val3=alarmhora.toInt();//se transforma los datos obtenidos  enteros 
        val4=alarmmin.toInt();//se transforma los datos obtenidos  enteros 
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
      control = 1;//se cambia el valor de la variable de control
      alarmmin = "";//se vacia la variable  para seguir con el ciclo
      str = "";//se vacia la variable  para seguir con el ciclo
      alarmhora = "";//se vacia la variable  para seguir con el ciclo
      funS = 0;//se iguala la variable a cero para seguir con el ciclo
      val1 = 0;//se iguala la variable a cero para seguir con el ciclo
      val2 = 0;//se iguala la variable a cero para seguir con el ciclo
    } else {//condicion para cuando la alarma no ha sonado
      control = 0;//se iguala la variable a cero para seguir con el ciclo
    }
    if (control == 1)//condicion de la variable de control,1 es para alarma encendida
    {
      digitalWrite(indicador, HIGH);//se enciende el indicador de alarma 
      funS = 0;//se iguala la variable a cero para seguir con el ciclo
    }
    else if (control == 0) {//condicion de la variable de control,1 es para alarma apagada 
      digitalWrite(indicador, LOW);//se apaga el indicador 
    }
  }

}
