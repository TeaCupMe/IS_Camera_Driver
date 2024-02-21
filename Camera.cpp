#include <Wire.h>
#include "Arduino.h"

#include "Camera.h"

Camera::Camera(ImageSize imageSize, Colorspace colorspace)
{
    _colorspace = colorspace;
    _imageSize = imageSize;
}

void Camera::setCameraImageSize(ImageSize imageSize)
{
    _imageSize = imageSize;
    setCameraRegisters();
}
