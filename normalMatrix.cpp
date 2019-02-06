#include "normalMatrix.h"
#include <iostream>
#include <cmath>


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

Matrix* NormalMatrix::matrixD() {
	Matrix* newMatrix = new NormalMatrix(this->getSizeRows(), false);

	for (int i = 0; i < this->getSizeRows(); i++) {
		newMatrix->setElementXY(i, i, this->getElementXY(i, i));
	}
	return newMatrix;
}

Matrix* NormalMatrix::matrixU() {
	Matrix* newMatrix = new NormalMatrix(this->getSizeRows(), false);

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (int x = 0; x < this->getSizeCols(); x++) {
			if (x > y)
				newMatrix->setElementXY(x, y, this->getElementXY(x, y));
		}
	}
	return newMatrix;
}

Matrix* NormalMatrix::matrixL() {
	Matrix* newMatrix = new NormalMatrix(this->getSizeRows(), false);

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (int x = 0; x < this->getSizeCols(); x++) {
			if (x < y)
				newMatrix->setElementXY(x, y, this->getElementXY(x, y));
		}
	}
	return newMatrix;
}

Matrix* NormalMatrix::reverseD() {
	Matrix* newMatrix = new NormalMatrix(this->getSizeRows(), false);
	double pomValue;

	for (int i = 0; i < this->getSizeRows(); i++) {
		pomValue = this->getElementXY(i, i);
		if (pomValue)
			newMatrix->setElementXY(i, i, 1.0 / pomValue);
	}
	return newMatrix;
}

Matrix* NormalMatrix::matrixGenerator(int size, int a1, int a2, int a3) {
	NormalMatrix* newMatrix = new NormalMatrix(size);

	for (int i = 0; i < size; i++) {
		if (i >= 2)
			newMatrix->setElementXY(i - 2, i, (double)a3);
		if (i >= 1)
			newMatrix->setElementXY(i - 1, i, (double)a2);
		newMatrix->setElementXY(i, i, (double)a1);
		if (i < size - 1)
			newMatrix->setElementXY(i + 1, i, (double)a2);
		if (i < size - 2)
			newMatrix->setElementXY(i + 2, i, (double)a3);
	}
	return newMatrix;
}

Matrix* NormalMatrix::vectorBGenerator(int size, int f) {
	NormalMatrix* newMatrix = new NormalMatrix(size, 1);

	for (int i = 0; i < size; i++) {
		newMatrix->setElementXY(0, i, sin((i + 1)*(f + 1)));
	}
	return newMatrix;
}

Matrix* NormalMatrix::vectorXGenerator(int size) {
	NormalMatrix* newMatrix = new NormalMatrix(size, 1);

	for (int i = 0; i < size; i++) {
		newMatrix->setElementXY(0, i, 1.0 / size);
	}
	return newMatrix;
}

Matrix* NormalMatrix::diagOnesGenerator(int size) {
	NormalMatrix* newMatrix = new NormalMatrix(size);

	for (int i = 0; i < size; i++) {
		newMatrix->setElementXY(i, i, 1.0);
	}
	return newMatrix;
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
