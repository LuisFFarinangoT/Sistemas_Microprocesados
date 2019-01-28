/*

*/
#define ARM_MATH_CM3//libreria math DUE
#include <arm_math.h>
#define tam_sig 640
extern float32_t  points_ecg_[tam_sig];
float32_t OutputSignal[tam_sig];
void plot_sig() {//**************************************************************************************************
  uint32_t i;
  for (i = 0; i < tam_sig; i++)
  { Serial.println(points_ecg_[i]);
    Serial.println(",");
    Serial.println(OutputSignal[i]);
    delay(10);
  }
}
void running_sum(float32_t *inputs, float32_t *outputs, uint32_t tam) //********************************************
{ uint32_t i;
  for (i = 0; i < tam_sig; i++) {
    outputs[i] = inputs[i] + outputs[i - 1];
  }
}
void first_rest(float32_t *inputs, float32_t *outputs, uint32_t tam) //*********************************************
{ uint32_t i;
  for (i = 0; i < tam_sig; i++) {
    outputs[i] = inputs[i] - outputs[i - 1];
  }
}
void setup() {//******************************************************************************************************
  Serial.begin(9600);

}

void loop() {//********************************************************************************************************
  //running_sum(&points_ecg_[0],&OutputSignal[0],tam_sig);//primera sum 
  first_rest(&points_ecg_[0],&OutputSignal[0],tam_sig);//primera resta 
  plot_sig();
}
