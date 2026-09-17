#include "AutoPilot.h"
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

static const int DX[4] = {0, 1, 0, -1};
static const int DY[4] = {-1, 0, 1, 0};
constexpr int HUNGER_LIMIT = 80;

static bool bfsPath(const vector<vector<bool>> &blocked, Point start, Point goal, int width, int height, vector<Point> &path)
{
    path.clear();
    if (start == goal)
        return true;

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
    while (!(cur == start))
    {
        path.push_back(cur);
        cur = parent[cur.y][cur.x];
    }
    reverse(path.begin(), path.end());
    return true;
}

static bool bfsFirstStep(const vector<vector<bool>> &blocked, Point start, Point goal, int width, int height, Point &outStep)
{
    vector<Point> path;

    if (!bfsPath(blocked, start, goal, width, height, path))
        return false;
    outStep = path.empty() ? start : path.front();
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

static deque<Point> simulateWalk(const deque<Point> &body, const vector<Point> &path, const Point &food)
{
    deque<Point> after = body;
    for (const Point &cell : path)
    {
        bool willGrow = (cell == food);
        after.push_front(cell);
        if (!willGrow)
            after.pop_back();
    }
    return after;
}

static bool isPathSafe(const deque<Point> &body, const vector<Point> &path, const Point &food, int width, int height)
{
    if (path.empty())
        return true;

    deque<Point> after = simulateWalk(body, path, food);
    Point newHead = after.front();
    Point newTail = after.back();
    vector<vector<bool>> afterBlocked = buildBlocked(after, width, height);

    Point dummy;
    return bfsFirstStep(afterBlocked, newHead, newTail, width, height, dummy);
}

Direction nextDirection(const Snack &snake, const Point &food, int width, int height, int stepsSinceEat)
{
    const auto &body = snake.getBody();
    Point head = body.front();
    vector<vector<bool>> blocked = buildBlocked(body, width, height);

    vector<Point> path;
    if (bfsPath(blocked, head, food, width, height, path) && !path.empty())
    {
        bool safe = isPathSafe(body, path, food, width, height);
        if (safe || stepsSinceEat > HUNGER_LIMIT)
            return stepToDirection(head, path.front(), snake.getDirection());
    }

    Point step;
    if (bfsFirstStep(blocked, head, body.back(), width, height, step))
        return stepToDirection(head, step, snake.getDirection());
    return snake.getDirection();
}