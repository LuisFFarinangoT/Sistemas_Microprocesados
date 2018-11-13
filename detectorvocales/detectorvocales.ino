
/*UTN -FICA -CIERCOM
DEBER SISTEMAS MICROPROCESADOS
 * Realizar un sistema que permite determinar el número de vocales dentro de una palabra. 
 * Este dato es ingresado por comunicación serial y la respuesta del mismo de igual manera
 * Nombre 
        Luis Farinango
 * configuracion :
 * 
 * Comunicacion serial -----cx oara tx y rx de datos
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
int cont = 0;//varible para contador
String str;//cadena que albergara la cadena ingresada por C-x
char dato;
int numero;//convertir de char a int
void setup() {
  Serial.begin(9600);//velocidad de comunicacion serial
}
void loop (){
int contador = 0;//asignacion de valor de la variable del contador 
  if (Serial.available() > 0) {//comprobaciond de C.x
   str = Serial.readString();//Recibe en caracteres//ingreso de la cadena 
     delay(50);//retraso del sistema 
     Serial.println( "---------");//conocer tamaño string
       int tam = str.length();//tamaño de la cadena ingresada para calculos futuros
       for(int i=0;i<tam;i++){//recorrido de la cadena 
         if(str.charAt(i)=='a' || str.charAt(i)=='e' || str.charAt(i)=='i' || str.charAt(i)=='o'|| str.charAt(i)=='u'||
         str.charAt(i)=='A' || str.charAt(i)=='E' || str.charAt(i)=='I' || str.charAt(i)=='O'|| str.charAt(i)=='U')//condiciones de reconocimiento de vocales 
        {
            contador=contador+1;//si se encuentra una vocal se aumenta un contador ,dicho contador nos dara el numero de vocales ingresadas al final del ciclo
          }
        }
      Serial.println("+++++++++++++++++++++++++ ");
  Serial.println("el valor de vocales es  ");//impresion de resultados 
 Serial.println(contador);//impresion de resultados 
        }
}
