#include "Camera.h"

using namespace OV7670;

Camera::Camera(ImageSize imageSize, Colorspace colorspace)
{
    _colorspace = colorspace;
    _imageSize = imageSize;
    // TODO Camera setup
}

void Camera::setCameraImageSize(ImageSize imageSize)
{
    _imageSize = imageSize;
    switch (imageSize)
    {
    case ImageSize::_160x120:
        setCameraRegisters(regsQQVGA);
        break;

    case ImageSize::_320x240:
        setCameraRegisters(regsQVGA);
        break;
    case ImageSize::_640x480:
        setCameraRegisters(regsVGA);
    default:
        break;
    }
    // setCameraRegisters();
}

void Camera::setCameraColorspace(Colorspace colorspace)
{
    _colorspace = colorspace;
    switch (colorspace)
    {
    case Colorspace::RGB555:
        /* code */
        setCameraRegisters(_colorspace);
        break;

    case Colorspace::RGB565:

        break;

    case Colorspace::YUV422:

        break;

    default:
        break;
    }
}

bool Camera::setCameraRegister(uint8_t addr, uint8_t value, bool ensure)
{
#ifdef DEBUG_MODE
    Serial.print("Writing 0x");
    Serial.print(value, HEX);
    Serial.print(" (0b");
    Serial.print(value, BIN);
    Serial.print(") to 0x");
    Serial.print(addr, HEX);
    Serial.print(" register\n");
#endif
    Wire.beginTransmission(CAMERA_ADDRESS);
    Wire.write(addr);
    Wire.write(value);
    Wire.endTransmission();
#ifdef DEBUG_MODE
    Serial.print("Register sent\n");
#endif
    if (ensure)
    {
        Wire.beginTransmission(CAMERA_ADDRESS);
        Wire.write(addr);
        Wire.endTransmission();
        while (Wire.available() > 0)
            Wire.read();
        // Serial.write("2");
        Wire.requestFrom(CAMERA_ADDRESS, 1);
        long long st = micros();
        while (Wire.available() <= 0)
        {
            if (micros() - st > 500)
            {
                Serial.print("[W] No response from camera!!\n");
                return false;
            }
        };

        uint8_t res = Wire.read();
#ifdef DEBUG_MODE
        Serial.print("Read 0x");
        Serial.print(value, HEX);
        Serial.print(" from register 0x");
        Serial.print(res, HEX);
        Serial.write('\n');
        Serial.write('\n');
#endif
        return res == value;
    }
    return true;
}

bool Camera::setCameraRegister(const RegisterData *regData, bool ensure)
{
    return setCameraRegister(regData->addr, regData->val, ensure);
}

void Camera::readCameraRegister(RegisterData *regData)
{
    Wire.beginTransmission(CAMERA_ADDRESS);
    Wire.write(regData->addr);
    Wire.endTransmission();
    Wire.requestFrom(CAMERA_ADDRESS, 1);
    while (Wire.available() <= 0)
        ;
    regData->val = Wire.read();
}

uint8_t Camera::getCameraRegister(RegisterData *regData)
{
    Wire.beginTransmission(CAMERA_ADDRESS);
    Wire.write(regData->addr);
    Wire.endTransmission();
    Wire.requestFrom(CAMERA_ADDRESS, 1);
    while (Wire.available() <= 0)
        ;
    uint8_t registerValue = Wire.read();
    return registerValue;
}

uint8_t Camera::getCameraRegister(uint8_t addr)
{
    Wire.beginTransmission(CAMERA_ADDRESS);
    Wire.write(addr);
    Wire.endTransmission();
    Wire.requestFrom(CAMERA_ADDRESS, 1);
    while (Wire.available() <= 0)
        ;
    uint8_t registerValue = Wire.read();
    return registerValue;
}

bool Camera::setCameraRegisters(const RegisterData *regs, int retries) // FIXME debug mode support
{
#ifdef DEBUG_MODE
    uint8_t regsCount = 0;
    Serial.print("Writing to camera registers: ");
#endif

    while (true)
    {
        // RegisterData regData = *regs; // {addr: pointer->addr, val: pointer->val };
        if (regs->addr == 0xFF)
            break; // Если дошли до конца массива данных
        else
        {
            for (int i = 0; i < retries; i++)
            {
                if (setCameraRegister(regs))
                    break;
                else
                {
                    // FIXME
                    // TODO
                }
            }

            // bool fl = false;
            // do
            // {
            //     fl = setCameraRegister(regData.addr, regData.val);
            // } while (!fl && ensure);

            regs++;
        }
    }
}

void Camera::resetCamera()
{
    setCameraRegister(&ResetRegister, false);
}

bool Camera::setCameraPresaler(int prescaler)
{
    return setCameraRegister(REG_CLKRC, 0x80 | prescaler, true);
}

bool Camera::setCameraPLLMultiplier(uint8_t multiplier)
{
    uint8_t mask = 0b11000000;
    uint8_t currentValue = readCameraRegister(DBLV);
    return setCameraRegister(DBLV, (currentValue & ~mask) | (multiplier << 6), true);
}

void Camera::waitForPCLKRising(uint16_t skip, void (*routine)(void))
{
    while (skip >= 0)
    {
        while (PCLK)
            routine();
        while (!PCLK)
            routine();
        skip--;
    }
}

void Camera::waitForPCLKFalling(uint16_t skip, void (*routine)(void))
{
    while (skip >= 0)
    {
        while (!PCLK)
            routine();
        while (PCLK)
            routine();
        skip--;
    }
}

void Camera::waitForHREFRising(uint16_t skip, void (*routine)(void))
{
    while (skip >= 0)
    {
        while (HREF)
            routine();
        while (!HREF)
            routine();
        skip--;
    }
}

void Camera::waitForHREFFalling(uint16_t skip, void (*routine)(void))
{
    while (skip >= 0)
    {
        while (!HREF)
            routine();
        while (HREF)
            routine();
        skip--;
    }
}

void Camera::waitForVSYNCRising(uint16_t skip, void (*routine)(void))
{
    while (skip >= 0)
    {
        while (VSYNC)
            routine();
        while (!VSYNC)
            routine();
        skip--;
    }
}

void Camera::waitForVSYNCFalling(uint16_t skip, void (*routine)(void))
{
    while (skip >= 0)
    {
        while (!VSYNC)
            routine();
        while (VSYNC)
            routine();
        skip--;
    }
}

//          UART-related

bool Camera::uartIsReady() //! move to other file
{
    return UCSR0A & (1 << UDRE0);
}

void Camera::uartWaitForPreviousByteToBeSent()
{ //! move to other file
    while (!isUartReady())
        ; // wait for byte to transmit
}

bool Camera::setupCamera()
{
    bool res = true;

    // reset
    resetCamera();
    // write default
    res &= setCameraRegisters(regsDefault, 2);
    // write resolution
    res &= setCameraImageSize(_imageSize);
    // write colorspace
    res &= setCameraColorspace(_imageSize);
    // set prescaler
    res &= setCameraPresaler(_prescaler);

    return res;
}