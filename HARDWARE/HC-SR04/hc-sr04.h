#ifndef HC_SR04_H_
#define HC_SR04_H_
#include "sys.h"
#define gTrig  PCout(10)
#define gEcho  PAout(1)
void StartModule(void);
static void MeasureDistance(void);
void HCSR04Test(void);
#endif
