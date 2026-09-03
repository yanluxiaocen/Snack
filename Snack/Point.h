#pragma once

struct Point
{
	int x, y;

	Point(int x = 0, int y = 0);
	bool operator==(const Point& other) const;
};