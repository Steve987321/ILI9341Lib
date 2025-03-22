#include "../vendor/catch2/catch.hpp"

#include <cstdint>

using COLOR16 = uint16_t;

/// @brief
/// Same as ILI9341:::ToColor()
/// r g b should be between 0 ad 31 
COLOR16 ToColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (COLOR16)(((uint16_t)b & 0x1F) << 11 | ((uint16_t)g & 0x1F) << 6 | (uint16_t)r & 0x1F);
}

TEST_CASE("Test ToColor16")
{
    COLOR16 col = ToColor(31, 31, 31);
    REQUIRE(col == 65535);

    col = ToColor(0, 0, 0);
    REQUIRE(col == 0);
}
