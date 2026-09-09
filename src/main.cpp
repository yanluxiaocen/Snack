#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "Snack.h"
#include "UI.h"

using namespace std;
constexpr int STEP_DELAY_MS = 150;

bool isOnSnake(const Snack &snake, const Point &pos)
{
	for (const Point &p : snake.getBody())
		if (p == pos)
			return true;
	return false;
}

Point makeFood(const Snack &snake)
{
	Point food;
	do
	{
		food.x = rand() % PLAY_WIDTH + 1;
		food.y = rand() % PLAY_HEIGHT + 1;
	} while (isOnSnake(snake, food));
	return food;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	srand((unsigned)time(nullptr));

	Snack snake(PLAY_WIDTH / 2, PLAY_HEIGHT / 2);
	int score = 0;
	Point food = makeFood(snake);

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

		if (!gameOver && snake.isHeadAt(food))
		{
			snake.grow();
			++score;
			food = makeFood(snake);
		}

		draw(snake, food, score);
		Sleep(STEP_DELAY_MS);
	}

	cout << "你寄了，得分：" << score << endl;
	cin.get();

	return 0;
}