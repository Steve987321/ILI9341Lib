#include "ILI9341SPI.h"
#include <Arduino.h>

ILI9341SPI::ILI9341SPI(int8_t cs, int8_t dc)
 : cs(cs), dc(dc)
{
}

void ILI9341SPI::Init()
{
    // setup SPI commuication
    pinMode(cs, OUTPUT);
    pinMode(dc, OUTPUT);

    SPI.begin();
}

void ILI9341SPI::WriteCommand16(COMMAND command, uint16_t *args, uint16_t arglen)
{
    SPIStartCommand((uint8_t)command);

    // write args 
    if (args && arglen > 0)
    {
        for (int i = 0; i < arglen; i++)
        {
            SPI.transfer16(args[i]);
        }
    }

    SPIEnd();
}

void ILI9341SPI::WriteCommandProgMem(COMMAND command, const uint8_t* args, uint16_t arglen)
{
    SPIStartCommand((uint8_t)command);

    // write args
    for (int i = 0; i < arglen; i++)
        SPI.transfer(pgm_read_byte(args++));

    SPIEnd();
}

void ILI9341SPI::WriteCommand(COMMAND command, uint8_t* args, uint16_t arglen)
{
    SPIStartCommand((uint8_t)command);

    // write args 
    if (args && arglen > 0)
    {
        for (int i = 0; i < arglen; i++)
        {
            SPI.transfer(args[i]);
        }
    }

    SPIEnd();
}

void ILI9341SPI::WriteCommandSameArgMultipleTimes(COMMAND command, uint8_t arg, uint16_t count)
{
    SPIStartCommand((uint8_t)command);

    // write args 
    for (uint16_t i = 0; i < count; i++)
        SPI.transfer(arg);

    SPIEnd();
}

void ILI9341SPI::WriteCommandSameArgMultipleTimes16(COMMAND command, uint16_t arg, uint16_t count)
{   
    SPIStartCommand((uint8_t)command);

    // write args 
    for (uint16_t i = 0; i < count; i++)
        SPI.transfer16(arg);

    SPIEnd();
}

void ILI9341SPI::SPIStartCommand(uint8_t command)
{
    SPI.beginTransaction(spi_settings);
    digitalWrite(cs, LOW);

    // low = command
    digitalWrite(dc, LOW);

    // write command
    SPI.transfer(command);

    // data select for possible arguments
    digitalWrite(dc, HIGH);
}

void ILI9341SPI::SPIEnd()
{
    digitalWrite(cs, HIGH);
    SPI.endTransaction();
}
