#include "matrix.h"
#include <iostream>
#include <cmath>
#include <algorithm>


Matrix::Matrix(int n) {
	this->sizeRows = n;
	this->sizeCols = n;
	for (int i = 0; i < this->sizeCols; i++) {
		std::vector<int> a;
		this->matrixIndexes.push_back(a);
	}
}

Matrix::Matrix(int m, int n) {
	this->sizeRows = m;
	this->sizeCols = n;
	for (int i = 0; i < this->sizeCols; i++) {
		std::vector<int> a;
		this->matrixIndexes.push_back(a);
	}
}

Matrix::~Matrix() {

}
/*
bool Matrix::searchForIndex(int x, int y) {
	int tmpSize = matrixIndexes[x].size();
	for (int i = 0; i < tmpSize; i++) {
		if (matrixIndexes[x][i] == y)
			return true;
	}
	return false;
}
*/
double Matrix::getElemXY(int x, int y) {
	if (matrixValues.find(y * this->sizeCols + x) == matrixValues.end())
		return 0;
	else
		return matrixValues[y * this->sizeCols + x];
}

double Matrix::getNoZeroElemXY(const int x,const int y) {
	return matrixValues[y * this->sizeCols + x];
}

void Matrix::setElemXY(int x, int y, double elem) {
	this->matrixIndexes[x].push_back(y);
	this->matrixValues.insert(std::pair<int, double>(y*this->sizeCols + x, elem));
}

void Matrix::matrixGeneratr(int a1, int a2, int a3) {
	int pomSize = matrixIndexes.size();
	for (int i = 0; i < pomSize; i++) {
		if (i >= 2)
			setElemXY(i - 2, i, (double)a3);
		if (i >= 1)
			setElemXY(i - 1, i, (double)a2);
		setElemXY(i, i, (double)a1);
		if (i < pomSize - 1)
			setElemXY(i + 1, i, (double)a2);
		if (i < pomSize - 2)
			setElemXY(i + 2, i, (double)a3);
	}
}

void Matrix::vectorGenerator(int f) {
	int pomSize = this->sizeRows;
	for (int i = 0; i < pomSize; i++) {
		setElemXY(0, i, sin(i*(f + 1)));
	}
}

void Matrix::printMatrix() {
	int pomSize = matrixIndexes.size();
	for (int i = 0; i < pomSize; i++) {
		for (int j = 0; j < matrixIndexes[i].size(); j++) {
			std::cout << "(" << i << "," << matrixIndexes[i][j] << ") -> " << matrixValues[matrixIndexes[i][j] * this->sizeCols + i] << std::endl;
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
			this->matrixIndexes[x].erase(std::remove(matrixIndexes[x].begin(), matrixIndexes[x].end(), y));
		}
	}
	else
	{
		this->matrixIndexes[x].push_back(y);
		this->matrixValues.insert(std::pair<int, double>(y*this->sizeCols + x, val));
	}
}

Matrix operator+ (Matrix& left, Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeCols);
	for (int x = 0; x < left.sizeCols; x++) {
		for (int j = 0; j < left.matrixIndexes[x].size(); j++) {
			newMatrix.setElemXY(x, left.matrixIndexes[x][j], left.getNoZeroElemXY(x, left.matrixIndexes[x][j]));
		}
	}
	for (int x = 0; x < right.sizeCols; x++) {
		for (int j = 0; j < right.matrixIndexes[x].size(); j++) {
			newMatrix.changeElemXY(x, right.matrixIndexes[x][j], left.getNoZeroElemXY(x, left.matrixIndexes[x][j]));
		}
	}
	return newMatrix;
}

Matrix operator- (Matrix& left, Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeCols);
	for (int x = 0; x < left.sizeCols; x++) {
		for (int j = 0; j < left.matrixIndexes[x].size(); j++) {
			newMatrix.setElemXY(x, left.matrixIndexes[x][j], left.getNoZeroElemXY(x, left.matrixIndexes[x][j]));
		}
	}
	for (int x = 0; x < right.sizeCols; x++) {
		for (int j = 0; j < right.matrixIndexes[x].size(); j++) {
			newMatrix.changeElemXY(x, right.matrixIndexes[x][j], -left.getNoZeroElemXY(x, left.matrixIndexes[x][j]));
		}
	}
	return newMatrix;
}

Matrix operator* (Matrix& left, Matrix& right) {
	Matrix newMatrix = Matrix(left.sizeRows, right.sizeCols);
	for (int x = 0; x < newMatrix.sizeCols; x++) {
		for (int y = 0; y < newMatrix.sizeRows; y++) {
			double singleResult = 0;
			for (int i = 0; i < newMatrix.sizeRows; i++) {
				if(left.getElemXY(i, y) && right.getElemXY(x, i))
					singleResult += left.getElemXY(i, y) * right.getElemXY(x, i);
			}
			newMatrix.setElemXY(x, y, singleResult);
		}
	}
	return newMatrix;
}

Matrix Matrix::matrixD() {
	Matrix newMatrix = Matrix(this->sizeCols);
	for (int i = 0; i < this->sizeCols; i++) {
		newMatrix.setElemXY(i, i, this->getElemXY(i, i));
	}
	return newMatrix;
}

Matrix Matrix::matrixU() {
	Matrix newMatrix = Matrix(this->sizeCols);
	for (int i = 0; i < this->sizeCols; i++) {
		for (int j = 0; j < this->matrixIndexes[i].size(); j++)
			if (matrixIndexes[i][j] < i)
				newMatrix.setElemXY(i, matrixIndexes[i][j], this->getElemXY(i, matrixIndexes[i][j]));
	}
	return newMatrix;
}

Matrix Matrix::matrixL() {
	Matrix newMatrix = Matrix(this->sizeCols);
	for (int i = 0; i < this->sizeCols; i++) {
		for (int j = 0; j < this->matrixIndexes[i].size(); j++)
			if (matrixIndexes[i][j] < i)
				newMatrix.setElemXY(i, matrixIndexes[i][j], this->getElemXY(i, matrixIndexes[i][j]));
	}
	return newMatrix;
}