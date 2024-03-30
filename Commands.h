#ifndef COMMANDS_H
#define COMMANDS_H

/*
bits [7:6] - command type:
  - 00: VSYNC, HSYNC, ...
  - 01: Color space definition, pixel lenght
  - 10: Picture height/10 in bits [5:0] - ? // используется нулевой бит, который зарезервирован под определение команды. Учитывая кратность размеров 20 всё должно быть нормально
  - 11: Picture width/10 in bits [5:0] - ?

bit 0: always 0 for command byte, indicates that byte is a command

  - 00:
    - 0b00000110 - VSYNC
    - 0b00011000 - HSYNC
  

*/

#define COMMAND_VSYNC 0b00000110
#define COMMAND_HREF 0b00011000

#define COMMAND_ESC 0b00110010 // next symbol is NOT a command byte

#endif // COMMANDS_H