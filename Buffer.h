#ifndef BUFFER_H_
#define BUFFER_H_

#include "Arduino.h"

class Buffer
{
    Buffer(uint16_t length);

    void addToBuffer(uint8_t);
    void bufferTick();

private:
    uint8_t *data;
}

#endif /* BUFFER_H_ */