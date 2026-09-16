#include "doctest.h"
#include "AutoPilot.h"
#include "Snack.h"

TEST_CASE("直线追食物")
{
    Snack s(5, 5);
    Direction d = nextDirection(s, Point(5, 2), 32, 16);
    CHECK(d == Direction::Up);
}

TEST_CASE("向右追食物")
{
    Snack s(5, 5);
    Direction d = nextDirection(s, Point(8, 5), 32, 16);
    CHECK(d == Direction::Right);
}

TEST_CASE("长度 1 可反向")
{
    Snack s(5, 5);
    Direction d = nextDirection(s, Point(5, 7), 32, 16);
    CHECK(d == Direction::Down);
}

TEST_CASE("绕开自身")
{
    Snack s(5, 5);
    s.grow();
    s.move();
    s.grow();
    s.move();

    s.setDirection(Direction::Right);
    s.grow();
    s.move();

    s.setDirection(Direction::Down);
    s.grow();
    s.move();
    CHECK(nextDirection(s, Point(4, 4), 32, 16) == Direction::Down);
}

TEST_CASE("尾巴不算障碍")
{
    Snack s(5, 5);
    s.grow();
    s.move();
    Direction d = nextDirection(s, Point(5, 6), 32, 16);
    CHECK(d == Direction::Down);
}

TEST_CASE("不可达保底")
{
    Snack s(5, 5);
    Direction d = nextDirection(s, Point(0, 0), 32, 16);
    CHECK(d == Direction::Up);
}