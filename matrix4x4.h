#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#define MATRIX_LEN 4
#include <iostream>
#include <string>
#include <memory.h>
/*
TODO�� ��ֵ������������ʱ�ż����ȣ�
		��ά�����=����
		���ط��طǳ��������õ�<<����
		^����ʵ�ָ�����
*/

using namespace std;

class matrix4x4
{
public:
	matrix4x4();
	matrix4x4(int Val); //���ڳ˷�
	//template<typename T>
	matrix4x4( double mat[][MATRIX_LEN]);

	matrix4x4 operator+(const matrix4x4& add);
	matrix4x4 operator-(const matrix4x4& sub);
	matrix4x4 operator*(const matrix4x4& muti);			//�Ѳ���
	matrix4x4 operator^(const int pow);					//�Ѳ���
	matrix4x4 operator=(const matrix4x4& right);		//�Ѳ���
	double& operator()(const int  row, const int col);	//�Ѳ���
	
	friend istream& operator>> (istream& is, matrix4x4& mt);	//�Ѳ���
	friend ostream& operator<<(ostream& os,const matrix4x4& mt);		//�Ѳ���
	//friend ostream& operator<<(ostream&, matrix4x4);		

	matrix4x4 Trans();		//�Ѳ���
	matrix4x4 Inverse();	//�Ѳ���
	double Det();			//�Ѳ���

	~matrix4x4();

private:

	double ERRORCODE = 0.0;
	double matrix[MATRIX_LEN][MATRIX_LEN];
	//double rule;	//�������

	//���ڽ��г��ȱ任�ĺ���
	double* operator()(const int row);			//���أ����Է�����
	void Add(double* pDst, double* pSrc);		//������
	void Minus(double* pDst, double* pSrc);		//������
	void ValMuti(double* pSrc, double Val);
	void MutiAdd(double* pDst,double* pSrc , double Val);	//������
	void MutiMinus(double* pDst, double* pSrc, double Val);

	//������
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

//�����������
//istream& operator>> (istream&, matrix4x4&);
//ostream& operator<<(ostream&, matrix4x4&);
//ostream& operator<<(ostream&, matrix4x4);


#endif // MATRIX4X4_H


