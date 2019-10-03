// matrix44.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "matrix4x4.h"

using namespace std;

int main()
{
	matrix4x4 a,b,c;
	cin >> a;

	//试一试强转成参数列表的xxx&格式——可以
	cout << (matrix4x4&)(a + b) << endl; // 参数列表去除&后又报我一个有多个<<重载的错orz
	//cout << c << endl;
	//c = a^3 ;
	/*cout << a(1, 1) << a(3, 2) << endl;
	cout << a(-2, -2) << endl;*/
	//cout << c << endl;
	//cout << a << endl;
	cout << endl<<a.Det() << endl;
	
	cout << endl << (matrix4x4&)a.Trans() << endl;
	//matrix4x4 d(0);
	//d = a.Inverse();
	//cout << d << endl;
	cout << endl << (matrix4x4&)a.Inverse() << endl;
	

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
