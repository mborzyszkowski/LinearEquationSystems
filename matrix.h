#ifndef MATRIX_H
#define MATRIX_H

#include "objectManager.h"


class Matrix : public ObjectManager {
	int sizeCols;
	int sizeRows;
public:
	/*NxN*/
	Matrix(int size, bool marked = true);
	/*MxN*/
	Matrix(int rows, int cols, bool marked = true);
	virtual ~Matrix();
	int getSizeCols() const;
	int getSizeRows() const;
	virtual double getElementXY(int x, int y) const;
	virtual void setElementXY(int x, int y, double value);
	virtual void print() const;

	friend Matrix& operator+(const Matrix& left, const Matrix& right);
	friend Matrix& operator-(const Matrix& left, const Matrix& right);
	friend Matrix& operator*(const Matrix& left, const Matrix& right);
	friend Matrix& operator-(const Matrix& matrix);

	virtual Matrix* add(const Matrix& left, const Matrix& right) const;
	virtual Matrix* sub(const Matrix& left, const Matrix& right) const;
	virtual Matrix* mul(const Matrix& left, const Matrix& right) const;
	virtual Matrix* inversion(const Matrix& matrix) const;
};

//namespace normal {
//	class Matrix {
//	public:
//		void matrixGenerator(int a1, int a2, int a3);
//		void vectorBGenerator(int f);
//		void vectorXGenerator();
//		void diagOnesGenerator();
//		void printMatrix();
//		double norm();
//		Matrix matrixD();
//		Matrix matrixU();
//		Matrix matrixL();
//		Matrix reverseD();
//		void doolittle_fLU(Matrix& L, Matrix& U);
//		Matrix forwardSubstitution(Matrix& eqations, Matrix& values);
//		Matrix backSubstitution(Matrix& eqations, Matrix& values);
//	};
//}
#endif // !MATRIX_H


