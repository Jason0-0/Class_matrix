#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#define MATRIX_LEN 4
#include <iostream>
#include <string>
#include <memory.h>
/*
TODO： 赋值或计算后还是求逆时才计算秩？
		二维数组的=重载
		重载返回非常变量引用的<<重载
		^重载实现负次幂
*/

using namespace std;

class matrix4x4
{
public:
	matrix4x4();
	matrix4x4(int Val); //用于乘法
	//template<typename T>
	matrix4x4( double mat[][MATRIX_LEN]);

	matrix4x4 operator+(const matrix4x4& add);
	matrix4x4 operator-(const matrix4x4& sub);
	matrix4x4 operator*(const matrix4x4& muti);			//已测试
	matrix4x4 operator^(const int pow);					//已测试
	matrix4x4 operator=(const matrix4x4& right);		//已测试
	double& operator()(const int  row, const int col);	//已测试
	
	friend istream& operator>> (istream& is, matrix4x4& mt);	//已测试
	friend ostream& operator<<(ostream& os,const matrix4x4& mt);		//已测试
	//friend ostream& operator<<(ostream&, matrix4x4);		

	matrix4x4 Trans();		//已测试
	matrix4x4 Inverse();	//已测试
	double Det();			//已测试

	~matrix4x4();

private:

	double ERRORCODE = 0.0;
	double matrix[MATRIX_LEN][MATRIX_LEN];
	//double rule;	//矩阵的秩

	//用于进行初等变换的函数
	double* operator()(const int row);			//重载（）以访问行
	void Add(double* pDst, double* pSrc);		//可弃用
	void Minus(double* pDst, double* pSrc);		//可弃用
	void ValMuti(double* pSrc, double Val);
	void MutiAdd(double* pDst,double* pSrc , double Val);	//可弃用
	void MutiMinus(double* pDst, double* pSrc, double Val);

	//交换行
	void ExchangeRow(double* row1, double* row2)
	{
		for (int i = 0; i < MATRIX_LEN; i++)
		{
			double temp = row1[i];
			row1[i] = row2[i];
			row2[i] = temp;
		}	
	}



};

//输入输出重载
//istream& operator>> (istream&, matrix4x4&);
//ostream& operator<<(ostream&, matrix4x4&);
//ostream& operator<<(ostream&, matrix4x4);


#endif // MATRIX4X4_H


