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

	static Matrix* matrixGenerator(int size, int a1, int a2, int a3);
	static Matrix* vectorBGenerator(int size, int f);
	static Matrix* vectorXGenerator(int size);
	static Matrix* diagOnesGenerator(int size);

	virtual Matrix* add(const Matrix& left, const Matrix& right) const;
	virtual Matrix* sub(const Matrix& left, const Matrix& right) const;
	virtual Matrix* mul(const Matrix& left, const Matrix& right) const;
	virtual Matrix* inversion(const Matrix& matrix) const;

};
//namespace sparse {
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
//		std::vector<std::vector<int>> matrixIndexes;
//		std::unordered_map<long long, double> matrixValues;
//		double getElemXYconst(int x, int y) const;
//		double getNoZeroElemXY(int x, int y) const;
//		bool getNoEmptyElemXY(int x, int y, double& val);
//		void setElemXY(int x, int y, double val);
//		void changeElemXY(int x, int y, double val);
//	};
//}
#endif // !SPARSEMATRIX_H