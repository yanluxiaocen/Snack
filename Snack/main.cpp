#include <iostream>
#include "Snack.h"
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Snack snack(5, 5);

	while (true)
	{
		int ch = _getch();
		if (ch == 0 || ch == 224)
			ch = _getch();
		Direction dir = Direction::Up;
		switch (ch)
		{
		case 'w':
		case 'W':
		case 72:
			dir = Direction::Up;
			break;
		case 's':
		case 'S':
		case 80:
			dir = Direction::Down;
			break;
		case 'a':
		case 'A':
		case 75:
			dir = Direction::Left;
			break;
		case 'd':
		case 'D':
		case 77:
			dir = Direction::Right;
			break;
		case 'q':
		case 'Q':
			return 0;
		default:
			continue;
		}

		snack.setDirection(dir);
		snack.move();
		cout << "头=(" << snack.getBody().front().x << "," << snack.getBody().front().y << ") 长度=" << snack.getBody().size() << endl;
	}

	return 0;
}