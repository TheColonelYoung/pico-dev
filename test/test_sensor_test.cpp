#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>

#include "sensor_test.hpp"

TEST_CASE("ID_test", "[ID_test]" ) {
        REQUIRE(ID_test(0x82));
        REQUIRE(ID_test(0x80) == 0x82);
}
