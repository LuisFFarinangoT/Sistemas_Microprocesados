/*
   UTN ---FICA ---CIERCOM
   Segundo Bimestre
   Deber 21
   Nombre :
            Farinago Luis
   Realizar un  programa de un programa que muestre el segundero, minutero y horero visto en una lcd.
*/
#include <MsTimer2.h>//inclusion de librerias necesarias 
#include <LiquidCrystal.h>//librerá de pantalla lcd
LiquidCrystal LCD(3, 4, 5, 6, 7, 8); //pines de habilitacion RS,E,D4,D5,D6,D7
int contseg = 0 ;//variabla para guardar los datos de segundos ,se inicializa en cero
int contmin = 0 ;//variabla para guardar los datos de minutos,se inicializa en cero
int conthor = 0 ;//variabla para guardar los datos de horas ,se inicializa en cero
void setup() {//**********************************************************************************************************
  LCD.begin(16, 2); //inicializar lcd
  Serial.begin(9600);//inicializacion de Cx
  MsTimer2::set(1000, rutina);//iniciliazacion de timer
  MsTimer2::start();//el reloj comeinza a correr
  LCD.setCursor(4, 0);//impresion de datos en LCD
  LCD.print("RELOJ");//impresion de datos en LCD
  LCD.setCursor(3, 1);//impresion de datos en LCD
  LCD.print("00:");//siempre se comienza la impresion de 00 en horas
  LCD.setCursor(6, 1);//impresion de datos en LCD
  LCD.print("00:");//siempre se comienza la impresion de 00 en minutos
  LCD.setCursor(9, 1);//impresion de datos en LCD
  LCD.print("00");//siempre se comienza la impresion de 00 en segundos
}
void rutina()//Interrupcion de tiempo para manejar el reloj
{ //*************************************************************************************************************************************************
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
void loop() {//*****************************************************************************************************************************************

  if (contmin == 59 && contseg == 59 && conthor == 23)//condicion para cuando se alcanza el valor maximo de las variables del reloj
  { conthor = 0;//se iguala a cero para repetir el proceso 
    LCD.setCursor(3, 1);//posicion en la lcd
    LCD.print("00:");//impresion de datos en LCD
    contmin = 0;//se iguala a cero para repetir el proceso 
    contseg = 0;//se iguala a cero para repetir el proceso 
  }
}
