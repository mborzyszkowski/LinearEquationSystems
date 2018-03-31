#include "matrix.h"
#include <iostream>
#include <cmath>
#include <algorithm>


Matrix::Matrix(int n) {
	this->sizeRows = n;
	this->sizeCols = n;
	for (int i = 0; i < this->sizeRows; i++) {
		std::vector<int> a;
		this->matrixIndexes.push_back(a);
	}
}

Matrix::Matrix(int m, int n) {
	this->sizeRows = m;
	this->sizeCols = n;
	for (int i = 0; i < this->sizeRows; i++) {
		std::vector<int> a;
		this->matrixIndexes.push_back(a);
	}
}

Matrix::~Matrix() {

}

double Matrix::getElemXY(int x, int y) {
	if (matrixValues.find(y * this->sizeCols + x) == matrixValues.end())
		return 0;
	else
		return matrixValues[y * this->sizeCols + x];
}

double Matrix::getNoZeroElemXY(int x, int y) {
	return matrixValues[y * this->sizeCols + x];
}

void Matrix::setElemXY(int x, int y, double elem) {
	this->matrixIndexes[y].push_back(x);
	this->matrixValues.insert(std::pair<int, double>(y*this->sizeCols + x, elem));
}

void Matrix::matrixGeneratr(int a1, int a2, int a3) {
	for (int i = 0; i < sizeRows; i++) {
		if (i >= 2)
			setElemXY(i - 2, i, (double)a3);
		if (i >= 1)
			setElemXY(i - 1, i, (double)a2);
		setElemXY(i, i, (double)a1);
		if (i < sizeRows - 1)
			setElemXY(i + 1, i, (double)a2);
		if (i < sizeRows - 2)
			setElemXY(i + 2, i, (double)a3);
	}
}

void Matrix::vectorGenerator(int f) {
	for (int i = 0; i < this->sizeRows; i++) {
		setElemXY(0, i, sin(i*(f + 1)));
	}
}

void Matrix::printMatrix() {
	for (int y = 0; y < sizeRows; y++) {
		for (int x = 0; x < matrixIndexes[y].size(); x++) {
			std::cout << "(" << y << "," << matrixIndexes[y][x] << ") -> " << matrixValues[y * this->sizeCols + matrixIndexes[y][x]] << std::endl;
		}
	}
}

void Matrix::changeElemXY(int x, int y, double val) { // var zerowania
	double pom = this->getElemXY(x, y);
	if (pom) {
		pom += val;
		if (pom)
			this->matrixValues[y*this->sizeCols + x] += val;
		else {		//usuniecie indexu w tab poniewaz wartosc jest zero
			this->matrixValues.erase(y*this->sizeCols + x);
			this->matrixIndexes[y].erase(std::remove(matrixIndexes[y].begin(), matrixIndexes[y].end(), x));
		}
	}
	else
	{
		this->matrixIndexes[y].push_back(x);
		this->matrixValues.insert(std::pair<int, double>(y*this->sizeCols + x, val));
	}
}

Matrix operator+ (Matrix& left, Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeRows);
	for (int y = 0; y < left.sizeRows; y++) {
		for (int x = 0; x < left.matrixIndexes[y].size(); x++) {
			newMatrix.setElemXY(left.matrixIndexes[y][x], y, left.getNoZeroElemXY(left.matrixIndexes[y][x], y));
		}
	}
	for (int y = 0; y < right.sizeRows; y++) {
		for (int x = 0; x < right.matrixIndexes[y].size(); x++) {
			newMatrix.changeElemXY(left.matrixIndexes[y][x], y, left.getNoZeroElemXY(left.matrixIndexes[y][x], y));
		}
	}
	return newMatrix;
}

Matrix operator- (Matrix& left, Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeCols);
	for (int y = 0; y < left.sizeRows; y++) {
		for (int x = 0; x < left.matrixIndexes[y].size(); x++) {
			newMatrix.setElemXY(left.matrixIndexes[y][x], y, left.getNoZeroElemXY(left.matrixIndexes[y][x], y));
		}
	}
	for (int y = 0; y < right.sizeRows; y++) {
		for (int x = 0; x < right.matrixIndexes[y].size(); x++) {
			newMatrix.changeElemXY(left.matrixIndexes[y][x], y, -left.getNoZeroElemXY(left.matrixIndexes[y][x], y));
		}
	}
	return newMatrix;
}

Matrix operator* (Matrix& left, Matrix& right) {	// zmienic
	Matrix newMatrix = Matrix(left.sizeRows, right.sizeCols);
	for (int x = 0; x < newMatrix.sizeCols; x++) {
		for (int y = 0; y < newMatrix.sizeRows; y++) {
			double singleResult = 0;
			for (int i = 0; i < left.matrixIndexes[y].size(); i++) {
				int pomIndex = left.matrixIndexes[y][i];
				//if(left.getElemXY(pomIndex, y) && right.getElemXY(x, pomIndex))
				singleResult += left.getElemXY(pomIndex, y) * right.getElemXY(x, pomIndex);
			}
			newMatrix.setElemXY(x, y, singleResult);
		}
	}
	return newMatrix;
}

Matrix Matrix::matrixD() {
	Matrix newMatrix = Matrix(this->sizeRows);
	for (int i = 0; i < this->sizeRows; i++) {
		newMatrix.setElemXY(i, i, this->getElemXY(i, i));
	}
	return newMatrix;
}

Matrix Matrix::matrixU() {
	Matrix newMatrix = Matrix(this->sizeRows);
	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->matrixIndexes[y].size(); x++)
			if (matrixIndexes[y][x] > y)
				newMatrix.setElemXY(matrixIndexes[y][x], y, this->getElemXY(matrixIndexes[y][x], y));
	}
	return newMatrix;
}

Matrix Matrix::matrixL() {
	Matrix newMatrix = Matrix(this->sizeRows);
	for (int y = 0; y < this->sizeRows; y++) {
		for (int x = 0; x < this->matrixIndexes[y].size(); x++)
			if (matrixIndexes[y][x] < y)
				newMatrix.setElemXY(matrixIndexes[y][x], y, this->getElemXY(matrixIndexes[y][x], y));
	}
	return newMatrix;
}