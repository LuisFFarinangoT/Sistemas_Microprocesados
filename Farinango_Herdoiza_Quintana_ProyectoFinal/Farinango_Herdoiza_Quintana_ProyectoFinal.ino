
#include <Keypad.h>
#include <LiquidCrystal.h>//librerá de pantalla lcd
LiquidCrystal LCD(12, 13, 19, 18, 17, 16); //pines de habilitacion RS,E,D4,D5,D6,D7
/*
   UTN ---FICA ---CIERCOM
   PROYECTO FINAL DE SISTEMAS MICROPROCESADOS
   Nombres :
            Farinago Luis
            Herdoiza Adriana
            Quintana Karen
  La empresa XYZ le solicita que realice un sistema de seguridad y acceso para su edificio. Las indicaciones son las siguientes.
    1.  Debe tener un ingreso y salida de los empleados mediante una contraseña individual por ingreso de teclado matricial.
    2.  Las contraseñas deben ser de 5 dígitos y hay que validar ese número.
    3.  Son 4 trabajadores.
    4.  Si alguno de los empleados se olvida la contraseña, es necesario que el personal administrativo digite su contraseña master y permita el cambio de la contraseña olvidada.
    5.  Desea contabilizar el número de clientes por día que ingresan a las instalaciones. Al final de día, se puede observar el número final en displays.
    6.  Al terminar la jornada del día, se ingresa una nueva contraseña por comunicación serial para activar la alarma. Si alguien ingresa y el sensor lo detecta se enciende una alarma hasta que se ingrese la misma contraseña.
    7.  Se necesita interrupciones para dar un mejor funcionamiento al sistema.
*/
int sensor = 14;
int indicador = 15;
int funS = 0; //variable interrupción 0
int users = 0; //variable interrupción 1
int cont = 0;//variable de contador de personas
int fallos = 0;//variable de fallos
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char tecla1[1] = {'1'}; //Caracteres en la tecla 1
int t1 = 0; //variable para contador
char tecla2 [1] = {'2'}; //Caracteres en la tecla 2
int t2 = 0; //variable para contador
char tecla3 [1] = {'3'}; //Caracteres en la tecla 3
int t3 = 0; //variable para contador
char tecla4 [1] = {'4'}; //Caracteres en la tecla 4
int t4 = 0; //variable para contador
char tecla5 [1] = {'5'}; //Caracteres en la tecla 5
int t5 = 0; //variable para contador
char tecla6 [1] = {'6'}; //Caracteres en la tecla 6
int t6 = 0; //variable para contador
char tecla7 [1] = {'7'}; //Caracteres en la tecla 7
int t7 = 0; //variable para contador
char tecla8 [1] = {'8'}; //Caracteres en la tecla 8
int t8 = 0; //variable para contador
char tecla9 [1] = {'9'}; //Caracteres en la tecla 8
int t9 = 0; //variable para contador
char supermaster[5] = {'1', '2', '3', '4', '5'};
char usuario1[5] = {'5', '4', '3', '2', '1'};
char usuario2[5] = {'8', '5', '2', '3', '1'};
char usuario3[5] = {'2', '5', '8', '9', '7'};
char usuario4[5] = {'7', '9', '1', '3', '5'};
char alarma[5] = {'A', 'A', 'A', 'A', 'A'};;
int alm = 0;//varaiable de decision
int i = 0;//varaiable de contador para vectores
int estado = 0; //0= nada, 1=es master, 2=es cambio de contrasenia
char usuario;//variable que guarda los datos ingresaddos
char ingreso[5] = {};//variable que guarda los datos ingresaddos
char hexaKeys[ROWS][COLS] = {//datos de teclado
  {'1', '2', '3', 'W'},
  {'4', '5', '6', 'X'},
  {'7', '8', '9', 'Y'},
  {'E', '0', 'D', 'Z'}
};
byte rowPins[ROWS] = {4, 5, 6 , 7 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10, 11}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup() {//*******************************************************************************************************************************************************
  LCD.begin(16, 2); //inicializar lcd
  Serial.begin(9600);//inicio de comunicacion serial
  attachInterrupt(0, sistema, FALLING);//interrupcion de sistema para control general
  attachInterrupt(1, usuarios, FALLING);//interrupcion de sistema para control interno de contraseñas
  LCD.clear();//se limpia la lcd
  pinMode(sensor, INPUT);//declaracion de pines
  pinMode(indicador, OUTPUT);//declaracion de pines//impresion en LCD
}
void sistema() //**********************************************************************************************************************************************************
{
  switch (funS) {//diferentes situaciones para la variable funcionamiento
    case 0://condicion de inicio de sistema
      Serial.println("Inicio de dia");
      funS++;//aumento de contador
      LCD.setCursor(0, 0);//impresion en LCD
      LCD.print("INICIO DE DIA...............");//impresion en LCD
      LCD.setCursor(0, 1);//impresion en LCD
      LCD.print("...............");//impresion en LCD
      break;
    case 1://condicion para ingreso de empleados
      Serial.println("ingreso de empleados ");//impresión de información
      funS ++;//aumento de contador
      LCD.setCursor(0, 0);//impresion en LCD
      LCD.print("INGRESO EMPLEAD...............");//impresion en LCD
      LCD.setCursor(0, 1);//impresion en LCD
      LCD.print("...............");//impresion en LCD
      break;//condicion de finalización de dia
    case 2://condición que permite realizar las operaciones del sistema
      Serial.println("Dia finalizado ");//impresión de información
      funS++;//aumento de contador
      LCD.setCursor(0, 0);//impresion en LCD
      LCD.print("NUMERO PERSONAS IN ...............");//impresion en LCD
      LCD.setCursor(0, 1);//impresion en LCD
      LCD.setCursor(13, 1);//impresion en LCD
      LCD.print(cont);//impresion en LCD
      break;
    case 3://condicion que regula la salida de empleados
      Serial.println("Salida de empleados");//impresión de información
      funS++;;//contador  aumenta
      LCD.setCursor(0, 0);//impresion en LCD
      LCD.print("SALIDA EMPLEA...............");//impresion en LCD
      LCD.setCursor(0, 1);//impresion en LCD
      LCD.print("...............");//impresion en LCD
      break;
    case 4://condicion de ingreso de alarma
      Serial.println("ingrese contraseña de alarma");//impresión de información
      funS++;//contador aumenta
      LCD.setCursor(0, 0);//impresion en LCD
      LCD.print("PSWD ALARMA...............");//impresion en LCD
      LCD.setCursor(0, 1);//impresion en LCD
      LCD.print("...............");//impresion en LCD
      break;
    case 5://condicion que apaga el sistema
      if (alm == 1) {//se lee una variable condcional para que solo ingrese si se mete una contraseña de alarma
        Serial.println("SEGURIDAD ON");//impresión de información
        funS++;//aumento de contador
        LCD.setCursor(0, 0);//impresion en LCD
        LCD.print("ALARMA ON...............");//impresion en LCD
        LCD.setCursor(0, 1);//impresion en LCD
        LCD.print("...............");//impresion en LCD
        //Serial.println(funS);
      } else {
        funS = 5;//si no se detecta ingreso de contraseña no avanzara a otra condicion
      }
      break;
    case 6:
      if (cont == 0) {//condicion para apagar la alarma
        funS = 0;//se iguala a cero la variable
      }
      break;
    case 7://caso para cuando se detecte un intruso
      Serial.println("ALARMA REQUIERE PASSWORD  ");//impresion en LCD
      LCD.setCursor(0, 0);//impresion en LCD
      LCD.print("INTRUSOS DETE...............");//impresion en LCD
      LCD.setCursor(0, 1);//impresion en LCD
      LCD.print("...............");//impresion en LCD
      break;
      //fin de la interrupcion
  }
}
void usuarios() {//interrupcion de manejo de contraseñas
  if (funS == 2 || funS == 4) {//solo se pondrán a funcionar cuando se ingrese o salga del almacén
    switch (users) {//diferentes situaciones para la variable funcionamiento
      case 0://condicion de inicio de ingreso
        Serial.println("Seccion de Ingreso de contra ");
        users++;//aumento de contador
        break;
      case 1://condición para saber que usuario se ingresa
        Serial.println("Presione su boton de usuario e ingrese su contraseña");//impresión de información
        users ++;//aumento de contador
        break;
      case 2://condición que decir que ya ingresaron todos los usuarios
        Serial.println("Fin de contraseñas");//impresión de información
        users++;//aumento de contador
        break;
      case 3://condicion termina la interrupcion
        Serial.println("Continue operando");//impresión de información
        users = 0;//contador  cero para comenzar de nuevo el ciclo
        cont = 0;//contador a cero
        break;
    }//fin de la interrupcion
  }
}
void teclado(char vect[], char customKey)//metodo que guarda los datos que se presionen en el teclado
{ if (i < 5)//se regula la cantidad de caracteres permitidos
   {vect[i] = customKey;//los datos ingresados se guardan en un vector
    Serial.print(customKey);
    LCD.setCursor(0, 0);//impresion en LCD
    LCD.print(vect);//impresion en LCD

    i++;//se aumenta el contador para controlar el tamaño del vector 
  }
  else {
    i = 0;//si se llega a cinco se resetea la ariable de conteo
  }
}

void llenarvector(char vector1[], char vector2[]) {//metodo para llenar un vector a traves de otro
  for (int j = 0; j < 5; j++) {//se recorre el vector 
    vector1[j] = vector2[j];//se llena el vector 
  }
}
int compara(char ingreso[], char contrasenia[]) {//Metodo para comparacion de contraseñas en base a los parámetros presentados 
  int correcta = 2;//variable de control
  if (ingreso[0] == contrasenia[0] && ingreso[1] == contrasenia[1] && ingreso[2] == contrasenia[2] && ingreso[3] == contrasenia[3] && ingreso[4] == contrasenia[4])
  { Serial.println("contraseña correcta");//se compara los vectores 
    LCD.setCursor(0, 1);//Impresión en la pantalla LCD
    LCD.print("CORRECT PSWD...............");//Impresión en la pantalla LCD
    Serial.println("Continue operando");//Impresión de datos en serial 
    correcta = 1;//se cambia la variable de control 
    i = 0;//se iguala la variable a cero para repetir el ciclo 
    contrasenia[5] = {};//se vacia la contra ingresada
  } else {//condicicion para cuando no se cumple la condicion 
    LCD.setCursor(0, 1);//Impresión en la pantalla LCD
    LCD.print("INCORRECT PSWD...............");//Impresión en la pantalla LCD
    Serial.println("contraseña incorrecta");//Impresión de datos en serial 
    //Serial.println(contrasenia);
    correcta = 0;//se cambia la variable de control
    contrasenia[5] = {};//se vacia la contra ingresada
    if (estado == 0) {//se controla una variable de estado para cuando sea la contraseña incorrecta 
      fallos++;//se aumenta un contador de fallos
      Serial.println("Numero de intentos restantes");//Impresión de datos en serial 
      Serial.println(3 - fallos);//Impresión de datos en serial 
    }
    if (fallos == 3)//se controla que solo exista tres intentos de fallos
    {
      fallos = 0;//se resetea la contraseña 
      Serial.println("ingrese contraseña master");//Impresión de datos en serial 
      LCD.setCursor(0, 1);//Impresión de datos en LCD
      LCD.print("INGRE PSWD MASTER...............");//Impresión de datos en LCD
      estado = 1;//se cambia la variable de estado 
    }
  }
  return correcta;//el metodo retorna la variable de control correcta para saber que estoy comparando 
}
int igualdadcontra(char usuarioX[], char ingreso[]) {//método para saber si una contrasela ya existe 
  int coincidencias = 0;//se inicializa una variable de repeticiones 
  for (int k = 0; k < 5; k++) {//se recorre el vector de las contraseña
    if (usuarioX[k] == ingreso[k]) {//se realiza la comparacion 
      coincidencias++;//por cada coincidencia se aumenta el contador ,se debe tener en cuenta que puede existir hasta 4 coincidencias 
    }
  }
  return coincidencias;//el método retorna las coincidencias 
}

void cambiarcontra(char usuarioX[], char ingreso[]) {//metodo para verificar si las contraseñas son repetidas entre si 
  int verifica1 = igualdadcontra(usuario1, ingreso);//llamamos la metodo que bota las coincidencias 
  int verifica2 = igualdadcontra(usuario2, ingreso);//llamamos la metodo que bota las coincidencias 
  int verifica3 = igualdadcontra(usuario3, ingreso);//llamamos la metodo que bota las coincidencias 
  int verifica4 = igualdadcontra(usuario4, ingreso);//llamamos la metodo que bota las coincidencias 

  if (verifica1 == 5 || verifica2 == 5 || verifica3 == 5 || verifica4 == 5) {//se compara si hay mas de 4 coincidencias 
    Serial.println("Ingrese otra contraseña");//Impresion de datos en Cx
    LCD.setCursor(0, 1);//impresion en pantalla LCD
    LCD.print("PSWD REPETIDA...............");//impresion en pantalla LCD
    estado = 2;//se cambia la variable de estado 
  } else {//condicion para cuando no se cumple las repeticiones 
    llenarvector(usuarioX, ingreso);//se guarda los contraseñas ingresadas 
    LCD.setCursor(0, 1);//impresion en pantalla LCD
    LCD.print("PSWD ACEPTADA...............");//impresion en pantalla LCD
    Serial.println("Su nueva contraseña es ");//impresion en Cx
    Serial.print(ingreso);//impresion en Cx
    Serial.println("Continue operando");//impresion en Cx
    estado = 0;//se cambia la variable de estado 
  }
}

void guardarnueva(char customKey) {//metodo para guardar una nueva contraseña 
  switch (customKey) {//condicion de llenado de teclas 
      delay(300);
    case '1'://tecla 1
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '2'://tecla 2
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '3'://tecla 3
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");
      break;
    case '4'://tecla 4
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '5'://tecla 5
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '6'://tecla 6
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '7'://tecla 7
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '8'://tecla 8
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '9'://tecla 9
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case '0'://tecla 0
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      LCD.setCursor(6, 1);//impresion en pantalla LCD
      LCD.print("...................");//impresion en pantalla LCD
      break;
    case 'E': {//boton que ingresa los datos 
        if (i == 5) {//se controla el tamaño de la contraseña
          if (usuario == 'W') {//se controla el usuario que esta ingresando 
            cambiarcontra(usuario1, ingreso);//si se cumple se cambia la contraseña 
            LCD.setCursor(0, 1);//impresion en pantalla LCD
            LCD.print("...................");//impresion en pantalla LCD
          } else if (usuario == 'X') {//se controla el usuario que esta ingresando 
            cambiarcontra(usuario2, ingreso);//si se cumple se cambia la contraseña
            LCD.setCursor(0, 1);//impresion en pantalla LCD
            LCD.print("...................");//impresion en pantalla LCD
          } else if (usuario == 'Y') {//se controla el usuario que esta ingresando 
            cambiarcontra(usuario3, ingreso);//si se cumple se cambia la contraseña
            LCD.setCursor(0, 1);//impresion en pantalla LCD
            LCD.print("...................");//impresion en pantalla LCD
          } else if (usuario == 'Z') {//se controla el usuario que esta ingresando 
            cambiarcontra(usuario4, ingreso);//si se cumple se cambia la contraseña
            LCD.setCursor(0, 1);//impresion en pantalla LCD
            LCD.print("...................");//impresion en pantalla LCD
          }

        } else {
          Serial.println("numero no permitido");//si no se cumple el tamaño se bota un mensaje 
        }
      }
  }
}
void contra(char customKey, char ingreso[], char master[]) { //metodo que controla el ingreso de contraseñas //**************************************************************************************
  // if (customKey) {
  switch (customKey) {//condicion de ingreso de caracteres por teclado 
      delay(300);//retraso para que el sistema se retraso
    case '1'://tecla 1
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '2'://tecla 2
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '3'://tecla 3
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '4'://tecla 4
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '5'://tecla 5
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '6'://tecla 6
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '7'://tecla 7
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '8'://tecla 8
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case '9':
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
    case 'E'://tecla que controla el ingreso de contraseñas (enter)

      {
        LCD.setCursor(0, 1);//impresion en pantalla LCD
        LCD.print("...................");//impresion en pantalla LCD
        Serial.println(master);//impresion de master 
        if (i == 5 && sizeof(master) > 1)//conprueba que se cumple el tamaño de contrasela y exista una master 
        {
          switch (estado) {//se utiliza la variable de estado 
            case 0: {// compara si coincide contraseña ingresada con usuario seleccionado
                compara(ingreso, master);//se compara la ingresa con la master
                break;
              }
            case 1: {// cuando ha fallado tres veces compara que la contraseña de master sea correcta
                if (compara(ingreso, supermaster) == 1) {//se compara la ingresa con la master
                  estado = 2;//se cambia la variable de estado
                  Serial.println("Escriba nueva contraseña ");//se envia los mensaje por Cx
                  LCD.setCursor(0, 1);//impresion en pantalla LCD
                  LCD.print("INGRESE NEW PSWD...............");//impresion en pantalla LCD
                }
                break;
              }
            case 2: {// si contraseña de master fue correcta guarda nueva contraseña
                guardarnueva(customKey);//se llama al metodo de guardado
                LCD.setCursor(0, 1);//impresion en pantalla LCD
                LCD.print("...................");//impresion en pantalla LCD
                break;
              }
            case 3: {//condcion que controla la contraseña de alarma 
                llenarvector(alarma, ingreso);//se guarda el vector de alarma 
                if (alarma[0] != 'A') {//se realiza las comprobacions para saber si ingreso algo de contraseña
                  estado = 0;//se resetea la varaiable de estado
                  alm = 1; //se pone igual a 1 porque se ingreso contraseña de alarma
                  cont = 0;//reseteo de contador 
                  Serial.println("Contraseña ingresada");//impresion en Cx
                  LCD.setCursor(0, 1);//impresion en pantalla LCD
                  LCD.print("PSWD SEG ON...............");//impresion en pantalla LCD
                  Serial.println("Alarma encendida");//impresion en Cx
                }
                break;
              }
            case 4: {//condicion para cuando se activa la alarma y es necessario ingresar la contraseña para desactivarla 
                if (ingreso[0] == master[0] && ingreso[1] == master[1] && ingreso[2] == master[2] && ingreso[3] == master[3] && ingreso[4] == master[4]) {
                  estado = 0;//se resetea la varaiable de estado
                  alm = 1;//se pone cambia la variable a igual a 1 porque se ingreso contraseña de alarma
                  cont = 0;//se resetea el contador 
                  digitalWrite(indicador, LOW);//se desactiva el indicador 
                  funS = 6;//se pasa a la siguente etapa de la interrupcion 
                  Serial.println("Contraseña correcta");//impresion en Cx
                  Serial.println("SEGURIDAD ACTIVADA");//impresion en Cx
                  LCD.setCursor(0, 1);//impresion en pantalla LCD
                  LCD.print("SEGURIDAD ON...............");//impresion en pantalla LCD
                  break;
                }
              }
          }
        } else
        { Serial.println("numero no permitido");//se ingresaron demasiados caracteres 
          i = 0;//reseteo de contador 
        }
      }
      break;
    case '0'://tecla 0
      teclado(ingreso, customKey);//se guarda los datos que se pulsan 
      LCD.setCursor(0, 1);//impresion en pantalla LCD
      LCD.print(ingreso);//impresion en pantalla LCD
      break;
  }
}
void loop() {

  char contrasenia[5];//se crea un vector auxiliar para guardar los datos 
  if (funS == 2 || users == 2)//condcion de ingreso de contraseñas 
  {
    char customKey = customKeypad.getKey();//se inicializa el teclado 
    //char contrasenia[5];
    switch (customKey)//condicion de teclas de usuarios 
    {   delay(300);//retardo del sistema 
      case 'W': {//user 1
          usuario = 'W';
          LCD.setCursor(10, 1);//impresion en pantalla LCD
          LCD.print("USER 1");//impresion en pantalla LCD
          Serial.println("ingrese la contraseña de 1");//impresion de datos en CX
          llenarvector(contrasenia, usuario1);//se guarda los datos en un vector de usuario 
          //Serial.println(contrasenia);
        }
        break;
      case 'X': {//user 2
          usuario = 'X';
          LCD.setCursor(10, 1);//impresion en pantalla LCD
          LCD.print("USER 2");//impresion en pantalla LCD
          Serial.println("ingrese la contraseña de 2");//impresion de datos en CX
          llenarvector(contrasenia, usuario2);//se guarda los datos en un vector de usuario 
          //Serial.println(contrasenia);
        }
        break;
      case 'Y': {//user 3
          usuario = 'Y';
          LCD.setCursor(10, 1);//impresion en pantalla LCD
          LCD.print("USER 3");//impresion en pantalla LCD
          Serial.println("ingrese la contraseña de 3");//impresion de datos en CX
          llenarvector(contrasenia, usuario3);//se guarda los datos en un vector de usuario 
          //Serial.println(contrasenia);
        }
        break;
      case 'Z': {//user 4
          usuario = 'Z';
          LCD.setCursor(10, 1);//impresion de datos en CX
          LCD.print("USER 4");//impresion de datos en CX
          Serial.println("ingrese la contraseña de 4");//impresion de datos en CX
          llenarvector(contrasenia, usuario4);//se guarda los datos en un vector de usuario
          //Serial.println(contrasenia);
          break;
        }
    }

    contra(customKey, ingreso, contrasenia);//ingresa la contraseña para realizar las comprobaciones correspondeintes 
  } else if (funS == 5) {//condicion para cuando la interrucion ingresa las contraseñas 
    estado = 3;//se cambia la variable de entrada 
    char customKey = customKeypad.getKey();// se inicizalia el teclado 
    contra(customKey, ingreso, contrasenia);//se llama al metod que compara las contraseñas y las guarda

  } else if (funS == 6) {//condicion de alarma
    if (digitalRead(sensor) == HIGH)//si se detecta algo en el sensor 
    { delay(300);//retraso del sistema 
      cont++;//se aumenta el contador 
      if (cont > 0) {//se lee el numero del contador 
        digitalWrite(indicador, HIGH);//se enciende el indicador 
        Serial.println("intrusos");////impresion de datos en CX
        LCD.clear();//impresion en pantalla LCD
        LCD.setCursor(0, 0);//impresion en pantalla LCD
        LCD.print("ROOOOOOOBO...............");//impresion en pantalla LCD
        funS = 7;//se cambia la variable de interrupcion para moverse entre interrupciones 
      } else if (cont == 0) {//si no existe intrusos 
        funS = 0;//se reseta la variable de interrupcion 
        Serial.println("sin eventualidades");//impresion en pantalla Cx
        LCD.setCursor(0, 1);//impresion en pantalla LCD
        LCD.print("NO AMENAZAS                ");//impresion en pantalla LCD
      }
    }
  } else if (funS == 7) {//condicion de ingreso de contraseña de alarma 
    estado = 4;//se cambia la variable de entrada 
    char customKey = customKeypad.getKey();//se inicializa el teclado 
    contra(customKey, ingreso, alarma);//se llama al ingreso de las contraseñas 
  } else if (funS == 2 || users == 3) {//condicion de inicio de contador
    if (digitalRead(sensor) == HIGH)//se lee los datos del contador 
    { delay(300);//retraso del sistema 
      cont++;//sube el contador 
    }
  }
}
