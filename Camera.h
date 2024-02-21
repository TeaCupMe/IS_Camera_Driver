#ifndef CAMERA_H_
#define CAMERA_H_

#include "Registers.h"

#include "IS_Cam.h"

enum ImageSize
{
    _160x120,
    _320x240,
    _640x480,
    // TODO custom resolution?
}

enum Colorspace
{
    RGB565,
    RGB555,
    YUV422,
    // TODO отдельное значение для WB?
}

class Camera
{
public:
    Camera(ImageSize imageSize = ImageSize::_160x120, Colorspace colorspace = Colorspace::RGB555);

    void setCameraImageSize(ImageSize imageSize);
    void setCameraColorspace(Colorspace colorspace);

    bool setCameraRegister(RegisterData regData);
    void readCameraRegister(RegisterData *regData);

    uint8_t getCameraRegister(RegisterData *regData);
    uint8_t getCameraRegister(uint8_t addr);

    bool setCameraRegisters(const RegisterData *regs, bool ensure);

    void resetCamera();

    void setCameraPresaler(int prescaler); // REVIEW - why did I use int here?

    void setCameraPLLMultiplier(uint8_t multiplier); // REVIEW - unused in most scenarios

    void waitForPCLKRising(int16_t = 0);
    void waitForPCLKFalling(int16_t = 0);
    void waitForHREFRising(int16_t = 0);
    void waitForHREFFalling(int16_t = 0);
    void waitForVSYNCRising(int16_t = 0);
    void waitForVSYNCFalling(int16_t = 0);

    void uartWaitForPreviousByteToBeSent();
    void uartSendByte(uint8_t);
    bool uartIsReady();
    uint8_t uartHasData();
    uint8_t uartGetData();

private:
    ImageSize _imageSize;
    Colorspace _colorspace;
    int prescaler;
    uint8_t address;
}

#endif