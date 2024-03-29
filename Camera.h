#ifndef CAMERA_H_
#define CAMERA_H_

#include <Wire.h>
#include "Arduino.h"


#include "Registers/Registers.h"

#include "Registers/VGA_Registers.h"
#include "Registers/QVGA_Registers.h"
#include "Registers/QQVGA_Registers.h"

#define PCLK ((PINB & 0b00000100) == 0 ? false : true)
#define VSYNC ((PIND & 0b00000100) == 0 ? false : true)
#define HREF ((PINB & 0b00000001) == 0 ? false : true) //! TODO

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

inline void dummyRoutineFunction()
{
    // return;
}

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

    void waitForPCLKRising(uint16_t = 0, void (*routine)(void) = &dummyRoutineFunction);   // TODO
    void waitForPCLKFalling(uint16_t = 0, void (*routine)(void) = &dummyRoutineFunction);  // TODO
    void waitForHREFRising(uint16_t = 0, void (*routine)(void) = &dummyRoutineFunction);   // TODO
    void waitForHREFFalling(uint16_t = 0, void (*routine)(void) = &dummyRoutineFunction);  // TODO
    void waitForVSYNCRising(uint16_t = 0, void (*routine)(void) = &dummyRoutineFunction);  // TODO
    void waitForVSYNCFalling(uint16_t = 0, void (*routine)(void) = &dummyRoutineFunction); // TODO

private:
    ImageSize _imageSize;
    Colorspace _colorspace;
    int _prescaler;
    uint8_t _address;
    uint16_t _width, _height;
};

void uartWaitForPreviousByteToBeSent(); // TODO
void uartSendByteSafe(uint8_t);         // TODO
void uartSendByte(uint8_t);             //! TODO just write to UDR0!!
bool uartIsReady();                     // TODO
uint8_t uartHasData();                  // TODO
uint8_t uartGetData();                  // TODO

#endif /* CAMERA_H_ */