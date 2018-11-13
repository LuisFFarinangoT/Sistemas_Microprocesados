// UTN -FICA -CIERCOM
//DEBER SISTEMAS MICROPROCESADOS
//  Realizar un programa que permita ingresar el número de cédula con el guión y posteriormente validarlo. El dato se lo
//  ingresa por comunicación serial.
//  Nombre :Luis Farinango
//  Comunicacion serial -----cx oara tx y rx de datos
//  la comunicacion es bit a bit
//  velocidad transmision -recepcion  tx -rx
//  configuracon
//  Serial.begin.(tx)-->la unidad de medida es de 9600
//  enviar datos
//    Serial.print(dato)//mensaje se envia en forma seguida
//    Serial.println(dato)//mensaje se envia con salto de linea (enter)
//    (dato'\n')
//  recepcion de datos
//    Serial.available()//confirma si existeb datos
//    Serial.readString()//lee cadenas de texto
//
//  delay
//
// CODIGO BASE DE COMPROBACION EXTRAIDO DE :https://gist.github.com/vickoman/7800717
String cedula = "";//declaracion de una cadena vacia para albergar la cedula

void setup() {
  Serial.begin(9600);//velocidad de comunicacion serial
}
int comprobletras(String letras)//metotdo para comprobar que no existan letras con la devolucion de un entero
{
  int comprobar = 0;//declaracion de una variable que crecera si existen letras en la cedula ingresada
  for (int i = 0; i < letras.length(); i++)//se recorre la cedula ingresada
  {
    char c = letras.charAt(i);//Extraccion de cada uno de los caracteres de la cedula 
    if ((int(c) >= 65) && (int(c) <= 122))//Se comprueba los valores numericos de los caracteres coinciden con los valores ASCII de las letras mayusculas y minusculas 
    { comprobar++;//si se encuentra con una letra se aumenta el valor de la variable
    }
  }
  return comprobar;//devuelve el numero de letras encontrados   
}

void loop() {
  if (Serial.available() > 0) {
    cedula = Serial.readString();//Recibe la cedula
    delay(100);//retraso para el sistema 
    int tam = cedula.length(); //variable que indica el tamaño de la cadena cedula ingresada

    if (tam > 11 && cedula.charAt(9) != '-') //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {//Condicion que comprueba el tamaño de la cadena ademas de que se contenga un guion en la misma 
      Serial.println("**********************************");
      Serial.println("el numero de cedula no es valido");
    } else if (comprobletras(cedula) > 0) {
      Serial.println("**********************************");
      Serial.println("cedula no válida, cadena contiene letras");
    }
    else if (tam == 11) //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {//condicion para cuando se cumple el tamaño de la cadena 
      Serial.println("**********************************");
      String digitoR = cedula.substring(0, 2);//calculos 
      int digito_region = digitoR.toInt();//calculos 
      delay(100);//retraso para el sistema 
      if (digito_region >= 1 && digito_region <= 24) //Region del Ecuador existente o no
      { int  ultimo_digito = cedula.substring(10).toInt(); //extraccion del ultimo digito
        //OPERACIONES CON PARES
        int p1 = (cedula.substring(1, 2)).toInt();//transformacion de la cadena para un entero y sus respectivas operaciones anteriores 
        int p2 = (cedula.substring(3, 4)).toInt();//transformacion de la cadena para un entero y sus respectivas operaciones anteriores
        int p3 = (cedula.substring(5, 6)).toInt();//transformacion de la cadena para un entero y sus respectivas operaciones anteriores
        int p4 = (cedula.substring(7, 8)).toInt();//transformacion de la cadena para un entero y sus respectivas operaciones anteriores
        int pares = p1 + p2 + p3 + p4;//calculos 
        //OPERACIONES CON IMPARES SEGUN LOS CALCULOS PARA CEDULAS ECUATORIANAS 
        int numero1 = cedula.substring(0, 1).toInt();//calculos 
        numero1 = (numero1 * 2);                     //calculos 
        if ( numero1 > 9 )                           //calculos 
        {
          numero1 = (numero1 - 9);                   //calculos 
        }
        int numero3 = cedula.substring(2, 3).toInt();//calculos 
        numero3 = (numero3 * 2);                     //calculos 
        if ( numero3 > 9 )                           //calculos 
        {
          numero3 = (numero3 - 9);                    //calculos 
        }

        int numero5 = cedula.substring(4, 5).toInt(); //calculos 
        numero5 = (numero5 * 2);                      //calculos 
        if ( numero5 > 9 ) {                          //calculos 
          numero5 = (numero5 - 9);                    //calculos 
        }

        int numero7 = cedula.substring(6, 7).toInt(); //calculos     
        numero7 = (numero7 * 2);                       //calculos  
        if ( numero7 > 9 ) {                          //calculos 
          numero7 = (numero7 - 9);                    //calculos 
        }
        int numero9 = cedula.substring(8, 9).toInt();//calculos 
        numero9 = (numero9 * 2);                      //calculos 
        if ( numero9 > 9 ) {                          //calculos 
          numero9 = (numero9 - 9);                    //calculos 
        }
        int impares = numero1 + numero3 + numero5 + numero7 + numero9;//calculos 
        int suma_total = pares + impares;                             //calculos 
        int primer_digito_suma = String(suma_total).substring(0, 1).toInt(); //extraccion del primer digito
        int decena = (((primer_digito_suma) + 1)  * 10);//obtencion de decena
        int digito_validador = (decena - suma_total);//obtencion del validador
        if (digito_validador == 10) //condiciones para la validacion
        {
          digito_validador = 0;//calculos de validacion finales 
        }
        if (digito_validador == ultimo_digito) { //condicion para validar el ultimo digito
          Serial.println("la cedula:" + cedula + " es correcta");//mensajes de salida 
        } else {
          Serial.println("la cedula:" + cedula + " es incorrecta");//mensajes de salida 
        }
      } else {
        Serial.println("Esta cedula no pertenece a ninguna region");//cedula no registrada en region
      }
    } else {
      Serial.println("Esta cedula tiene menos de 11 Digitos");//informativo si la cedula no coincide con los digitos
    }
  }
}
