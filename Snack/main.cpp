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

	cout << "direction   = " << static_cast<int>(snake.getDirection()) << "  (期望 0)" << endl;

	const auto &body = snake.getBody(); // 拿常引用，验证不拷贝
	cout << "body[0]     = (" << body.front().x << ", " << body.front().y << ")  (期望 (3, 5))" << endl;

	// ===== move() / grow() 验证 =====
	snake.move(); // 不成长：正常滑动
	cout << "move 后：头=(" << snake.getBody().front().x << "," << snake.getBody().front().y
		 << ") 长度=" << snake.getBody().size() << "  (期望 头=(3,4) 长度=1)" << endl;

	snake.grow(); // 打成长标记
	snake.move(); // 消化标记：不弹尾
	cout << "成长后：头=(" << snake.getBody().front().x << "," << snake.getBody().front().y
		 << ") 长度=" << snake.getBody().size() << "  (期望 头=(3,3) 长度=2)" << endl;
	cout << "成长后：尾=(" << snake.getBody().back().x << "," << snake.getBody().back().y
		 << ")  (期望 (3,4))" << endl;

	snake.move(); // 标记已消化，恢复滑动
	cout << "再移动：头=(" << snake.getBody().front().x << "," << snake.getBody().front().y
		 << ") 长度=" << snake.getBody().size() << "  (期望 头=(3,2) 长度=2)" << endl;

	cin.get();
	return 0;
}