#include "QQVGA_Registers.h"

const RegisterData regsQQVGA[] = {
    {REG_VSTART, QQVGA_VSTART},
    {REG_VSTOP, QQVGA_VSTOP},
    {REG_VREF, 0},
    {REG_HSTART, QQVGA_HSTART >> 3},
    {REG_HSTOP, QQVGA_HSTOP >> 3},
    {REG_HREF, 0b00000000 | (QQVGA_HSTART & 0b111) | ((QQVGA_HSTOP & 0b111) << 3)},

    {REG_COM3, COM3_DCWEN}, // enable downsamp/crop/window
    {REG_COM14, 0x1a},        // divide by 4
    {SCALING_DCWCTR, 0x22},   // downsample by 4
    {SCALING_PCLK_DIV, 0xf2}, // divide by 4

    {0xff, 0xff}	/* END MARKER */
};
