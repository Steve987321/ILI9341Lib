#ifndef TYPES_H
#define TYPES_H

#ifndef __AVR // when running tests 
#include <cstdint>
#else 
#include <Arduino.h>
#endif

/// @brief 
/// Minimal vector 2 with x and y components of type 8 bit unsigned integers.
struct Vec2u8
{
    Vec2u8(uint8_t x, uint8_t y);

    uint8_t x = 0;
    uint8_t y = 0;
};

/// @brief 
/// Minimal vector 2 with x and y components of type floats.
struct Vec2f
{
    Vec2f(float x, float y);

    float x = 0;
    float y = 0;
};
#endif 