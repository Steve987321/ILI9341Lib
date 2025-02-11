#ifndef ILI9341SPI_H
#define ILI9341SPI_h

#include <SPI.h>

/// @brief 
/// Handles SPI communication with the ILI9341.
class ILI9341SPI
{
public:
    /// @brief 
    /// Sets the needed pins for communication (SPI).
    /// SPI pins on the Arduino Uno 10(cs), 11(mosi), 12(miso), 13(sck).
    /// @param cs Chip select pin 
    /// @param dc Data select pin 
    ILI9341SPI(int8_t cs, int8_t dc);

public:
    /// @brief 
    /// Commands that can be sent to the ILI9341.
    enum class COMMAND : uint8_t 
    {
        NOP = 0x00,                         // no op
        SOFTWARE_RESET = 0x01,              // wait 5 ms before next command, causes a reset which is not used as we use RESX pin for hardware reset.
        SLEEP_OUT = 0x11,                   // turns off sleep mode 
        DISPLAY_OFF = 0x28,                 // turns off display
        DISPLAY_ON = 0x29,                  // turns on display
        INVERSION = 0x21,                   // invert display colors
        MEM_WRITE = 0x2C,                   // write to display n args which hold colors 
        MEM_READ = 0x2E,                    // read from display 
        MEM_ACCESS_CONTROL = 0x36,          // how mem write data should be received and directed 1 arg with settings, 8 lsbits.
        PIXEL_FORMAT_SET = 0x3A,            // sets the pixel format for the RGB image data used by the interface. 1 arg with settings, 8 lsbits.
        RGB_INTERFACE_SIGNAL_CONTROL = 0xB0,// sets rgb interface for the display. 1 arg with settings
        INTERFACE_CONTROL = 0xF6,           // sets interface settings with chip  3 args with settings. 
        COLUMN_ADDRESS_SET = 0x2A,          // sets column area to write to using MEM_WRITE, 4 args (start8:15, start0:7, end8:15, end0:7)
        PAGE_ADDRESS_SET = 0x2B,            // sets page area to write to using MEM_WRITE, 4 args (start8:15, start0:7, end8:15, end0:7)
        POSITIVE_GAMMA_CORRECTION = 0xE0,   // sets positive gamma 15 args
        NEGATIVE_GAMMA_CORRECTION = 0xE1,   // sets negative gamma 15 args
    };

public:
    /// @brief 
    /// Initializes SPI communication.
    void Init();

public:
    /// @brief 
    /// Write a command byte with 16 bit parameters.
    /// @param command The command byte
    /// @param args Pointer to the 16 bit arguments (optional)
    /// @param arglen Length of arguments (optional)
    void WriteCommand16(COMMAND command, uint16_t* args = nullptr, uint16_t arglen = 0);

    /// @brief 
    /// Write a command byte with arguments stored in program memory.
    /// @param command The command byte
    /// @param args Pointer to arguments stored in program memory
    /// @param arglen Length of arguments
    void WriteCommandProgMem(COMMAND command, const uint8_t* args, uint16_t arglen);

    /// @brief 
    /// Write a command byte with 8 bit arguments.
    /// @param command The command byte
    /// @param args Pointer to the 8 bit arguments (optional)
    /// @param arglen Length of arguments (optional)
    void WriteCommand(COMMAND command, uint8_t* args = nullptr, uint16_t arglen = 0);

    /// @brief 
    /// Write a command byte with an argument that can be sent multiple times.
    /// 
    /// Writes the command then sends \b arg for \b count times.
    /// Use this function to save memory, for example when filling the screen with the same color. 
    /// @param command The command byte
    /// @param arg Argument byte that gets passed 
    /// @param count How many time the arg will be sent
    void WriteCommandSameArgMultipleTimes(COMMAND command, uint8_t arg, uint16_t count = 1);

    /// @brief 
    /// Write a command byte with an argument that can be sent multiple times. 
    ///
    /// Overload for 16 bit argument data.
    /// @see WriteCommandSameArgMultipleTimes() 
    /// @param command The command byte
    /// @param arg 16 bit argument
    /// @param count How many times we send \b arg
    void WriteCommandSameArgMultipleTimes16(COMMAND command, uint16_t arg, uint16_t count = 1);

private:
    /// @brief 
    /// Sets up SPI and writes a command then sets up for arguments.
    ///
    /// One should call SPIEnd() after writing  
    /// @param command The command byte
    /// @see SPIEnd()
    void SPIStartCommand(uint8_t command);

    /// @brief 
    /// Ends SPI transaction. Call after SPIStartCommand.
    /// @see SpiStartCommand()
    void SPIEnd();

private:
    /// @brief Data select pin.  
    int8_t dc = 0;

    /// @brief Chip select pin.
    int8_t cs = 0;

    SPISettings spi_settings {8000000, MSBFIRST, SPI_MODE0};
};
#endif