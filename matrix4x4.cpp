//matrix4x4.cpp
//���⣺Ϊʲô���������������.h��ᱨ��������������.h+.cppģʽ����Ҫ�����ж��嶼��cpp���𣿣�
//���⣺inline ��ʹ��ʱ�������ϣ������ⶨ��ʱ��

#include <iostream>	
#include "matrix4x4.h"

using namespace std;



//����&�����������弰����
inline matrix4x4::matrix4x4()
{
	memset(matrix, 0, sizeof(double) * MATRIX_LEN * MATRIX_LEN);
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		matrix[i][i] = 1;
	}
	rule = MATRIX_LEN;
}
inline matrix4x4::matrix4x4(int Val)
{
	memset(this->matrix, Val, sizeof(double) * MATRIX_LEN * MATRIX_LEN);
}
template<typename T>
inline matrix4x4::matrix4x4(T const mat[][MATRIX_LEN])
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

//���أ���
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
	cout << "Override!!!" << endl;  //��дreturn�ͳ��������ԭ����Ϊ����û�з���ֵ���Ծ���㷵����һ����ַ��
	return ERRORCODE;				//Խ��ͷ���һ��0��==����δ�������
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



//ת��
matrix4x4& matrix4x4::Trans()
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			matrix[i][j] = matrix[j][i];
		}
	}
	return *this;
}

matrix4x4 matrix4x4::Reverse()
{
	matrix4x4 temp;
	temp = *this;

	return matrix4x4();
}

double matrix4x4::Det()
{
	matrix4x4 temp;
	temp = *this;
	return 0.0;
}

//����+-*^
matrix4x4 matrix4x4:: operator+(const matrix4x4& add)
{
	matrix4x4 temp(*this);
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			temp.matrix[i][j] = +add.matrix[i][j];
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
	//matrix4x4 temp;  Ϊʲô����ͨ����һ���м�������ظ�ֵȻ�󷵻�������Ϊ���õ���ֵ��ֵ���û�б���
	this->rule = right.rule;
	//return (*this) * right;	��仰Ҳ����ͬ��ԭ����ֵ����Ķ���û�б��޸ģ���ֵ��
	memcpy(this->matrix, right.matrix, sizeof(double) * MATRIX_LEN * MATRIX_LEN);
	return *this;
}

matrix4x4 matrix4x4::operator^(const int pow)
{
	matrix4x4 res;

	for (int i = 0; i < pow; i++)
	{
		res = res * (*this);
	}
	return res;
}

istream& operator>>(istream& is, matrix4x4& mt)
{
	if (is)		//����������Ƿ�ɹ�
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
		mt = matrix4x4();	//�������������������ù��캯������ΪĬ��ֵ P.S.����Ϊʲô��˵��δ����������orz
		cout << "Matrix is initated with default value !" << endl;
	}
	return is;
}

ostream& operator<<(ostream& os, matrix4x4& mt)
{
	for (int i = 0; i < MATRIX_LEN; i++)
	{
		for (int j = 0; j < MATRIX_LEN; j++)
		{
			os << mt(i, j) << "	";
		}
		os << endl;
	}
	return os;
}