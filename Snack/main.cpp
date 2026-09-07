#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Snack.h"
#include "UI.h"

using namespace std;
constexpr int STEP_DELAY_MS = 150;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Snack snake(PLAY_WIDTH / 2, PLAY_HEIGHT / 2);

	bool gameOver = false;
	while (!gameOver)
	{
		if (_kbhit())
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

			snake.setDirection(dir);
		}

		snake.move();

		Point head = snake.getBody().front();
		if (head.x <= 0 || head.x > PLAY_WIDTH || head.y <= 0 || head.y > PLAY_HEIGHT)
			gameOver = true;

		draw(snake);
		Sleep(STEP_DELAY_MS);
	}

	cout << "你寄了" << endl;

	return 0;
}