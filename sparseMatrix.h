#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "matrix.h"
#include <unordered_map>


class SparseMatrix : public Matrix {
	std::vector<std::vector<int>> matrixIndexesRows;
	std::vector<std::vector<int>> matrixIndexesCols;
	std::unordered_map<long long, double> matrixValues;
	void init();
	void setEmptyElementXY(int x, int y, double value);
	void addToElementXY(int x, int y, double value);
public:
	SparseMatrix(int size, bool marked = true);
	SparseMatrix(int rows, int cols, bool marked = true);
	virtual ~SparseMatrix();
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

#endif // !SPARSEMATRIX_H
