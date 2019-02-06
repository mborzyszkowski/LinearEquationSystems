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

	virtual double normalize();
	virtual Matrix* matrixD();
	virtual Matrix* matrixU();
	virtual Matrix* matrixL();
	virtual Matrix* reverseD();
//	virtual void doolittle_fLU(Matrix& L, Matrix& U);
//	virtual Matrix forwardSubstitution(Matrix& eqations, Matrix& values);
//	virtual Matrix backSubstitution(Matrix& eqations, Matrix& values);

	friend Matrix& operator+(const Matrix& left, const Matrix& right);
	friend Matrix& operator-(const Matrix& left, const Matrix& right);
	friend Matrix& operator*(const Matrix& left, const Matrix& right);
	friend Matrix& operator-(const Matrix& matrix);
	virtual Matrix* add(const Matrix& left, const Matrix& right) const;
	virtual Matrix* sub(const Matrix& left, const Matrix& right) const;
	virtual Matrix* mul(const Matrix& left, const Matrix& right) const;
	virtual Matrix* inversion(const Matrix& matrix) const;
};

#endif // !MATRIX_H
