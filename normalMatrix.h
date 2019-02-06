#ifndef NORMALMATRIX_H
#define NORMALMATRIX_H

#include "matrix.h"


class NormalMatrix : public Matrix {
	std::vector<std::vector<double>> values;
	void init();
public:
	NormalMatrix(int size, bool marked = true);
	NormalMatrix(int rows, int cols, bool marked = true);
	virtual ~NormalMatrix();
	virtual double getElementXY(int x, int y) const;
	virtual void setElementXY(int x, int y, double value);
	virtual void print() const;

	virtual Matrix* matrixD();
	virtual Matrix* matrixU();
	virtual Matrix* matrixL();
	virtual Matrix* reverseD();
	virtual void doolittle_fLU(Matrix* L, Matrix* U);
	virtual Matrix* forwardSubstitution(Matrix* eqations, Matrix* values);
	virtual Matrix* backSubstitution(Matrix* eqations, Matrix* values);

	static Matrix* matrixGenerator(int size, int a1, int a2, int a3);
	static Matrix* vectorBGenerator(int size, int f);
	static Matrix* vectorXGenerator(int size);
	static Matrix* diagOnesGenerator(int size);

	virtual Matrix* add(const Matrix& left, const Matrix& right) const;
	virtual Matrix* sub(const Matrix& left, const Matrix& right) const;
	virtual Matrix* mul(const Matrix& left, const Matrix& right) const;
	virtual Matrix* inversion(const Matrix& matrix) const;
};

#endif // !NORMALMATRIX_H
