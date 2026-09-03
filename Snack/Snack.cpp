#include "Snack.h"

Snack::Snack(int startX, int startY) : m_direction(Direction::Up), m_isGrow(false)
{
    m_body.push_back(Point(startX, startY));
}

bool Snack::isHeadAt(const Point &pos) const
{
    return !m_body.empty() && m_body.front() == pos;
}

const std::deque<Point> &Snack::getBody() const
{
    return m_body;
}

Direction Snack::getDirection() const
{
    return m_direction;
}

void Snack::move()
{
    Point head = m_body.front();
    switch (m_direction)
    {
    case Direction::Up:
        head.y -= 1;
        break;
    case Direction::Right:
        head.x += 1;
        break;
    case Direction::Down:
        head.y += 1;
        break;
    case Direction::Left:
        head.x -= 1;
        break;
    }

    if (m_isGrow)
        m_isGrow = false;
    else
        m_body.pop_back();
    m_body.push_front(head);
}

void Snack::grow()
{
    m_isGrow = true;
}