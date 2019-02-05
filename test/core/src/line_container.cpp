#include <catch2/catch.hpp>
#include "utils.hpp"

#include <rvi/transform2.hpp>
#include <rvi/line_container.hpp>

using namespace rvi;

TEST_CASE("line_container::apply_transform(*)")
{
    SECTION("Default transform")
    {
        transform2 tform(vector2(0, 0), vector2(1,1), 0.0F);
        line_container lnc;
        lnc.push_back(
            vector2(1,1), 
            color_rgba(120,120,45,255), 
            vector2(2,2), 
            color_rgba(210,210,54,52)
        );
        lnc.apply_transform(tform);
        line_position_data pdata = lnc.position_data_at(0);
        REQUIRE(pdata.start().x == Approx(1.0F));
        REQUIRE(pdata.start().y == Approx(1.0F));
        REQUIRE(pdata.end().x   == Approx(2.0F));
        REQUIRE(pdata.end().y   == Approx(2.0F));
    }
}