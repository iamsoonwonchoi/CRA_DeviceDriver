#include "device_driver.h"
#include <iostream>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int data_in_flash = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++)
    {
        int cur_data_in_flash = (int)(m_hardware->read(address));
        if (data_in_flash != cur_data_in_flash) throw ReadFiveTimeFail();
    }
    return data_in_flash;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int read_data = read(address);
    if (read_data != EMPTY)
    {
        throw WriteFail();
    }

    m_hardware->write(address, (unsigned char)data);
}