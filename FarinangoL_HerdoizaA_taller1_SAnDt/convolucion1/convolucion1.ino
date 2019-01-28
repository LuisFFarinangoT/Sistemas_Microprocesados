/*
 * UTN-FICA -CIERCOM
 * Sistemas Analogos Digiatles 
*/
//float32_t -> float de 32 bits
//uint32_t -> u de unsigned, toma los 32 bits para datos positivos
#define ARM_MATH_CM3 //Cortex M3
#include <arm_math.h> //Librearía para Due
#define tam_impl 29
#define tam_inputSignal 640
#define IMP_RSP_LENGTH 29
extern float32_t points_ecg_[tam_inputSignal]; //Busca del archivo en la misma carpeta
extern float32_t Impulse_response[tam_impl];
float32_t signalOut[tam_inputSignal + tam_impl]; //Convolución salidaz
void setup() {
  Serial.begin(9600);


}

void loop() {
  convolucion(points_ecg_, Impulse_response, tam_inputSignal, tam_impl);
  arm_conv_f32(&points_ecg_[0], tam_inputSignal, &Impulse_response[0], tam_impl, &signalOut[0]);
  plot_sig(signalOut, tam_inputSignal + tam_impl);
}

void plot_sig (float32_t *sig_entrada, uint32_t tam_sig) {
  uint32_t i;
  for (i = 0; tam_sig; i++) {
    Serial.println(sig_entrada[i] * 100);
    delay(10);
  }
}

void convolucion (float32_t *sig_entrada, float32_t *sig_impulso, uint32_t tam_sig_entrada,uint32_t tam_impulse) {
  uint32_t i;
  uint32_t j;
  for (i = 0; i < tam_sig_entrada; i++) {
    for (j = 0; j < tam_impulse; j++) {
      signalOut[i + j] = signalOut[i + j] + sig_entrada[i] * sig_impulso[j]; //Suma ponderada + conv

    }
    
  }

}
