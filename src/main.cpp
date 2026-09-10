#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "Snack.h"
#include "UI.h"
#include "AutoPilot.h"

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

	while (true)
	{
		Snack snake(PLAY_WIDTH / 2, PLAY_HEIGHT / 2);
		int score = 0;
		Point food = makeFood(snake);

		bool gameOver = false;
		bool autoMode = false;
		while (!gameOver)
		{
			if (_kbhit())
			{
				int ch;
				do
				{
					ch = _getch();
					if (ch == 0 || ch == 224)
						ch = _getch();
				} while (_kbhit());

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
				case 'e':
				case 'E':
					autoMode = !autoMode;
					continue;
				case 'q':
				case 'Q':
					return 0;
				default:
					continue;
				}
				if (!autoMode)
					snake.setDirection(dir);
			}
			if (autoMode)
				snake.setDirection(nextDirection(snake, food, PLAY_WIDTH, PLAY_HEIGHT));
			snake.move();

			Point head = snake.getBody().front();
			if (head.x <= 0 || head.x > PLAY_WIDTH || head.y <= 0 || head.y > PLAY_HEIGHT)
				gameOver = true;

			if (!gameOver)
			{
				const auto &body = snake.getBody();
				for (size_t i = 1; i < body.size(); i++)
				{
					if (body[i] == head)
					{
						gameOver = true;
						break;
					}
				}
			}
			if (!gameOver && snake.isHeadAt(food))
			{
				snake.grow();
				++score;
				food = makeFood(snake);
			}

			draw(snake, food, score);
			Sleep(STEP_DELAY_MS);
		}

		std::cout << "你寄了，得分：" << score << endl;
		std::cout << "按 R 再来一局，按 Q 退出" << endl;
		while (true)
		{
			int ch = _getch();
			if (ch == 0 || ch == 224)
				ch = _getch();
			if (ch == 'r' || ch == 'R')
				break;
			if (ch == 'q' || ch == 'Q')
				return 0;
		}
	}
}