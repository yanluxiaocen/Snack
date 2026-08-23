#include<iostream>
#include"Point.h"

using namespace std;

int main() {
	Point point(2, 5);
	Point points(6, 7);
	Point pointsh(2, 5);

	if (point == points)
		cout << "WTF" << endl;
	else cout << "yeah" << endl;

	if (point == pointsh)
		cout << "yeah!" << endl;
	else cout << "WTF?" << endl;

	return 0;
}