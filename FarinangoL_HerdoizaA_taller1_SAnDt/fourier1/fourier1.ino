/*
 * UTN-FICA -CIERCOM
 * 
 * Sistemas Análogos Digitales 
 *    TEMA: Taller Señales 
 *          Transformada de Fourier(excel)
 *    INTEGRANTES: Farinango Luis
 *                 Herdoíza Adriana
 *    FECHA: 28-01-2019
 * 
*/
#define ARM_MATH_CM3 //Libreria math del DUE
#include <arm_math.h> //Librearía para Due
#define tam_sig 640
extern float32_t points_ecg_[tam_sig];
float32_t REX[tam_sig];
float32_t IDX[tam_sig];
float32_t OutputSignal[tam_sig];

void setup() {
  Serial.begin(9600);
}

void loop() {
  cal_tdf(&points_ecg_[0],&REX[0],&IDX[0],tam_sig);  //primero calculo, luego asigno y luego le grafico
  get_tdf();
  plot_signal();
 
}

void cal_tdf(float32_t *input_sig,float32_t*sig_rex, float32_t *sig_idx, uint32_t tam){  //calcular la transformada discreta de fourier
  uint32_t i, j, k;
  
  for(j=0;j<tam/2;j++) {
    sig_rex[j]=0;
    sig_idx[j]=0;
  }
  for(k=0;k<tam/2;k++) {  //almacenar en idx y rex
    for(i=0;i<tam;i++) {  //sumatoria de todos los componentes de sig_input
      sig_rex[k]=sig_rex[k]+input_sig[i]*cos(2*PI*k*i/tam);
      sig_idx[k]=sig_idx[k]-input_sig[i]*sin(2*PI*k*i/tam);
    }
  }
}

void get_tdf() {
  uint32_t i;
  for(i=0;i<tam_sig;i++) {
    OutputSignal[i]=sqrt(pow(REX[i],2)+pow(IDX[i],2));
  }
}

void plot_signal() {
  uint32_t i;
  for(i=0;i<tam_sig;i++) {
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}
