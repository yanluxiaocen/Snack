#include "Snack.h"
#include "doctest.h"

TEST_CASE("Snack：初始为 1 节、头在起点、方向向上")
{
    Snack s(5, 5);

    CHECK(s.getBody().size() == 1);
    CHECK(s.isHeadAt(Point(5, 5)));
    CHECK(s.getDirection() == Direction::Up);
}

TEST_CASE("Snack：向上移动，头的 y 减 1")
{
    Snack s(5, 5);
    s.setDirection(Direction::Up);
    s.move();
    CHECK(s.isHeadAt(Point(5, 4)));
}

TEST_CASE("Snack：向右移动，头的 x 加 1")
{
    Snack s(5, 5);
    s.setDirection(Direction::Right);
    s.move();
    CHECK(s.isHeadAt(Point(6, 5)));
}

TEST_CASE("Snack：向下移动，头的 y 加 1")
{
    Snack s(5, 5);
    s.setDirection(Direction::Down);
    s.move();
    CHECK(s.isHeadAt(Point(5, 6)));
}

TEST_CASE("Snack：向左移动，头的 x 减 1")
{
    Snack s(5, 5);
    s.setDirection(Direction::Left);
    s.move();
    CHECK(s.isHeadAt(Point(4, 5)));
}

TEST_CASE("Snack：grow 只打标记，下一次 move 才变长且旧尾保留")
{
    Snack s(5, 5);
    s.grow();
    CHECK(s.getBody().size() == 1);      // 标记不立即生效
    s.move();
    CHECK(s.getBody().size() == 2);      // 消化标记：不弹尾
    CHECK(s.getBody().back() == Point(5, 5)); // 旧尾还在 —— 这就是变长的证据
}

TEST_CASE("Snack：长度 >1 时反向掉头被拒")
{
    Snack s(5, 5);
    s.grow();
    s.move();                            // 长度变 2，方向仍为 Up
    s.setDirection(Direction::Down);     // 反向 → 应被拒绝
    CHECK(s.getDirection() == Direction::Up);
}

TEST_CASE("Snack：长度 >1 时 90° 转弯允许")
{
    Snack s(5, 5);
    s.grow();
    s.move();                            // 长度变 2
    s.setDirection(Direction::Right);    // 90° → 允许
    CHECK(s.getDirection() == Direction::Right);
}
