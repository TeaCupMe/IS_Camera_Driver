#ifndef CAMERA_H_
#define CAMERA_H_

#include "Registers.h"

enum ImageSize
{
    _160x120,
    _320x240,
    _640x480,
    // TODO custom resolution?
};

enum Colorspace
{
    RGB565,
    RGB555,
    YUV422,
    // TODO отдельное значение для WB?
};

class Camera
{
public:
    Camera(ImageSize imageSize = ImageSize::_160x120, Colorspace colorspace = Colorspace::RGB555);

    void setCameraImageSize(ImageSize imageSize);    // REVIEW
    void setCameraColorspace(Colorspace colorspace); // REVIEW

    bool setCameraRegister(const RegisterData *regData, bool ensure = false); // REVIEW
    bool setCameraRegister(uint8_t addr, uint8_t val, bool ensure);           // REVIEW
    void readCameraRegister(RegisterData *regData);                           // REVIEW

    uint8_t getCameraRegister(RegisterData *regData); // REVIEW
    uint8_t getCameraRegister(uint8_t addr);          // REVIEW

    bool setCameraRegisters(const RegisterData *regs, int retries = 2); // TODO

    void resetCamera(); // REVIEW

    bool setCameraPresaler(int prescaler); // REVIEW - why did I use int here?

    bool setCameraPLLMultiplier(uint8_t multiplier); // REVIEW - unused in most scenarios

    void waitForPCLKRising(int16_t = 0);   // TODO
    void waitForPCLKFalling(int16_t = 0);  // TODO
    void waitForHREFRising(int16_t = 0);   // TODO
    void waitForHREFFalling(int16_t = 0);  // TODO
    void waitForVSYNCRising(int16_t = 0);  // TODO
    void waitForVSYNCFalling(int16_t = 0); // TODO

private:
    ImageSize _imageSize;
    Colorspace _colorspace;
    int _prescaler;
    uint8_t _address;
    uint16_t _width, _height
};

void uartWaitForPreviousByteToBeSent(); // TODO
void uartSendByte(uint8_t);             // TODO
bool uartIsReady();                     // TODO
uint8_t uartHasData();                  // TODO
uint8_t uartGetData();                  // TODO

#endif /* CAMERA_H_ */