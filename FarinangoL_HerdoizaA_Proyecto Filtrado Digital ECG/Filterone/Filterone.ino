/*
 * UTN -FICA -CIERCOM 
 * PROYECTO FINAL  Filtrado Digital de señal ECG
 * Nombres:
 *         Farinango Luis 
 *         Herdoiza Adriana
 * Codigo tomado de :Filter one Examples
 */
 
#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>
#define ARM_MATH_CM3 // libreria math del DUE
#include <arm_math.h>
#define tam_sig 524
extern float32_t Senal[tam_sig];
float32_t out_signal[tam_sig ];
void setup() {
  Serial.begin(9600);
}
// filter out frequencies below 1 Hz.
// create a highpass filter that only keeps frequencies above highFilterFrequency
float highFilterFrequency = 0.05;
float lowFilterFrequency = 8;
FilterOnePole filterOneHighpass( HIGHPASS, highFilterFrequency );
FilterOnePole filterOneLowpass(LOWPASS, lowFilterFrequency);
// filters out frequenceies greater than 3 Hz.
// create a lowpass filter that only keeps frequencies below lowFilterFrequency
void loop() {
  int32_t i;
  //The next line applies a band pass filter to the signal
  for (i = 0; i < tam_sig; i++) {
    out_signal[i] = filterOneHighpass.input(filterOneLowpass.input(Senal[i]));
    Serial.print(Senal[i] * 100);
    Serial.print(",");
    Serial.println(out_signal[i] * 50);
  }
}
