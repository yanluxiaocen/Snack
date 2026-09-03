#pragma once
#include <deque>
#include "Point.h"

enum class Direction
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
};

class Snack
{
private:
	std::deque<Point> m_body;
	Direction m_direction;
	bool m_isGrow;

public:
	Snack(int startX, int startY);
	void move();
	void grow();
	bool isHeadAt(const Point &pos) const;

	const std::deque<Point> &getBody() const;
	Direction getDirection() const;
};