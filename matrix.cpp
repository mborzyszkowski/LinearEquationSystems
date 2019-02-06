#include "matrix.h"
#include <iostream>


Matrix::Matrix(int size, bool marked) : ObjectManager(marked) {
	this->sizeRows = size;
	this->sizeCols = size;
}

Matrix::Matrix(int rows, int cols, bool marked) : ObjectManager(marked) {
	this->sizeRows = rows;
	this->sizeCols = cols;
}

Matrix::~Matrix() {
}

int Matrix::getSizeCols() const {
	return this->sizeCols;
}

int Matrix::getSizeRows() const {
	return this->sizeRows;
}

double Matrix::getElementXY(int x, int y) const {
	return 0;
}

void Matrix::setElementXY(int x, int y, double value) {
	return;
}

void Matrix::print() const {
	for (int x = 0; x < this->sizeRows; x++) {
		for (int y = 0; y < this->sizeCols; y++) {
			std::cout << this->getElementXY(x, y) << " ";
		}
		std::cout << std::endl;
	}
}

double Matrix::normalize() {
	double result = 0, pom;

	for (int i = 0; i < this->sizeRows; i++) {
		pom = this->getElementXY(0, i);
		result += pom * pom;
	}
	return sqrt(result);
}

Matrix* Matrix::matrixD() {
	Matrix* newMatrix = new Matrix(this->sizeRows, this->sizeCols, false);

	return newMatrix;
}

Matrix* Matrix::matrixU() {
	Matrix* newMatrix = new Matrix(this->sizeRows, this->sizeCols, false);

	return newMatrix;
}

Matrix* Matrix::matrixL() {
	Matrix* newMatrix = new Matrix(this->sizeRows, this->sizeCols, false);

	return newMatrix;
}

Matrix* Matrix::reverseD() {
	Matrix* newMatrix = new Matrix(this->sizeRows, this->sizeCols, false);

	return newMatrix;
}

void Matrix::doolittle_fLU(Matrix* L, Matrix* U) {
	L = new Matrix(this->getSizeRows);
	U = new Matrix(this->getSizeRows);
}

Matrix* Matrix::forwardSubstitution(Matrix* eqations, Matrix* values) {
	Matrix* newMatrix = new Matrix(values->getSizeRows(), 1);

	return newMatrix;
}

Matrix* Matrix::backSubstitution(Matrix* eqations, Matrix* values) {
	Matrix* newMatrix = new Matrix(values->getSizeRows(), 1);

	return newMatrix;
}

Matrix& operator+(const Matrix& left, const Matrix& right) {
	Matrix* result = left.add(left, right);
	return *result;
}

Matrix* Matrix::add(const Matrix& left, const Matrix& right) const {
	return new Matrix(left.sizeCols, left.sizeRows, false);
}

Matrix& operator-(const Matrix& left, const Matrix& right) {
	Matrix* result = left.sub(left, right);
	return *result;
}

Matrix* Matrix::sub(const Matrix& left, const Matrix& right) const {
	return new Matrix(left.sizeCols, left.sizeRows, false);
}

Matrix& operator*(const Matrix& left, const Matrix& right) {
	Matrix* result = left.mul(left, right);
	return *result;
}

Matrix* Matrix::mul(const Matrix& left, const Matrix& right) const {
	return new Matrix(left.sizeCols, right.sizeRows, false);
}

Matrix& operator-(const Matrix& matrix) {
	Matrix* result = matrix.inversion(matrix);
	return *result;
}

Matrix* Matrix::inversion(const Matrix& matrix) const {
	return new Matrix(matrix.sizeCols, matrix.sizeRows, false);
}
