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
    uint16_t _toWrite, _toSend;
    uint16_t _length;
}

#endif /* BUFFER_H_ */