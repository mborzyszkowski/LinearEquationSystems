#include "sparseMatrix.h"
#include <iostream>
#include <algorithm>


SparseMatrix::SparseMatrix(int size, bool marked) : Matrix(size, marked) {
	init();
}

SparseMatrix::SparseMatrix(int rows, int cols, bool marked) : Matrix(rows, cols, marked) {
	init();
}

void SparseMatrix::init() {

	// y -> x row search
	for (int i = 0; i < this->getSizeRows(); i++) {
		std::vector<int> a;
		this->matrixIndexesRows.push_back(a);
	}

	//x -> y col search
	for (int i = 0; i < this->getSizeCols(); i++) {
		std::vector<int> a;
		this->matrixIndexesCols.push_back(a);
	}
}

SparseMatrix::~SparseMatrix() {
}

double SparseMatrix::getElementXY(int x, int y) const {

	for (size_t i = 0; i < matrixIndexesRows[y].size(); i++) {
		if (matrixIndexesRows[y][i] == x)
			return matrixValues.at(y * this->getSizeCols() + x);
	}
	return 0;
}

void SparseMatrix::setElementXY(int x, int y, double value) {

	if (this->getElementXY(x, y)) {
		if (value) {
			this->matrixValues[y*this->getSizeCols() + x] = value;
		}
		else {
			this->matrixValues.erase(y*this->getSizeCols() + x);
			this->matrixIndexesRows[y].erase(std::remove(this->matrixIndexesRows[y].begin(), this->matrixIndexesRows[y].end(), x));
			this->matrixIndexesCols[x].erase(std::remove(this->matrixIndexesCols[x].begin(), this->matrixIndexesCols[x].end(), y));
		}
	}
	else if (value) {
		this->setEmptyElementXY(x, y, value);
	}
}

void SparseMatrix::setEmptyElementXY(int x, int y, double value) {

	if (value != 0) {
		this->matrixIndexesRows[y].push_back(x);
		this->matrixIndexesCols[x].push_back(y);
		this->matrixValues.insert(std::pair<int, double>(y*this->getSizeCols() + x, value));
	}
}

void SparseMatrix::addToElementXY(int x, int y, double value) {
	double pom;

	if (pom = this->getElementXY(x, y)) {
		pom += value;
		if (pom)
			this->matrixValues[y*this->getSizeCols() + x] = pom;
		else {
			this->matrixValues.erase(y*this->getSizeCols() + x);
			this->matrixIndexesRows[y].erase(std::remove(this->matrixIndexesRows[y].begin(), this->matrixIndexesRows[y].end(), x));
			this->matrixIndexesCols[x].erase(std::remove(this->matrixIndexesCols[x].begin(), this->matrixIndexesCols[x].end(), y));
		}
	}
	else if (value) {
		this->setEmptyElementXY(x, y, value);
	}
}

void SparseMatrix::print() const {

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (int x = 0; x < (int)matrixIndexesRows[y].size(); x++) {
			std::cout << "(" << matrixIndexesRows[y][x] << "," << y << ") -> " << matrixValues.at(y * this->getSizeCols() + matrixIndexesRows[y][x]) << std::endl;
		}
	}
}

Matrix* SparseMatrix::add(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = NULL;

	if (typeid(left) != typeid(right)) {
		newMatrix = right.add(left, right); //static virtual add as normalMatrix?? rzutowanie na normal??
	}
	else {
		SparseMatrix* newMatrixS = new SparseMatrix(left.getSizeRows(), left.getSizeCols(), false);
		SparseMatrix* leftP = (SparseMatrix*)&left;
		SparseMatrix* rightP = (SparseMatrix*)&right;

		for (int y = 0; y < leftP->getSizeRows(); y++) {
			for (int x = 0; x < (int)leftP->matrixIndexesRows[y].size(); x++) {
				newMatrixS->setEmptyElementXY(leftP->matrixIndexesRows[y][x], y,
					leftP->getElementXY(leftP->matrixIndexesRows[y][x], y));
			}
		}
		for (int y = 0; y < rightP->getSizeRows(); y++) {
			for (int x = 0; x < (int)rightP->matrixIndexesRows[y].size(); x++) {
				newMatrixS->addToElementXY(rightP->matrixIndexesRows[y][x], y,
					rightP->getElementXY(rightP->matrixIndexesRows[y][x], y));
			}
		}
		newMatrix = newMatrixS;
	}
	return newMatrix;
}

Matrix* SparseMatrix::sub(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = NULL;

	if (typeid(left) != typeid(right)) {
		newMatrix = right.sub(left, right); //static virtual add as normalMatrix??
	}
	else {
		SparseMatrix* newMatrixS = new SparseMatrix(left.getSizeRows(), left.getSizeCols(), false);
		SparseMatrix* leftP = (SparseMatrix*)&left;
		SparseMatrix* rightP = (SparseMatrix*)&right;

		for (int y = 0; y < leftP->getSizeRows(); y++) {
			for (int x = 0; x < (int)leftP->matrixIndexesRows[y].size(); x++) {
				newMatrixS->setEmptyElementXY(leftP->matrixIndexesRows[y][x], y,
					leftP->getElementXY(leftP->matrixIndexesRows[y][x], y));
			}
		}
		for (int y = 0; y < rightP->getSizeRows(); y++) {
			for (int x = 0; x < (int)rightP->matrixIndexesRows[y].size(); x++) {
				newMatrixS->addToElementXY(rightP->matrixIndexesRows[y][x], y,
					-(rightP->getElementXY(rightP->matrixIndexesRows[y][x], y)));
			}
		}
		newMatrix = newMatrixS;
	}
	return newMatrix;
}

Matrix* SparseMatrix::mul(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = NULL;

	if (typeid(left) != typeid(right)) {
		newMatrix = right.mul(left, right); //static virtual add as normalMatrix??
	}
	else {
		SparseMatrix* newMatrixS = new SparseMatrix(left.getSizeRows(), right.getSizeCols(), false);
		SparseMatrix* leftP = (SparseMatrix*)&left;
		SparseMatrix* rightP = (SparseMatrix*)&right;

		for (int rows = 0; rows < leftP->getSizeRows(); rows++)
		{
			for (int cols = 0; cols < rightP->getSizeCols(); cols++)
			{ 
				long long rowsIdx = 0, maxRows = leftP->matrixIndexesRows[rows].size();
				long long colsIdx = 0, maxCols = rightP->matrixIndexesCols[cols].size();
				int pomRows, pomCols;
				double cellResult = 0;

				while (rowsIdx < maxRows && colsIdx < maxCols) {
					pomRows = leftP->matrixIndexesRows[rows][rowsIdx], pomCols = rightP->matrixIndexesCols[cols][colsIdx];

					if (pomRows == pomCols) { //zlozenie rows ->y, pomRows->x * cols->x, pomCols->y (y * this->getSizeCols() + x)
						cellResult += 
							leftP->matrixValues[rows * leftP->getSizeCols() + pomRows] 
							* rightP->matrixValues[pomCols * rightP->getSizeCols() + cols];
						colsIdx++, rowsIdx++;
					}
					else if (pomRows > pomCols) {
						colsIdx++;
					}
					else {
						rowsIdx++;
					}
				}

				newMatrixS->setEmptyElementXY(cols, rows, cellResult);
			}
		}
		newMatrix = newMatrixS;
	}
	return newMatrix;
}

Matrix* SparseMatrix::inversion(const Matrix& matrix) const {
	SparseMatrix* newMatrix = new SparseMatrix(matrix.getSizeRows(), matrix.getSizeCols(), false);
	SparseMatrix* matrixP = (SparseMatrix*)&matrix;
	int pomX = 0;

	for (int y = 0; y < matrixP->getSizeRows(); y++) {
		for (size_t x = 0; x < matrixP->matrixIndexesRows[y].size(); x++) {
			pomX = matrixP->matrixIndexesRows[y][x];
			newMatrix->setEmptyElementXY(pomX, y, -matrixP->getElementXY(pomX, y));
		}
	}
	return newMatrix;
}

//#include "sparseMatrix.h"
//#include <iostream>
//#include <cmath>
//#include <algorithm>
//#include <fstream>
//
//using namespace sparse;
//
//Matrix::Matrix(int n) {
//	this->sizeRows = n;
//	this->sizeCols = n;
//
//	for (int i = 0; i < this->sizeRows; i++) {
//		std::vector<int> a;
//		this->matrixIndexes.push_back(a);
//	}
//}
//
//Matrix::Matrix(int m, int n) {
//	this->sizeRows = m;
//	this->sizeCols = n;
//
//	for (int i = 0; i < this->sizeRows; i++) {
//		std::vector<int> a;
//		this->matrixIndexes.push_back(a);
//	}
//}
//
//Matrix::~Matrix() {
//
//}
//
//bool Matrix::getNoEmptyElemXY(int x, int y, double& val) {
//	if (matrixValues.find(y * this->sizeCols + x) == matrixValues.end()) {
//		val = 0;
//		return 0;
//	}
//	else {
//		val = matrixValues[y * this->sizeCols + x];
//		return 1;
//	}
//}
//
//double Matrix::getElemXY(int x, int y) {
//
//	if (matrixValues.find(y * this->sizeCols + x) == matrixValues.end())
//		return 0;
//	else
//		return matrixValues[y * this->sizeCols + x];
//}
//
//double Matrix::getNoZeroElemXY(int x, int y) const {
//	return matrixValues.at(y * this->sizeCols + x);
//}
//
//double Matrix::getElemXYconst(int x, int y) const {
//
//	for (int i = 0; i < matrixIndexes[y].size(); i++) {
//		if (matrixIndexes[y][i] == x)
//			return matrixValues.at(y * this->sizeCols + x);
//	}
//	return 0;
//}
//
//void Matrix::setElemXY(int x, int y, double elem) {
//
//	this->matrixIndexes[y].push_back(x);
//	this->matrixValues.insert(std::pair<int, double>(y*this->sizeCols + x, elem));
//}
//
//void Matrix::matrixGenerator(int a1, int a2, int a3) {
//
//	for (int i = 0; i < sizeRows; i++) {
//		if (i >= 2)
//			setElemXY(i - 2, i, (double)a3);
//		if (i >= 1)
//			setElemXY(i - 1, i, (double)a2);
//		setElemXY(i, i, (double)a1);
//		if (i < sizeRows - 1)
//			setElemXY(i + 1, i, (double)a2);
//		if (i < sizeRows - 2)
//			setElemXY(i + 2, i, (double)a3);
//	}
//}
//
//void Matrix::vectorBGenerator(int f) {
//
//	for (int i = 0; i < this->sizeRows; i++) {
//		setElemXY(0, i, sin((i + 1)*(f + 1)));
//	}
//}
//
//void Matrix::vectorXGenerator() {
//
//	for (int i = 0; i < this->sizeRows; i++) {
//		setElemXY(0, i, 1.0 / this->sizeRows);
//	}
//}
//
//void Matrix::diagOnesGenerator() {
//	for (int i = 0; i < this->sizeCols; i++) {
//		this->setElemXY(i, i, 1);
//	}
//}
//
//void Matrix::printMatrix() {
//	std::ofstream txt;
//	txt.open("vals.txt");
//
//	for (int y = 0; y < sizeRows; y++) {
//		for (int x = 0; x < (int)matrixIndexes[y].size(); x++) {
//			txt << "(" << y << "," << matrixIndexes[y][x] << ") -> " << matrixValues[y * this->sizeCols + matrixIndexes[y][x]] << std::endl;
//		}
//	}
//	txt.close();
//}
//
//void Matrix::changeElemXY(int x, int y, double val) {
//	double pom;
//
//	if (getNoEmptyElemXY(x, y, pom)) {
//		pom += val;
//		if (pom)
//			this->matrixValues[y*this->sizeCols + x] += val;
//		else {
//			this->matrixValues.erase(y*this->sizeCols + x);
//			this->matrixIndexes[y].erase(std::remove(matrixIndexes[y].begin(), matrixIndexes[y].end(), x));
//		}
//	}
//	else
//	{
//		this->matrixIndexes[y].push_back(x);
//		this->matrixValues.insert(std::pair<int, double>(y*this->sizeCols + x, val));
//	}
//}
//
//const Matrix sparse::operator+ (const Matrix& left, const Matrix& right) {
//	Matrix newMatrix = Matrix(left.sizeRows, left.sizeCols);
//
//	for (int y = 0; y < left.sizeRows; y++) {
//		for (int x = 0; x < (int)left.matrixIndexes[y].size(); x++) {
//			newMatrix.setElemXY(left.matrixIndexes[y][x], y, left.getNoZeroElemXY(left.matrixIndexes[y][x], y));
//		}
//	}
//	for (int y = 0; y < right.sizeRows; y++) {
//		for (int x = 0; x < (int)right.matrixIndexes[y].size(); x++) {
//			newMatrix.changeElemXY(right.matrixIndexes[y][x], y, right.getNoZeroElemXY(right.matrixIndexes[y][x], y));
//		}
//	}
//	return newMatrix;
//}
//
//const Matrix sparse::operator- (const Matrix& left, const Matrix& right) {
//	Matrix newMatrix = Matrix(left.sizeRows, left.sizeCols);
//
//	for (int y = 0; y < left.sizeRows; y++) {
//		for (int x = 0; x < (int)left.matrixIndexes[y].size(); x++) {
//			newMatrix.setElemXY(left.matrixIndexes[y][x], y, left.getNoZeroElemXY(left.matrixIndexes[y][x], y));
//		}
//	}
//	for (int y = 0; y < right.sizeRows; y++) {
//		for (int x = 0; x < (int)right.matrixIndexes[y].size(); x++) {
//			newMatrix.changeElemXY(right.matrixIndexes[y][x], y, -right.getNoZeroElemXY(right.matrixIndexes[y][x], y));
//		}
//	}
//	return newMatrix;
//}
//
//const Matrix sparse::operator* (const Matrix& left, const Matrix& right) {
//	Matrix newMatrix = Matrix(left.sizeRows, right.sizeCols);
//	double singleResult;
//	int pomIndex;
//
//	if (newMatrix.sizeCols == 1)
//		for (int x = 0; x < newMatrix.sizeCols; x++) {
//			for (int y = 0; y < newMatrix.sizeRows; y++) {
//				singleResult = 0;
//				for (int i = 0; i < (int)left.matrixIndexes[y].size(); i++) {
//					pomIndex = left.matrixIndexes[y][i];
//					singleResult += left.getNoZeroElemXY(pomIndex, y) * right.getNoZeroElemXY(x, pomIndex);
//				}
//				newMatrix.setElemXY(x, y, singleResult);
//			}
//		}
//	else {
//		for (int x = 0; x < newMatrix.sizeCols; x++) {
//			for (int y = 0; y < newMatrix.sizeRows; y++) {
//				double singleResult = 0;
//				for (int i = 0; i < (int)left.matrixIndexes[y].size(); i++) {
//					int pomIndex = left.matrixIndexes[y][i];
//					singleResult += left.getNoZeroElemXY(pomIndex, y) * right.getElemXYconst(x, pomIndex);
//				}
//				newMatrix.setElemXY(x, y, singleResult);
//			}
//		}
//	}
//
//
//	return newMatrix;
//}
//
//const Matrix sparse::operator- (const Matrix& matrix) {
//	Matrix newMatrix = Matrix(matrix.sizeRows, matrix.sizeCols);
//	int pomX;
//
//	for (int y = 0; y < matrix.sizeRows; y++) {
//		for (int x = 0; x < matrix.matrixIndexes[y].size(); x++) {
//			pomX = matrix.matrixIndexes[y][x];
//			newMatrix.setElemXY(pomX, y, -matrix.getNoZeroElemXY(pomX, y));
//		}
//	}
//	return newMatrix;
//}
//
//Matrix Matrix::matrixD() {
//	Matrix newMatrix = Matrix(this->sizeRows);
//
//	for (int i = 0; i < this->sizeRows; i++) {
//		newMatrix.setElemXY(i, i, this->getElemXY(i, i));
//	}
//	return newMatrix;
//}
//
//Matrix Matrix::matrixU() {
//	Matrix newMatrix = Matrix(this->sizeRows);
//
//	for (int y = 0; y < this->sizeRows; y++) {
//		for (int x = 0; x < (int)this->matrixIndexes[y].size(); x++)
//			if (matrixIndexes[y][x] > y)
//				newMatrix.setElemXY(matrixIndexes[y][x], y, this->getElemXY(matrixIndexes[y][x], y));
//	}
//	return newMatrix;
//}
//
//Matrix Matrix::matrixL() {
//	Matrix newMatrix = Matrix(this->sizeRows);
//	for (int y = 0; y < this->sizeRows; y++) {
//		for (int x = 0; x < (int)this->matrixIndexes[y].size(); x++)
//			if (matrixIndexes[y][x] < y)
//				newMatrix.setElemXY(matrixIndexes[y][x], y, this->getElemXY(matrixIndexes[y][x], y));
//	}
//	return newMatrix;
//}
//
//Matrix Matrix::reverseD() {
//	Matrix newMatrix = Matrix(this->sizeCols);
//	double pomElem;
//
//	for (int i = 0; i < this->sizeCols; i++) {
//		pomElem = this->getElemXY(i, i);
//		if (pomElem)
//			newMatrix.setElemXY(i, i, 1.0 / pomElem);
//	}
//	return newMatrix;
//}
//
//double Matrix::norm() {
//	double result = 0, pom;
//
//	for (int i = 0; i < this->sizeRows; i++) {
//		pom = getElemXY(0, i);
//		result += pom * pom;
//	}
//	return sqrt(result);
//}
//
//Matrix Matrix::forwardSubstitution(Matrix& eqations, Matrix& values) {
//	Matrix newMatrix = Matrix(values.sizeRows, 1);
//	double pomResult;
//	int pomIndex;
//
//	for (int y = 0; y < newMatrix.sizeRows; y++) {
//		pomResult = 0;
//		for (int j = 0; j < eqations.matrixIndexes[y].size(); j++) {
//			pomIndex = eqations.matrixIndexes[y][j];
//			if (pomIndex != y)
//				pomResult += eqations.getNoZeroElemXY(pomIndex, y) * newMatrix.getElemXY(0, pomIndex);
//		}
//		newMatrix.setElemXY(0, y, (values.getElemXY(0, y) - pomResult) / eqations.getNoZeroElemXY(y, y));
//	}
//	return newMatrix;
//}
//
//Matrix Matrix::backSubstitution(Matrix& eqations, Matrix& values) {
//	Matrix newMatrix = Matrix(values.sizeRows, 1);
//	double pomResult;
//	int pomIndex;
//
//	for (int y = newMatrix.sizeRows - 1; y >= 0; y--) {
//		pomResult = 0;
//		for (int j = 0; j < eqations.matrixIndexes[y].size(); j++) {
//			pomIndex = eqations.matrixIndexes[y][j];
//			if (pomIndex != y)
//				pomResult += eqations.getNoZeroElemXY(pomIndex, y) * newMatrix.getElemXY(0, pomIndex);
//		}
//		newMatrix.setElemXY(0, y, (values.getElemXY(0, y) - pomResult) / eqations.getNoZeroElemXY(y, y));
//	}
//	return newMatrix;
//}
//
//void Matrix::doolittle_fLU(Matrix& L, Matrix& U) {
//	double newElem;
//	int pomIndex;
//
//	L.diagOnesGenerator();
//	for (int i = 0; i < this->sizeRows; i++) {
//		for (int j = i; j < this->sizeCols; j++) {
//			newElem = 0;
//			for (int k = 0; k < L.matrixIndexes[i].size(); k++) {
//				pomIndex = L.matrixIndexes[i][k];
//				if (pomIndex != i)	
//					newElem += L.getNoZeroElemXY(pomIndex, i) * U.getElemXY(j, pomIndex);
//			}
//			newElem = this->getElemXY(j, i) - newElem;
//			if (newElem != 0)
//				U.setElemXY(j, i, newElem);
//		}
//		for (int j = i + 1; j < this->sizeCols; j++) {
//			newElem = 0;
//			for (int k = 0; k < i; k++) {
//				if (k != j)
//					newElem += L.getElemXY(k, j) * U.getElemXY(i, k);
//			}
//			newElem = (this->getElemXY(j, i) - newElem) / U.getElemXY(i, i);
//			if (newElem != 0)
//				L.setElemXY(i, j, newElem);
//		}
//	}
//}
