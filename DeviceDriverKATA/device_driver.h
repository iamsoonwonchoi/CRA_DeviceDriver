#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFiveTimeFail : public std::exception
{

};

class WriteFail : public std::exception
{

};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
private:
    static const int EMPTY = 0xFF;
};