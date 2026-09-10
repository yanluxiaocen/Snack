#include "Point.h"
#include "doctest.h"

TEST_CASE("Point：坐标不同判等为假")
{
    Point x(7, 8);
    Point y(3, 6);

    CHECK_FALSE(x == y);
}

TEST_CASE("Point：坐标相同判等为真")
{
    Point h(5, 5);
    Point j(5, 5);

    CHECK(h == j);
}

TEST_CASE("Point：默认构造得 (0,0)")
{
    Point a;
    CHECK(a.x == 0);
    CHECK(a.y == 0);
}
