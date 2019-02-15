/*
 * UTN -FICA -CIERCOM 
 * PROYECTO FINAL  Filtrado Digital de señal ECG
 * Nombres:
 *         Farinango Luis 
 *         Herdoiza Adriana
 * Código tomado de :https://github.com/puldavid87/SISTEMAS-MICROPROCESADOS/tree/master/WINDOWED
 * 
*/
#define ARM_MATH_CM3 // libreria math del DUE
#include <arm_math.h>
#define tam_sig 524
#define fil 50
float32_t filtro [fil];
extern float32_t Senal[tam_sig];
float32_t out_signal[tam_sig + fil];
int32_t M = 10;      //tamano del filtro
void setup() {
  Serial.begin(9600);//comunicacion serial
}
void loop() {//********************************************************************
  windowed(&Senal[0], &filtro[0], tam_sig, fil, 0.06);//filtrado 
  convolution (&Senal[0], &out_signal[0], &filtro[0], tam_sig, fil);//convolucion de filtro con señal original
  plot_sig();//graficas de la señal 
}
void windowed(float32_t *sig_in, float32_t *vec, int32_t tam_in, int32_t tam_fil, float32_t fc) {//metodo de filtrado//********
  int32_t i;
  float32_t sum = 0;
  for (i = 0; i < tam_fil; i++) {
    vec[i] = 0;
  }
  for (i = 0; i < tam_fil; i++) {
    if (i - tam_fil == 0) {
      vec[i] = 2 * PI * fc;
    }
    else {//Ecuaciones de los filtros
      vec[i] = sin(2 * PI * fc * ((float32_t)i - tam_fil / 2)) / (i - tam_fil / 2);
      vec[i]=vec[i]*(0.42-0.5*cos((2*PI*(float32_t)i)/(tam_fil-1))+0.08*cos((4*PI*(float32_t)i)/(tam_fil-1)));//ventana Blackman
      //vec[i] = vec[i] * (0.54 - 0.46 * cos(2 * PI * i * tam_fil)); //ventana Hamming
      //vec[i] = vec[i] *(((float32_t)i-((tam_fil -1)/(2)))/((tam_fil -1)/(2)));//ventana Barllet
       //vec[i] = vec[i] * (0.5*(1-cos((2*PI*(float32_t)i)/(tam_fil/2)))); //ventana Hanning  }
  }
  for (i = 0; i < tam_fil; i++) {
    if (sum < vec[i]) {
      sum = vec[i];
      // Serial.println(vec[i],10);
    }
  }
  for (i = 1; i < tam_fil; i++) {
    if (i == 25)
      vec[i] = 1;
    else
      vec[i] = vec[i] / sum;
    //
    //        Serial.print(i);
    //        Serial.print(",");
    //      Serial.println(vec[i],10);
    delay(100);
  }
}
}
void plot_sig () {//metodo de Graficas //*****************************************************************
  uint32_t i;
  for (i = 0; i < tam_sig; i++) {
    Serial.print((Senal[i] * 200)+200);
    Serial.print(",");
    //      Serial.print(filtro[i]*100);
    //      Serial.print(",");
    Serial.println((out_signal[i] * 50)+20);
    delay(10);
  }
}
void convolution (//metodo convolucion //************************************************************************************
  float32_t *sig_src_arr,
  float32_t *sig_dest_arr,
  float32_t *imp_response_arr,
  uint32_t sig_src_length,
  uint32_t imp_response_length
) {
  uint32_t i, j;
  for (i = 0; i < (sig_src_length + imp_response_length); i++)
  {
    sig_dest_arr[i] = 0; // conocer el tamano del nuevo vector
  }
  for (i = 0; i < sig_src_length; i++) { // lee las posiciones de la senal x[n]
    for (j = 0; j < imp_response_length; j++) { // lee las posiciones de h[x]
      sig_dest_arr[i + j] = (float32_t)(sig_dest_arr[i + j] + sig_src_arr[i] * imp_response_arr[j]); //almacena x[n]+h[n]
    }
    // Serial.print(i);
    // Serial.print(",");
    // Serial.println(sig_dest_arr[i],15);
    // delay(200);
  }
}
