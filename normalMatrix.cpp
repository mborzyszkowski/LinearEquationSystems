#include "normalMatrix.h"
#include <iostream>

NormalMatrix::NormalMatrix(int size, bool marked) : Matrix(size, marked) {
	init();
}

NormalMatrix::NormalMatrix(int rows, int cols, bool marked) : Matrix(rows, cols, marked) {
	init();
}

void NormalMatrix::init() {
	for (int x = 0; x < this->getSizeCols(); x++) {
		std::vector<double> vect;
		values.push_back(vect);
	}

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (int x = 0; x < this->getSizeCols(); x++)
		{
			values[x].push_back(0);
		}
	}
}

NormalMatrix::~NormalMatrix() {
}

double NormalMatrix::getElementXY(int x, int y) const {
	return values[x][y];
}

void NormalMatrix::setElementXY(int x, int y, double value) {
	values[x][y] = value;
}

void NormalMatrix::print() const {

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (int x = 0; x < this->getSizeCols(); x++)
		{
			std::cout << this->values[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix* NormalMatrix::add(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = new NormalMatrix(left.getSizeRows(), left.getSizeCols(), false);

	for (int y = 0; y < newMatrix->getSizeRows(); y++) {
		for (int x = 0; x < newMatrix->getSizeCols(); x++) {
			newMatrix->setElementXY(x, y, left.getElementXY(x, y) + right.getElementXY(x, y));
		}
	}
	return newMatrix;
}

Matrix* NormalMatrix::sub(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = new NormalMatrix(left.getSizeRows(), left.getSizeCols(), false);

	for (int y = 0; y < newMatrix->getSizeRows(); y++) {
		for (int x = 0; x < newMatrix->getSizeCols(); x++) {
			newMatrix->setElementXY(x, y, left.getElementXY(x, y) - right.getElementXY(x, y));
		}
	}
	return newMatrix;
}

Matrix* NormalMatrix::mul(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = new NormalMatrix(left.getSizeRows(), right.getSizeCols(), false);
	double singleResult;

	for (int y = 0; y < newMatrix->getSizeRows(); y++) {
		for (int x = 0; x < newMatrix->getSizeCols(); x++) {
			singleResult = 0;
			for (int i = 0; i < left.getSizeCols(); i++) {
				singleResult += left.getElementXY(i, y) * right.getElementXY(x, i);
			}
			newMatrix->setElementXY(x, y, singleResult);
		}
	}
	return newMatrix;
}

Matrix* NormalMatrix::inversion(const Matrix& matrix) const {
	Matrix* newMatrix = new NormalMatrix(matrix.getSizeRows(), matrix.getSizeCols(), false);
	double pom;

	for (int y = 0; y < matrix.getSizeRows(); y++) {
		for (int x = 0; x < matrix.getSizeCols(); x++) {
			if ((pom = matrix.getElementXY(x, y)) != 0)
				newMatrix->setElementXY(x, y, -pom);
		}
	}
	return newMatrix;
}
