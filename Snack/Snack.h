#pragma once
#include <deque>
#include"Point.h"

class Snack {
private:
	std::deque<Point> m_body;
	int m_direction;
	bool m_isGrow;

public:
	Snack(int startX, int startY);
	void move();
	void grow();
	bool isHeadAt(const Point& pos) const;

	const std::deque<Point>& getBody() const;
	int getDirection() const;
};