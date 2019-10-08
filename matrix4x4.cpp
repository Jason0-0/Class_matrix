//matrix4x4.cpp
//问题：为什么构造和析构函数放.h里会报错，是由于这种.h+.cpp模式必须要把所有定义都放cpp里吗？？
//问题：inline 的使用时机及场合（在类外定义时）

#include <iostream>
#include "matrix4x4.h"

using namespace std;



//构造&析构函数定义及重载
inline matrix4x4::matrix4x4()
{
	memset(matrix, 0, sizeof(double) * MATRIX_LEN * MATRIX_LEN);
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		matrix[i][i] = 1;
	}
	//rule = MATRIX_LEN;
}
inline matrix4x4::matrix4x4(int Val)
{
	memset(this->matrix, Val, sizeof(double) * MATRIX_LEN * MATRIX_LEN);
}


matrix4x4::matrix4x4( double mat[][MATRIX_LEN])
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
	//return *this;
}

inline matrix4x4::~matrix4x4()
{
}

//重载（）
inline double& matrix4x4::operator()(int row, int col)
{
	if (row >= 0 && col >= 0)
	{
		if (row < MATRIX_LEN && col < MATRIX_LEN)
		{
			return matrix[row][col];
		}
	}
	else if (row < 0 && col < 0)
	{
		if (row >= -MATRIX_LEN && col >= -MATRIX_LEN)
		{
			return matrix[MATRIX_LEN + row][MATRIX_LEN + col];
		}
	}
	cout << "Override!!!" << endl;  //不写return就出现乱码的原因，因为（）没有返回值所以就随便返回了一个地址？
	return ERRORCODE;				//越界就返回一个0吧==（如何错误处理？
}

inline double* matrix4x4::operator()(const int row)
{
	return this->matrix[row];
}

void matrix4x4::Add(double* pDst, double* pSrc)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		pDst[i] += pSrc[i];
	}
}

void matrix4x4::Minus(double* pDst, double* pSrc)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		pDst[i] -= pSrc[i];
	}
}

void matrix4x4::MutiAdd(double* pDst, double* pSrc, double Val)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		pDst[i] += pSrc[i] * Val;
	}
}

void matrix4x4::MutiMinus(double* pDst, double* pSrc, double Val)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		pDst[i] -= pSrc[i] * Val;
	}
}

void matrix4x4::ValMuti(double* pSrc, double Val)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		pSrc[i] *= Val;
	}
}



//转置,不能返回引用的原因是在输出时往往不会拿一个变量去承载它，就会出现类似于野指针的乱码情况
matrix4x4 matrix4x4::Trans()
{
	matrix4x4 temp;
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			temp.matrix[i][j] = this->matrix[j][i];
		}
	}
	return temp;
}

matrix4x4 matrix4x4::Inverse()
{
	matrix4x4 temp(*this);
	//temp = *this;
	matrix4x4 eye;		//外挂的增广矩阵

	for (int i = 0; i < MATRIX_LEN; i++)
	{
		int n = i+1;
		while (temp(i,i)==0&&n!=MATRIX_LEN)
		{

			ExchangeRow(temp(i), temp(n));
			ExchangeRow(eye(i), eye(n));
			++n;
		}
		if (temp(i,i)==0)
		{
			//rule = 0;
			return matrix4x4(0);
		}

		ValMuti(eye(i), 1/temp(i, i));
		ValMuti(temp(i), 1/temp(i, i));

		for (int j = 0; j < MATRIX_LEN; j++)
		{
			if (j != i)
			{
				MutiMinus(eye(j), eye(i), temp(j, i));
				MutiMinus(temp(j), temp(i), temp(j, i));
			}
		}
	}

	return eye;
}

double matrix4x4::Det()
{
	matrix4x4 temp(*this);
	//temp = *this;
	short Exchange = 1;		//用于判断结果是否需要取负
	int col = 0;

	//把每列最大元素通过交换放到对角线上
	for (int i = 0; i < MATRIX_LEN; i++,col++)
	{

		//判断每列最大行
		int MaxRow =col;
		for (int j = i+1; j < MATRIX_LEN; j++)
		{
			if (temp(j,col)>temp(j-1,col))
			{
				MaxRow = j;
			}
		}

		//交换
		ExchangeRow(temp(col), temp(MaxRow));
		Exchange=-Exchange;

		//让下面都变成0
		if (temp(col,col)==0)
		{
			//this->rule = 0;
			return 0.0;
		}
		for (int k =col+1 ; k < MATRIX_LEN; k++)
		{
			MutiMinus(temp(k), temp(col), temp(k, col) / temp(col, col));
		}
	}
	return Exchange*temp(0,0)*temp(1,1)*temp(2,2)*temp(3,3);
}

//重置+-*^
matrix4x4 matrix4x4:: operator+(const matrix4x4& add)
{
	matrix4x4 temp(*this);
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			temp.matrix[i][j] += add.matrix[i][j];
		}
	}
	return temp;
}

matrix4x4 matrix4x4:: operator-(const matrix4x4& sub)
{
	matrix4x4 temp(*this);
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			temp.matrix[i][j] -= sub.matrix[i][j];
		}
	}
	return temp;
}

matrix4x4 matrix4x4:: operator*(const matrix4x4& muti)
{
	matrix4x4 res(0);
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			for (int k = 0; k < MATRIX_LEN; k++)
			{
				res.matrix[i][j] =res.matrix[i][j]+ this->matrix[i][k] * muti.matrix[k][j];
			}
		}
	}
	return res;
}

matrix4x4 matrix4x4::operator=(const matrix4x4& right)
{
	//matrix4x4 temp;  为什么不能通过用一个中间变量承载赋值然后返回他？因为调用的左值的值真的没有被改
	//this->rule = right.rule;
	//return (*this) * right;	这句话也是相同的原因，左值里面的东西没有被修改（赋值）
	memcpy(this->matrix, right.matrix, sizeof(double) * MATRIX_LEN * MATRIX_LEN);
	return *this;
}

matrix4x4 matrix4x4::operator^(const int pow)
{
	matrix4x4 res;

    for (int i = 0; i < abs(pow); i++)
    {
        res = res * (*this);
    }

    if(pow<0)
    {
        res = res.Inverse();
    }

	return res;
}

istream& operator>>(istream& is, matrix4x4& mt)
{
	if (is)		//检查输入流是否成功
	{
		for (int i = 0; i < MATRIX_LEN; i++)
		{
			for (int j = 0; j < MATRIX_LEN; j++)
			{
				is >> mt(i, j);
			}
		}
	}
	else
	{
		cout << "Input error!" << endl;
		mt = matrix4x4();	//发生输入流错误则利用构造函数重置为默认值 P.S.这里为什么又说又未命名对象了orz
		cout << "Matrix is initated with default value !" << endl;
	}
	return is;
}

ostream& operator<<(ostream& os, const matrix4x4 &mt)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			os << mt.matrix[i][j] << "	";
		}
		os << endl;
	}
	return os;
}

//重载面向非对象引用的输出
//ostream& operator<<(ostream& os, matrix4x4 mt)
//{
//	for (int i = 0; i < MATRIX_LEN; i++)
//	{
//		for (int j = 0; j < MATRIX_LEN; j++)
//		{
//			os << mt(i, j) << "	";
//		}
//		os << endl;
//	}
//	return os;
//}
