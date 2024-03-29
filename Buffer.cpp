#include "Buffer.h"

Buffer::Buffer(uint16_t length)
{
    data = new uint8_t[length];
    _length = length;
}

void Buffer::addToBuffer(uint8_t b)
{
    data[_toWrite] = b;
    _toWrite++;
    _toWrite %= _length;
}

void Buffer::bufferTick(void (*send)(uint8_t), void (*channelReady)(void))
{
    if (!channelReady())
    {
        return;
    }
    if (_toSend != _toWrite)
    {
        send(data[_toSend]);
        _toSend++;
        _toSend %= _length;
    }
}
