#include "AutoPilot.h"
#include <queue>
#include <vector>

using namespace std;

static const int DX[4] = {0, 1, 0, -1};
static const int DY[4] = {-1, 0, 1, 0};

Direction nextDirection(const Snack &snake, const Point &food, int width, int height)
{
    Point head = snake.getBody().front();

    vector<vector<bool>> blocked(height + 2, vector<bool>(width + 2, false));
    const auto &body = snake.getBody();
    for (size_t i = 0; i < body.size(); ++i)
    {
        if (i == body.size() - 1)
            continue;
        if (i == 0)
            continue;
        blocked[body[i].y][body[i].x] = true;
    }

    vector<vector<bool>> visited(height + 2, vector<bool>(width + 2, false));
    vector<vector<Point>> parent(height + 2, vector<Point>(width + 2, Point(-1, -1)));
    queue<Point> q;

    visited[head.y][head.x] = true;
    q.push(head);
    bool found = false;

    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();

        if (cur == food)
        {
            found = true;
            break;
        }

        for (int d = 0; d < 4; ++d)
        {
            int nx = cur.x + DX[d];
            int ny = cur.y + DY[d];

            if (nx < 1 || nx > width || ny < 1 || ny > height)
                continue;
            if (visited[ny][nx] || blocked[ny][nx])
                continue;

            visited[ny][nx] = true;
            parent[ny][nx] = cur;
            q.push(Point(nx, ny));
        }
    }

    if (!found)
        return snake.getDirection();

    Point step = food;
    while (!(parent[step.y][step.x] == head))
        step = parent[step.y][step.x];

    int dx = step.x - head.x;
    int dy = step.y - head.y;
    for (int d = 0; d < 4; ++d)
        if (DX[d] == dx && DY[d] == dy)
            return static_cast<Direction>(d);

    return snake.getDirection();
}