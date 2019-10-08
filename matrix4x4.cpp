//matrix4x4.cpp
//���⣺Ϊʲô���������������.h��ᱨ������������.h+.cppģʽ����Ҫ�����ж��嶼��cpp���𣿣�
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
	return ERRORCODE;				//Խ��ͷ���һ��0��==����δ�����
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



//ת��,���ܷ������õ�ԭ���������ʱ����������һ������ȥ���������ͻ����������Ұָ����������
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
	matrix4x4 eye;		//��ҵ��������

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
	short Exchange = 1;		//�����жϽ���Ƿ���Ҫȡ��
	int col = 0;

	//��ÿ�����Ԫ��ͨ�������ŵ��Խ�����
	for (int i = 0; i < MATRIX_LEN; i++,col++)
	{

		//�ж�ÿ�������
		int MaxRow =col;
		for (int j = i+1; j < MATRIX_LEN; j++)
		{
			if (temp(j,col)>temp(j-1,col))
			{
				MaxRow = j;
			}
		}

		//����
		ExchangeRow(temp(col), temp(MaxRow));
		Exchange=-Exchange;

		//�����涼���0
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

//����+-*^
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
	//matrix4x4 temp;  Ϊʲô����ͨ����һ���м�������ظ�ֵȻ�󷵻�������Ϊ���õ���ֵ��ֵ���û�б���
	//this->rule = right.rule;
	//return (*this) * right;	��仰Ҳ����ͬ��ԭ����ֵ����Ķ���û�б��޸ģ���ֵ��
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

//��������Ƕ������õ����
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
