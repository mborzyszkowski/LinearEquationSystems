#include "matrix.h"
#include <cmath>
#include <fstream>

using namespace normal;

Matrix::Matrix(int n) {
	this->sizeRows = n;
	this->sizeCols = n;

	for (int i = 0; i < this->sizeCols; i++) {
		std::vector<double> a;
		this->values.push_back(a);
	}

	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->sizeCols; x++) {
			this->values[x].push_back(0);
		}
	}
}

Matrix::Matrix(int m, int n) {
	this->sizeRows = m;
	this->sizeCols = n;

	for (int i = 0; i < this->sizeCols; i++) {
		std::vector<double> a;
		this->values.push_back(a);
	}

	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->sizeCols; x++) {
			this->values[x].push_back(0);
		}
	}
}

Matrix::~Matrix() {

}


void Matrix::matrixGenerator(int a1, int a2, int a3) {

	for (int i = 0; i < sizeRows; i++) {
		if (i >= 2)
			this->values[i-2][i] = (double)a3;
		if (i >= 1)
			this->values[i - 1][i] = (double)a2;
		this->values[i][i] = (double)a1;
		if (i < sizeRows - 1)
			this->values[i+1][i] = (double)a2;
		if (i < sizeRows - 2)
			this->values[i+2][i] = (double)a3;
	}
}

void Matrix::vectorBGenerator(int f) {

	for (int i = 0; i < this->sizeRows; i++) {
		this->values[0][i] = sin((i + 1)*(f + 1));
	}
}

void Matrix::vectorXGenerator() {

	for (int i = 0; i < this->sizeRows; i++) {
		this->values[0][i] = 1.0 / this->sizeRows;
	}
}

void Matrix::diagOnesGenerator() {

	for (int i = 0; i < this->sizeCols; i++) {
		this->values[i][i] = 1.0;
	}
}

void Matrix::printMatrix() {
	std::ofstream txt;
	txt.open("vals.txt");

	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->sizeCols; x++) {
			txt << this->values[x][y] << " ";
		}
		txt << std::endl;
	}
	txt.close();
}

double Matrix::getElemXY(int x, int y) {
	return this->values[x][y];
}

double Matrix::norm() {
	double result = 0, pom;

	for (int i = 0; i < this->sizeRows; i++) {
		pom = this->values[0][i];
		result += pom * pom;
	}
	return sqrt(result);

}

Matrix Matrix::matrixD() {
	Matrix newMatrix = Matrix(this->sizeRows);

	for (int i = 0; i < this->sizeRows; i++) {
		newMatrix.values[i][i] = this->values[i][i];
	}
	return newMatrix;

}

Matrix Matrix::matrixU() {
	Matrix newMatrix = Matrix(this->sizeRows);

	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->sizeCols; x++)
			if (x > y)
				newMatrix.values[x][y] = this->values[x][y];
	}
	return newMatrix;
}

Matrix Matrix::matrixL() {
	Matrix newMatrix = Matrix(this->sizeRows);
	
	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->sizeCols; x++)
			if (x < y)
				newMatrix.values[x][y] = this->values[x][y];
	}
	return newMatrix;
}

Matrix Matrix::reverseD() {
	Matrix newMatrix = Matrix(this->sizeCols);
	double pomElem;

	for (int i = 0; i < this->sizeCols; i++) {
		pomElem = this->getElemXY(i, i);
		if (pomElem)
			newMatrix.values[i][i] = 1.0 / pomElem;
	}
	return newMatrix;
}

const Matrix normal::operator+ (const Matrix& left, const Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeRows, left.sizeCols);

	for (int y = 0; y < newMatrix.sizeRows; y++) {
		for (int x = 0; x < newMatrix.sizeCols; x++) {
			newMatrix.values[x][y] += left.values[x][y];
			newMatrix.values[x][y] += right.values[x][y];
		}
	}
	return newMatrix;
}

const Matrix normal::operator- (const Matrix& left, const Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeRows, left.sizeCols);

	for (int y = 0; y < newMatrix.sizeRows; y++) {
		for (int x = 0; x < newMatrix.sizeCols; x++) {
			newMatrix.values[x][y] += left.values[x][y];
			newMatrix.values[x][y] -= right.values[x][y];
		}
	}
	return newMatrix;
}

const Matrix normal::operator* (const Matrix& left, const Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeRows, right.sizeCols);
	double singleResult;

	for (int x = 0; x < newMatrix.sizeCols; x++) {
		for (int y = 0; y < newMatrix.sizeRows; y++) {
			singleResult = 0;
			for (int i = 0; i < left.sizeCols; i++) {
				singleResult += left.values[i][y] * right.values[x][i];
			}
			newMatrix.values[x][y] = singleResult;
		}
	}
	return newMatrix;
}

const Matrix normal::operator- (const Matrix& matrix) {
	Matrix newMatrix = Matrix(matrix.sizeRows, matrix.sizeCols);

	for (int y = 0; y < matrix.sizeRows; y++) {
		for (int x = 0; x < matrix.sizeCols; x++) {
			newMatrix.values[x][y] = -matrix.values[x][y];
		}
	}
	return newMatrix;
}

void Matrix::doolittle_fLU(Matrix& L, Matrix& U) {
	double newElem;

	L.diagOnesGenerator();
	for (int i = 0; i < this->sizeRows; i++) {
		for (int j = i; j < this->sizeCols; j++) {
			newElem = 0;
			for (int k = 0; k < i; k++) {
				if (j != k)	
					newElem += L.values[k][i] * U.values[j][k];
			}
			U.values[j][i] = this->values[j][i] - newElem;
		}
		for (int j = i + 1; j < this->sizeCols; j++) {
			newElem = 0;
			for (int k = 0; k < i; k++) {
				if (k != j)
					newElem += L.values[k][j] * U.values[i][k];
			}
			L.values[i][j] = (this->values[i][j] - newElem) / U.values[i][i];
		}
	}
}

Matrix Matrix::forwardSubstitution(Matrix& eqations, Matrix& values) {
	Matrix newMatrix = Matrix(values.sizeRows, 1);
	double pomResult;

	for (int y = 0; y < newMatrix.sizeRows; y++) {
		pomResult = 0;
		for (int x = 0; x < y; x++) {
			pomResult += eqations.values[x][y] * newMatrix.values[0][x];
		}
		newMatrix.values[0][y] = (values.values[0][y] - pomResult) / eqations.values[y][y];
	}
	return newMatrix;
}

Matrix Matrix::backSubstitution(Matrix& eqations, Matrix& values) {
	Matrix newMatrix = Matrix(values.sizeRows, 1);
	double pomResult;

	for (int y = newMatrix.sizeRows - 1; y >= 0; y--) {
		pomResult = 0;
		for (int x = newMatrix.sizeRows - 1; x > y; x--) {
			pomResult += eqations.values[x][y] * newMatrix.values[0][x];
		}
		newMatrix.values[0][y] = (values.values[0][y] - pomResult) / eqations.values[y][y];
	}
	return newMatrix;
}
