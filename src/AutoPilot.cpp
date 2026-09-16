#include "AutoPilot.h"
#include <queue>
#include <vector>

using namespace std;

static const int DX[4] = {0, 1, 0, -1};
static const int DY[4] = {-1, 0, 1, 0};

static bool bfsFirstStep(const vector<vector<bool>> &blocked, Point start, Point goal, int width, int height, Point &outStep)
{
    if (start == goal)
    {
        outStep = start;
        return true;
    }

    vector<vector<bool>> visited(height + 2, vector<bool>(width + 2, false));
    vector<vector<Point>> parent(height + 2, vector<Point>(width + 2, Point(-1, -1)));
    queue<Point> q;

    visited[start.y][start.x] = true;
    q.push(start);
    bool found = false;

    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();

        if (cur == goal)
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
        return false;

    Point cur = goal;
    while (!(parent[cur.y][cur.x] == start))
        cur = parent[cur.y][cur.x];

    outStep = cur;
    return true;
}

static vector<vector<bool>> buildBlocked(const deque<Point> &body, int width, int height)
{
    vector<vector<bool>> blocked(height + 2, vector<bool>(width + 2, false));
    for (size_t i = 0; i < body.size(); ++i)
    {
        if (i == body.size() - 1)
            continue;
        if (i == 0)
            continue;
        blocked[body[i].y][body[i].x] = true;
    }
    return blocked;
}

static Direction stepToDirection(Point from, Point to, Direction fallback)
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    for (int d = 0; d < 4; ++d)
        if (DX[d] == dx && DY[d] == dy)
            return static_cast<Direction>(d);
    return fallback;
}

Direction nextDirection(const Snack &snake, const Point &food, int width, int height)
{
    Point head = snake.getBody().front();
    Point step = food;
    if (bfsFirstStep(buildBlocked(snake.getBody(), width, height), head, food, width, height, step))
    {
        return stepToDirection(head, step, snake.getDirection());
    }
    return snake.getDirection();
}

static bool isMoveSafe(const deque<Point> &body, Point newHead, bool willGrow, int width, int height)
{
    deque<Point> after;
    after.push_front(newHead);
    size_t keep = willGrow ? body.size() : body.size() - 1;
    for (size_t i = 0; i < keep; i++)
        after.push_back(body[i]);

    Point newTail = after.back();

    vector<vector<bool>> afterBlocked = buildBlocked(after, width, height);
    Point dummy;
    return bfsFirstStep(afterBlocked, newHead, newTail, width, height, dummy);
}