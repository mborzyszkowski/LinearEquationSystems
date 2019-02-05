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

	virtual Matrix* add(const Matrix& left, const Matrix& right) const;
	virtual Matrix* sub(const Matrix& left, const Matrix& right) const;
	virtual Matrix* mul(const Matrix& left, const Matrix& right) const;
	virtual Matrix* inversion(const Matrix& matrix) const;
};
//namespace normal {
//	class Matrix {
//	public:
//		/*NxN*/
//		Matrix(int n);
//		/*MxN*/
//		Matrix(int m, int n);
//		~Matrix();
//		void matrixGenerator(int a1, int a2, int a3);
//		void vectorBGenerator(int f);
//		void vectorXGenerator();
//		void diagOnesGenerator();
//		void printMatrix();
//		double getElemXY(int x, int y);
//		double norm();
//		Matrix matrixD();
//		Matrix matrixU();
//		Matrix matrixL();
//		Matrix reverseD();
//		void doolittle_fLU(Matrix& L, Matrix& U);
//		Matrix forwardSubstitution(Matrix& eqations, Matrix& values);
//		Matrix backSubstitution(Matrix& eqations, Matrix& values);
//		friend const Matrix operator+ (const Matrix& left, const Matrix& right);
//		friend const Matrix operator- (const Matrix& left, const Matrix& right);
//		friend const Matrix operator* (const Matrix& left, const Matrix& right);
//		friend const Matrix operator- (const Matrix& matrix);
//	private:
//		int sizeCols;
//		int sizeRows;
//		std::vector<std::vector<double>> values;
//	};
//}
#endif // !NORMALMATRIX_H
