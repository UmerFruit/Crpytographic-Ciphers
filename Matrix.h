/*
 * 		Matrix.h
 *
 *  	Created on: 16-Sep-2023
 *      Author: umerfarooq
 * 		Made for the implementation of Hill Cipher
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Matrix
{
private:
	int rows;
	int columns;
	float **mat;

public:
	// constructors
	Matrix(int = 2, int = 2);
	Matrix(Matrix &);
	~Matrix();
	// operator overloads

	Matrix &operator%(int);
	Matrix &operator*(Matrix &);
	Matrix &operator*(int);
	Matrix &operator/(int);
	Matrix &operator=(Matrix &);
	void Setelement(float, int, int);
	float getElement(int , int );
	Matrix &inverse();
	friend ostream &operator<<(ostream &os, Matrix &right);
};
float Matrix::getElement(int r, int c)
{
	return mat[r][c];
}
Matrix &Matrix::inverse()
{
	if (rows == 2 && columns == 2)
	{
		Matrix adj = *this; // make deep copy
		// first find adjoint
		swap(adj.mat[0][0], adj.mat[1][1]);
		adj.mat[0][1] *= -1;
		adj.mat[1][0] *= -1;
		// then determinant

		int det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
		if (det != 0)
		{
			int i = 1;
			bool lol = true;
			for (; i < 26; i++)
			{
				int result = i * (det)-1;
				if (result % 26 == 0)
				{
					lol = false;
					break;
				}
			}
			if (lol)
			{
				cout << "ERROR! inverse in mod 26 not possible" << endl;
				return *this;
			}
			Matrix *inv = new Matrix((adj)*i);
			*inv = *inv % 26;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					if (inv->mat[i][j] < 0)
					{
						inv->mat[i][j] += 26;
					}
				}
			}
			return *inv;
		}
		else
		{
			cout << "Matrix not invertible" << endl;
		}
	}
	return *this;
}
void Matrix::Setelement(float element, int row, int col)
{
	mat[row][col] = element;
}
Matrix::Matrix(int r, int c)
{
	rows = r;
	columns = c;
	mat = new float *[rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new float[columns]; // allocated the memory
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = 0;
		}
	}
}

Matrix::Matrix(Matrix &m)
{
	rows = m.rows;
	columns = m.columns;
	mat = new float *[rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new float[columns]; // copy constructor
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->mat[i][j] = m.mat[i][j];
		}
	}
}

Matrix &Matrix::operator/(int d)
{
	Matrix *temp = new Matrix(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			temp->mat[i][j] = mat[i][j] / d;
		}
	}
	return *temp;
}
Matrix &Matrix::operator%(int d)
{
	Matrix *temp = new Matrix(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			temp->mat[i][j] = static_cast<int>(mat[i][j]) % d;
		}
	}
	return *temp;
}

Matrix &Matrix::operator*(Matrix &m)
{
	if (columns == m.rows)
	{
		Matrix *temp = new Matrix(this->rows, m.columns);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				temp->mat[i][j] = 0;
				for (int k = 0; k < m.rows; k++) // inner loop to traverse the * of columns with rows
				{
					temp->mat[i][j] += mat[i][k] * m.mat[k][j]; // store in temp and return that obj
				}
			}
		}
		return *temp;
	}
	else
	{
		cout << "Invalid Operation" << endl;
	}
	return *this;
}
Matrix &Matrix::operator*(int n)
{
	Matrix *temp = new Matrix(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++) // multiply each element
		{
			temp->mat[i][j] = this->mat[i][j] * n; // store in temp and return that obj
		}
	}
	return *temp;
}
Matrix &Matrix::operator=(Matrix &m)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] mat[i]; // deep copies elements from the arrays
	}
	delete[] mat;

	rows = m.rows;
	columns = m.columns;
	mat = new float *[rows];
	for (int i = 0; i < rows; i++) // works just like copy constructor
	{
		mat[i] = new float[columns];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->mat[i][j] = m.mat[i][j];
		}
	}
	return *this;
}

ostream &operator<<(ostream &os, Matrix &right)
{
	for (int i = 0; i < right.rows; i++)
	{
		for (int j = 0; j < right.columns; j++)
		{
			os << right.mat[i][j] << " "; // display
		}
		os << endl;
	}
	return os; // operator overloading for cout
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] mat[i];
	}
	delete[] mat;
}
#endif /* MATRIX_H_ */
