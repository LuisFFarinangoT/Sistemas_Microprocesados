#include <LowPower.h> //libreria de low power
#include <MsTimer2.h>//libreria de manejo de tiempos 
int led = 13;//led de aviso
int volatile cont;//variable de contador 
void setup()//******************************************
{ Serial.begin(9600);//Inicio de Cx
  MsTimer2::set(1000, conteo);//Inicio de Timer
  MsTimer2::start();//Inicio de Timer
  pinMode(led, OUTPUT);//led indicador
}
void conteo() {
  if (cont <= 1)//se comprueba el contador 
  { cont++;//se aumenta el contador 
    digitalWrite(led, LOW );//apagamos al foco
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //dormir al sistema por 8 s
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //dormir al sistema por 8 s
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //dormir al sistema por 8 s
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF); //dormir al sistema por 4 s
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); //dormir al sistema por 2 s
    //se duerme al sistema por 29 segundos 
  }  else  {
    digitalWrite(led, HIGH);//Manejo de leds
    Serial.println("LECTURA");//impresion de mensaje 
    Serial.println(analogRead(A0));//impresion de mensaje
    cont = 0;//reseteo del ciclo

  }

}
void loop()
{


}
