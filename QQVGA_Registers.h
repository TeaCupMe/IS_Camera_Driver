#ifndef QQVGA_REGISTERS_H_
#define QQVGA_REGISTERS_H_

#include "Registers.h"

#define QQVGA_VERTICAL_PADDING 2
#define QQVGA_VSTART 0
#define QQVGA_VSTOP (120 + QQVGA_VERTICAL_PADDING)

#define QQVGA_HSTART 182
#define QQVGA_HSTOP 46

RegisterData regsQQVGA[];

#endif // QQVGA_REGISTERS_H_