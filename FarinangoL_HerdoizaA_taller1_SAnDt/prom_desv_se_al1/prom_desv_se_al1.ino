/*
 * UTN-FICA -CIERCOM
 * Sistemas Análogos Digitales taller 
 * 
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
float32_t promedio;
float32_t des_estand;
float32_t var;
float32_t des;
void setup() {
  Serial.begin(9600);
  //Promedio
  arm_mean_f32(&points_ecg_[0], tam_inputSignal, &promedio); //Señal desde 0, tamaño
  Serial.print(promedio);
  //Varianza
  Serial.println("------------");
  arm_var_f32(&points_ecg_[0], tam_inputSignal, &var);
  des=sqrt(var);
  Serial.println(des);
}
void loop() {
}
