#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void PC_0(bool value);
void PC_1(bool value);
void PC_2(bool value);
void PC_3(bool value);
void PC_4(bool value);
void PC_5(bool value);
void PC_6(bool value);
void PC_7(bool value);
void PC_8(bool value);
void PC_9(bool value);
void PC_10(bool value);
void PC_11(bool value);
void PC_12(bool value);
void PC_13(bool value);
void PC_14(bool value);
// there is no PC_15 !
void PC_16(bool value);
void PC_17(bool value);
void PC_18(bool value);
void PC_19(bool value);
void PC_20(bool value);
void PC_21(bool value);
void PC_22(bool value);
void PC_23(bool value);

void pcint_enable(uint8_t arduinoPin);
void pcint_disable(uint8_t arduinoPin);

#ifdef __cplusplus
}
#endif
