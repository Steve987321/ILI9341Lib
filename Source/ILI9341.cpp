#include "ILI9341.h"

ILI9341::ILI9341(int8_t cs, int8_t dc, int8_t reset)
 : ILI9341SPI(cs, dc), reset(reset)
{
}

ILI9341::~ILI9341() = default;

void ILI9341::Init()
{
    // Setup spi
    ILI9341SPI::Init();

    // send the reset signal to initialize the chip 
    pinMode(reset, OUTPUT);

    digitalWrite(reset, HIGH);
    delay(50);
    digitalWrite(reset, LOW);
    delay(50);
    digitalWrite(reset, HIGH);
    delay(150);
    
    // set drawing direction
    WriteCommand(COMMAND::MEM_ACCESS_CONTROL, settings.mem_access_control, 1);

    WriteCommand(COMMAND::PIXEL_FORMAT_SET, settings.pixel_format_set_args, 1);
    WriteCommand(COMMAND::RGB_INTERFACE_SIGNAL_CONTROL, settings.rgb_interface_signal_control_args, 1);

    // turn off sleep mode and turn on display 
    WriteCommand(COMMAND::SLEEP_OUT); 
    delay(10); // sleep out requires a 5 ms delay
    WriteCommand(COMMAND::DISPLAY_ON);
    
    // set screen brightness higher
    WriteCommand16(COMMAND::NEGATIVE_GAMMA_CORRECTION, settings.negative_gamma_correction_args, 15);
}

void ILI9341::DrawPixel(uint8_t x, uint16_t y, COLOR16 color)
{
    bool custom_rotation = rotation != ROTATION_FLAGS::NONE;
    if (custom_rotation)
    {
        uint8_t mem_access_control_args[1] = {0};

        if ((bool)(rotation & ROTATION_FLAGS::XMIRRORED))
            mem_access_control_args[0] |= 1 << 6;
        if ((bool)(rotation & ROTATION_FLAGS::YMIRRORED))
            mem_access_control_args[0] |= 1 << 5;
        
        WriteCommand(COMMAND::MEM_ACCESS_CONTROL, mem_access_control_args, 1);
    }

    uint16_t col_args[2] = {x, x + 1};
    uint16_t page_args[2] = {y, y + 1};
    WriteCommand16(COMMAND::COLUMN_ADDRESS_SET, col_args, 2); 
    WriteCommand16(COMMAND::PAGE_ADDRESS_SET, page_args, 2); 
    uint16_t mem_write_args[] = {color};
    WriteCommand16(COMMAND::MEM_WRITE, mem_write_args, 1);

    if (custom_rotation)
        WriteCommand(COMMAND::MEM_ACCESS_CONTROL, settings.mem_access_control, 1);
}

void ILI9341::DrawChar(uint8_t x, uint16_t y, char c, COLOR16 color, float size)
{
    uint8_t bit_check = 0;

    // 8x8 font 
    for (uint16_t offx = 0; offx < 8 * size; offx++)
    {
        for (uint16_t offy = 0; offy < 8 * size; offy++) 
        {
            bit_check = (uint8_t)pgm_read_byte(&font8x8_basic[c][(uint8_t)(offy / size)]) & 1 << uint8_t(offx / size);
            if (bit_check)
                DrawPixel(x + offx, y + offy, color);
        }
    }
}

void ILI9341::DrawString(uint8_t x, uint16_t y, const char* str, uint16_t stringlength, COLOR16 color, float size)
{
    if (!stringlength)
        stringlength = strlen(str);

    for (uint16_t i = 0; i < stringlength; i++)
        DrawChar(x + i * 8 * size, y, str[i], color, size); // 8 is the fontsize 
}

void ILI9341::DrawRect(uint8_t x, uint16_t y, COLOR16 color, uint8_t sizex, uint16_t sizey)
{
    uint16_t col_args[2] = {x, sizex};
    uint16_t page_args[2] = {y, sizey};
    WriteCommand16(COMMAND::COLUMN_ADDRESS_SET, col_args, 2); 
    WriteCommand16(COMMAND::PAGE_ADDRESS_SET, page_args, 2); 

    for (; y < sizey; y++)
    {
        page_args[0] = y;
        WriteCommand16(COMMAND::PAGE_ADDRESS_SET, page_args, 2); 
        WriteCommandSameArgMultipleTimes16(COMMAND::MEM_WRITE, color, display_width);
    }
}

void ILI9341::SetRotation(ROTATION_FLAGS rot)
{
    rotation = rot;
}

void ILI9341::ResetRotation()
{
    rotation = ROTATION_FLAGS::NONE;
}

void ILI9341::SetSettings(const ILI9341Settings& new_settings)
{
    settings = new_settings;
}

ILI9341::COLOR16 ILI9341::ToColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (COLOR16)(((uint16_t)b & 0x1F) << 11 | ((uint16_t)g & 0x1F) << 6 | (uint16_t)r & 0x1F);
}

ILI9341::ROTATION_FLAGS operator|(ILI9341::ROTATION_FLAGS a, ILI9341::ROTATION_FLAGS b)
{
    return static_cast<ILI9341::ROTATION_FLAGS>((uint8_t)a | (uint8_t)b);
}

ILI9341::ROTATION_FLAGS operator&(ILI9341::ROTATION_FLAGS a, ILI9341::ROTATION_FLAGS b)
{
    return static_cast<ILI9341::ROTATION_FLAGS>((uint8_t) a & (uint8_t)b);
}
