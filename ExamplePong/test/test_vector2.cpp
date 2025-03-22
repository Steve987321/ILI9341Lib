#include "../vendor/catch2/catch.hpp"

#include "../src/Types.h"

TEST_CASE("Test Vec2u8")
{
    Vec2u8 v(0, 0);
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);

    v.x = 10;
    REQUIRE(v.x == 10);

    v.x = 256;
    REQUIRE(v.x == 0);
}

TEST_CASE("Test Vec2f")
{
    Vec2f v(0.f, 0.f);
    REQUIRE(v.x == 0.f);
    REQUIRE(v.y == 0.f);

    v.x = 10.f;
    REQUIRE(v.x == 10.f);
}
