#ifndef QVGA_REGISTERS_H_
#define QVGA_REGISTERS_H_

#include "Registers.h"

#define QVGA_VERTICAL_PADDING 5
#define QVGA_VSTART 0
#define QVGA_VSTOP (240 + QVGA_VERTICAL_PADDING)

#define QVGA_HSTART 174
#define QVGA_HSTOP 34

RegisterData regsQVGA[];

#endif // QVGA_REGISTERS_H_