#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#define MATRIX_LEN 4
#include <iostream>
#include <string>
#include <memory.h>
/*
TODO： 赋值或计算后还是求逆时才计算秩？
		二维数组的=重载
		想清楚两个相同类的赋值到底需不需要重载=

*/

using namespace std;

class matrix4x4
{
public:
	matrix4x4();
	matrix4x4(int Val); //用于乘法
	template<typename T>
	matrix4x4(T const mat[][MATRIX_LEN]);
	matrix4x4 operator+(const matrix4x4& add);
	matrix4x4 operator-(const matrix4x4& sub);
	matrix4x4 operator*(const matrix4x4& muti);
	matrix4x4 operator^(const int pow);
	matrix4x4 operator=(const matrix4x4& right);
	double& operator()(const int  row, const int col);
	
	friend istream& operator>> (istream& is, matrix4x4& mt);
	friend ostream& operator<<(ostream& os, matrix4x4& mt);

	matrix4x4& Trans();
	matrix4x4 Reverse();	//TODO 还没写呢！

	double Det();			//TODO 同样没写什么


	~matrix4x4();

private:

	double ERRORCODE = 0.0;
	double matrix[MATRIX_LEN][MATRIX_LEN];
	double rule;	//矩阵的秩
	//int CalRule();

	//用于进行初等变换的函数
	double* operator()(const int row);
	void Add(double* pDst, double* pSrc);
	void Minus(double* pDst, double* pSrc);
	void MutiAdd(double* pDst,double* pSrc , double Val);
	void MutiMinus(double* pDst, double* pSrc, double Val);
	//交换行
	void ExchangeRow(double* row1, double* row2)
	{
		double* temp = row1;
		row1 = row2;
		row2 = temp;
	}



};

//输入输出重载
istream& operator>> (istream&, matrix4x4&);
ostream& operator<<(ostream&, matrix4x4&);



#endif // MATRIX4X4_H


