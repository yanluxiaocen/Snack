#include <iostream>
#include "Snack.h"
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Snack snake(3, 5); // 从 (3,5) 出发

	cout << "body size   = " << snake.getBody().size() << "  (期望 1)" << endl;

	cout << boolalpha; // 让 bool 打印成 true/false 而不是 1/0
	cout << "head (3,5)? = " << snake.isHeadAt(Point(3, 5)) << "  (期望 true)" << endl;
	cout << "head (0,0)? = " << snake.isHeadAt(Point(0, 0)) << "  (期望 false)" << endl;

	cout << "direction   = " << snake.getDirection() << "  (期望 0)" << endl;

	const auto &body = snake.getBody(); // 拿常引用，验证不拷贝
	cout << "body[0]     = (" << body.front().x << ", " << body.front().y << ")  (期望 (3, 5))" << endl;

	cin.get();
	return 0;
}