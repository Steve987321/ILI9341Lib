#ifndef ILI9341_H
#define ILI9341_H

#include <Arduino.h>

#include "ILI9341SPI.h"
#include "8x8Font.h"
 
/// @brief 
/// Holds default settings/args for the initial commands for the ILI9341 
struct ILI9341Settings
{
    uint8_t mem_access_control[1] = {0b01000000};         // only sets MX: Column address order, good for vertical display.
    uint8_t pixel_format_set_args[1] = {0b01010101};       // RGB interface format 
    uint8_t rgb_interface_signal_control_args[1] = {0b01100001};

    // these values are maxed out 0s also work
    uint16_t negative_gamma_correction_args[15] = 
    {
        0b1111, 
        0b111111,
        0b111111,
        0b1111,
        0b11111, 
        0b1111, 
        0b1111111, 
        0xFF, 
        0b1111111, 
        0b1111, 
        0b11111, 
        0b1111, 
        0b111111, 
        0b111111, 
        0b1111 
    };      
};

/// @brief 
/// Class for the ILI9341 TFT LCD using SPI. 
/// Handles simple drawing and sending commands to the chip
///
/// When drawing text it uses an 8x8 font bitmap stored in flash. 
/// https://github.com/dhepper/font8x8
class ILI9341 : ILI9341SPI
{
public: 
    /// @brief 
    /// Sets the needed pins for communication (SPI).
    /// SPI pins on the Arduino Uno 10(cs), 11(mosi), 12(miso), 13(sck).
    /// @param cs Chip select pin 
    /// @param dc Data select pin 
    /// @param reset Reset pin for initialization
    ILI9341(int8_t cs, int8_t dc, int8_t reset);

    ~ILI9341();

public: 
    /// @brief 
    /// When using WritePixel, this will specify how to read the pixels direction.
    /// @see WritePixel();
    enum class ROTATION_FLAGS : uint8_t
    {
        NONE = 0,
        XMIRRORED = 1 << 0,
        YMIRRORED = 1 << 1,
    };

    /// @brief 16 bit value for storing colors, formatted in: BBBBBGGGGGxRRRRR
    using COLOR16 = uint16_t;

public:
    const static uint8_t display_width = 240;
    const static uint16_t display_height = 320;

public:
    /// @brief
    /// Initializes the display. 
    /// If you want to modify chip settings call SetSettings first.
    /// @see SetSettings()
    void Init();

    /// @brief
    /// Draws a pixel at a given position.
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param color Pixel color, format: BBBBBGGGGGxRRRRR
    void DrawPixel(uint8_t x, uint16_t y, COLOR16 color);

    /// @brief 
    /// Draws a character at a given position.
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param c Character to draw
    /// @param color Color of character, format: BBBBBGGGGGxRRRRR
    void DrawChar(uint8_t x, uint16_t y, char c, COLOR16 color = 0, float size = 1.f);

    /// @brief 
    /// Draws a string at a given position.
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param str Pointer to character array
    /// @param stringlength Character array length
    /// @param color color of string, format: BBBBBGGGGGxRRRRR
    void DrawString(uint8_t x, uint16_t y, const char* str, uint16_t stringlength = 0, COLOR16 color = 0, float size = 1.f);

    /// @brief 
    /// Draws a rectangle given the dimensions, faster then using DrawPixel for areas.
    /// @param x Starting position x
    /// @param y Starting position y 
    /// @param color Color of rect
    /// @param x2 Ending position x 
    /// @param y2 Ending position y 
    void DrawRect(uint8_t x, uint16_t y, COLOR16 color = 0, uint8_t sizex = ILI9341::display_width, uint16_t sizey = 1);

    /// @brief 
    /// Sets custom screen coordinates.
    /// @param rotation Rotation flags used, reset by using ResetRotation
    /// @see ResetRotation()
    void SetRotation(ROTATION_FLAGS rot);

    /// @brief 
    /// Sets screen coordinates to default. 
    void ResetRotation();

    /// @brief 
    /// Sets new starting settings for the ILI9341, this should only be called before Init().
    /// @param settings Struct filled with new settings/args
    void SetSettings(const ILI9341Settings& new_settings);

    /// @brief 
    /// Formats rgb to the 16 bit format. 
    /// Formatted to BBBBBGGGGGxRRRRR.
    /// @param r Red value max 31
    /// @param g Green value max 31
    /// @param b Blue value max 31
    /// @return Returns the formatted 16 bit color
    /// @see COLOR16
    static COLOR16 ToColor(uint8_t r, uint8_t g, uint8_t b);

private: 
    /// @brief 
    /// Reset pin to initialize the chip.
    int8_t reset = 0;

    /// @brief Used by DrawPixel() to set direction.
    /// @see DrawPixel()
    /// @see SetRotation()
    /// @see ResetRotation()
    ROTATION_FLAGS rotation = ROTATION_FLAGS::NONE;

    /// @brief Starting settings used in Init();
    /// @see Init()
    ILI9341Settings settings;
};

ILI9341::ROTATION_FLAGS operator | (ILI9341::ROTATION_FLAGS a, ILI9341::ROTATION_FLAGS b);
ILI9341::ROTATION_FLAGS operator & (ILI9341::ROTATION_FLAGS a, ILI9341::ROTATION_FLAGS b);

#endif