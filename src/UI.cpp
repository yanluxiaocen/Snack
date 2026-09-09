#include "UI.h"
#include <iostream>
#include <windows.h>

using namespace std;

void draw(const Snack &snake, const Point &food, int score)
{
    char grid[PLAY_HEIGHT + 2][PLAY_WIDTH + 2];
    for (int y = 0; y < PLAY_HEIGHT + 2; ++y)
        for (int x = 0; x < PLAY_WIDTH + 2; ++x)
            grid[y][x] = (x == 0 || x == PLAY_WIDTH + 1 || y == 0 || y == PLAY_HEIGHT + 1) ? '#' : ' ';

    for (const Point &p : snake.getBody())
        grid[p.y][p.x] = 'o';
    grid[snake.getBody().front().y][snake.getBody().front().x] = '@';

    grid[food.y][food.x] = '*';

    COORD topLeft = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), topLeft);

    cout << "WASD/方向键 转向 · Q 退出" << endl;
    for (int y = 0; y < PLAY_HEIGHT + 2; ++y)
    {
        for (int x = 0; x < PLAY_WIDTH + 2; ++x)
            cout << grid[y][x];
        cout << endl;
    }
}
