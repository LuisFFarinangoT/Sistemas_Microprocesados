
/*        UNIVERSIDAD TÉCNICA DEL NORTE
      FACULTAD DE INGENIERÍA EN CIENCIAS APLICADAS
  CARRERA DE INGENIERÍA ELECTRÓNICA Y REDES DE COMUNICACIÓN
    NOMBRES: 
            Farinango Luis
            Herdoiza Adriana
            Quintana Karen 
    FECHA: 16-11-2018
DEBER:  Se debe realizar un sistema que permita el ingreso de una contraseña por medio de 4 pulsadores. Cada uno tiene una letra diferente (A, B, C y D).
        El usuario debe ingresar una contraseña de 6 dígitos, la misma que debe tener los siguientes parámetros.
          1. Debe tener por lo menos 2 letras A en la contraseña.
          2.  Por lo menos 1 letra C.
          3.  Por lo menos 1 letra B.
          4.  El sistema cuenta con una interrupción que enciende y apaga el sistema.
          5.  Cuando una contraseña se aceptada, debe encender un led verde, caso contrario un led rojo y mensajes por comunicación serial en ambos casos.
configuración C-x
la comunicacion es bit a bit
  velocidad transmision -recepcion  tx -rx
  configuracon
  Serial.begin.(tx)-->la unidad de medida es de 9600
  enviar datos
    Serial.print(dato)//mensaje se envia en forma seguida
    Serial.println(dato)//mensaje se envia con salto de linea (enter)
    (dato'\n')
  recepcion de datos
    Serial.available()//confirma si existeb datos
    Serial.read(datos)//lectira de datos de la entrada
    Serial.readString()//lee cadenas de texto
  delay
*/
int pulsaD = 4; //pin para puslador de la letra A
int pulsaC = 5; //pin para puslador de la letra B
int pulsaB = 6; //pin para puslador de la letra C
int pulsaA = 7; //pin para puslador de la letra D
int ledb = 8; //pin para led para indicar que la contraseña cumple con los parametros
int ledm = 9; //pin para led para indicar que la contraseña no cumple con los parametros
int ledprueba=10;//pin para ledpara indicar el sistema esta encendido o no
String contra = ""; //cadena que albergara la cadena ingresada por C-x
const int intInterrup = 2;//pin del pulsador para interrupcion
volatile int state = LOW;//variable volatil para interrupcion 
void setup() {
  attachInterrupt(digitalPinToInterrupt(intInterrup),encendido,FALLING);
  pinMode(pulsaA, INPUT);//declaración de pines para entradas y salidas 
  pinMode(pulsaB, INPUT);//declaración de pines para entradas y salidas
  pinMode(pulsaC, INPUT);//declaración de pines para entradas y salidas
  pinMode(pulsaD, INPUT);//declaración de pines para entradas y salidas
  pinMode(ledb, OUTPUT);//declaración de pines para entradas y salidas
  pinMode(ledm, OUTPUT);//declaración de pines para entradas y salidas
  pinMode(ledprueba, OUTPUT);//declaración de pines para entradas y salidas
}
int contarA(String contra) {//método para contar las letras A en la contraseña
  int contadorA = 0;//inicializar un contador en cero 
  for (int i = 0; i < contra.length(); i++) {//recorrido de la cadena contraseña
    if (contra.charAt(i) == 'A') {//busqueda de los caracteres A en la cadena contra en la posición i
      contadorA++;//si se cumple la condición el contador avanza
    }
  }
  return contadorA;//el método devolvera el numero de letras  A encontradas en la cadena 
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int contarB(String contra) {//método para contar las letras B en la contraseña
  int contadorB = 0;//inicializar un contador en cero
  for (int i = 0; i < contra.length(); i++) {//recorrido de la cadena contraseña
    if (contra.charAt(i) == 'B') {//busqueda de los caracteres B en la cadena contra en la posición i
      contadorB++;//si se cumple la condición el contador avanza
    }
  }
  return contadorB;//el método devolvera el numero de letras A encontradas en la cadena 
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int contarC(String contra) {//método para contar las letras C en la contraseña
  int contadorC = 0;//inicializar un contador en cero
  for (int i = 0; i < contra.length(); i++) {//recorrido de la cadena contraseña
    if (contra.charAt(i) == 'C') {//busqueda de los caracteres C en la cadena contra en la posición i
      contadorC++;//si se cumple la condición el contador avanza
    }
  }
  return contadorC;//el método devolvera el numero de letras C encontradas en la cadena 
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop() {
  if (contra.length() < 6)//condición para controlar el tamaño de la contraseña 
  {
    if (digitalRead(pulsaA) == HIGH) {//condición para cuando se presiona el pulsador A
      delay(100);//retraso del sistema
      Serial.print('A');//se imprime a en pantalla
      delay(300);//retraso del sistema
      contra = contra + "A";//concatenación de la cadena si se presiona una vez más
    }
    else if (digitalRead(pulsaB) == HIGH) {//condición para cuando se presiona el pulsador B
      delay(100);//retraso del sistema
      Serial.print('B');//se imprime a en pantalla
      delay(300);//retraso del sistema
      contra = contra + "B";//concatenación de la cadena si se presiona una vez más
    }
    else if (digitalRead(pulsaC) == HIGH) {//condición para cuando se presiona el pulsador C
      delay(100);//retraso del sistema
      Serial.print('C');
      delay(300);//retraso del sistema
      contra = contra + "C";//concatenación de la cadena si se presiona una vez más
    }
    else if (digitalRead(pulsaD) == HIGH) {//condición para cuando se presiona el pulsador D
      delay(100);//retraso del sistema
      Serial.print('D');
      delay(300);//retraso del sistema
      contra = contra + "D";//concatenación de la cadena si se presiona una vez más
    }
  } 
   else if (contra.length() == 6) {//condición para cuando se cumple el número de carácteres permitidos 
    if ((contarA(contra) == 2)&&(contarB(contra)==1)&&(contarC(contra)==1)) {//se llama a los metodo de conteo tando de A,B y C
      contra = "";//se vacia la cadena 
      Serial.println(" \n CONTRASEÑA VALIDA ");//mensaja de aprobacion de contraseña
      Serial.println("++++++++++++++++++++++++++++++");
      digitalWrite(ledb,HIGH);//encendido y apagado de leds de señalización 
      digitalWrite(ledm,LOW);//encendido y apagado de leds de señalización 
    }else{//condición para cuando no se cumpla los parámetros exijidos 
      contra = "";
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("CONTRASEÑA NO VALIDA");
      digitalWrite(ledm,HIGH);//encendido y apagado de leds de señalización 
      digitalWrite(ledb,LOW);//encendido y apagado de leds de señalización 
    }
  }
}
void encendido() {//método de interrupción 
   state = !state;//cambio de estado 
   digitalWrite(ledprueba, state);//se escribe la condición anterior en un led e prueba 
if(!digitalRead(ledprueba)){//se evalua el estado del led 
  digitalWrite(ledm,LOW);//encendido y apagado de leds de señalización 
  digitalWrite(ledb,LOW);//encendido y apagado de leds de señalización 
   Serial.println("Proceso de apagado");
    Serial.end();}//se termina la comunucación serial 
  else{
Serial.begin(9600);//caso contrario se la inicia
  digitalWrite(ledm,LOW);//encendido y apagado de leds de señalización 
  digitalWrite(ledb,LOW);
Serial.println("Proceso de encendido");}
}
