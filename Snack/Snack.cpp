#include"Snack.h"

Snack::Snack(int startX, int startY) : m_direction(0), m_isGrow(false){
    m_body.push_back(Point(startX, startY));
}

bool Snack::isHeadAt(const Point &pos) const{
    return !m_body.empty() && m_body.front() == pos;
}

const std::deque<Point>& Snack::getBody() const{
    return m_body;
}

int Snack::getDirection() const{
    return m_direction;
}