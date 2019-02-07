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
			std::cout << "(" << matrixIndexesRows[y][x] << "," << y << ") -> " 
				<< matrixValues.at(y * this->getSizeCols() + matrixIndexesRows[y][x]) << std::endl;
		}
	}
}

Matrix* SparseMatrix::matrixD() {
	SparseMatrix* newMatrix = new SparseMatrix(this->getSizeRows(), this->getSizeCols());

	for (int i = 0; i < this->getSizeRows(); i++) {
		newMatrix->setEmptyElementXY(i, i, this->getElementXY(i, i));
	}
	return newMatrix;
}

Matrix* SparseMatrix::matrixU() {
	SparseMatrix* newMatrix = new SparseMatrix(this->getSizeRows(), this->getSizeCols());

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (size_t x = 0; x < this->matrixIndexesRows[y].size(); x++) {
			if (this->matrixIndexesRows[y][x] > y)
				newMatrix->setEmptyElementXY(this->matrixIndexesRows[y][x], y,
					this->matrixValues[y * this->getSizeCols() + matrixIndexesRows[y][x]]);
		}
	}
	return newMatrix;
}

Matrix* SparseMatrix::matrixL() {
	SparseMatrix* newMatrix = new SparseMatrix(this->getSizeRows(), this->getSizeCols());

	for (int y = 0; y < this->getSizeRows(); y++) {
		for (size_t x = 0; x < this->matrixIndexesRows[y].size(); x++) {
			if (this->matrixIndexesRows[y][x] < y)
				newMatrix->setEmptyElementXY(this->matrixIndexesRows[y][x], y,
					this->matrixValues[y * this->getSizeCols() + matrixIndexesRows[y][x]]);
		}
	}
	return newMatrix;
}

Matrix* SparseMatrix::reverseD() {
	SparseMatrix* newMatrix = new SparseMatrix(this->getSizeRows(), this->getSizeCols());
	double pomValue;

	for (int i = 0; i < this->getSizeRows(); i++) {
		pomValue = this->getElementXY(i, i);
		if (pomValue)
			newMatrix->setEmptyElementXY(i, i, 1.0 / pomValue);
	}
	return newMatrix;
}

void SparseMatrix::doolittle_fLU(Matrix** L, Matrix** U) {
	double newElement;
	SparseMatrix* pomL,* pomU;
	*L = SparseMatrix::diagOnesGenerator(this->getSizeRows());
	pomL = (SparseMatrix*)(*L);
	*U = new SparseMatrix(this->getSizeRows());
	pomU = (SparseMatrix*)(*U);

	for (int i = 0; i < this->getSizeRows(); i++) {
		for (int j = i; j < this->getSizeCols(); j++) {
			newElement = 0;

			for (int k = 0; k < i; k++) {
				if (j != k)
					newElement += pomL->getElementXY(k, i) * pomU->getElementXY(j, k);
			}
			pomU->setEmptyElementXY(j, i, this->getElementXY(j, i) - newElement);
		}
		for (int j = i + 1; j < this->getSizeCols(); j++) {
			newElement = 0;

			for (int k = 0; k < i; k++) {
				if (k != j)
					newElement += pomL->getElementXY(k, j) * pomU->getElementXY(i, k);
			}
			pomL->setEmptyElementXY(i, j, (this->getElementXY(i, j) - newElement) / pomU->getElementXY(i, i));
		}
	}
}

Matrix* SparseMatrix::forwardSubstitution(Matrix* eqations, Matrix* values) {
	SparseMatrix* newMatrix = new SparseMatrix(values->getSizeRows(), 1);
	double pomResult;

	for (int y = 0; y < newMatrix->getSizeRows(); y++) {
		pomResult = 0;

		for (int x = 0; x < y; x++) {
			pomResult += eqations->getElementXY(x, y) * newMatrix->getElementXY(0, x);
		}
		newMatrix->setEmptyElementXY(0, y, (values->getElementXY(0, y) - pomResult) / eqations->getElementXY(y, y));
	}

	return newMatrix;
}

Matrix* SparseMatrix::backSubstitution(Matrix* eqations, Matrix* values) {
	SparseMatrix* newMatrix = new SparseMatrix(values->getSizeRows(), 1);
	double pomResult;
	
	for (int y = newMatrix->getSizeRows() - 1; y >= 0; y--) {
		pomResult = 0;
		for (int x = newMatrix->getSizeRows() - 1; x > y; x--) {
			pomResult += eqations->getElementXY(x, y) * newMatrix->getElementXY(0, x);
		}
		newMatrix->setEmptyElementXY(0, y, (values->getElementXY(0, y) - pomResult) / eqations->getElementXY(y, y));
	}
	return newMatrix;
}

Matrix* SparseMatrix::matrixGenerator(int size, int a1, int a2, int a3) {
	SparseMatrix* newMatrix = new SparseMatrix(size);

	for (int i = 0; i < size; i++) {
		if (i >= 2)
			newMatrix->setEmptyElementXY(i - 2, i, (double)a3);
		if (i >= 1)
			newMatrix->setEmptyElementXY(i - 1, i, (double)a2);
		newMatrix->setEmptyElementXY(i, i, (double)a1);
		if (i < size - 1)
			newMatrix->setEmptyElementXY(i + 1, i, (double)a2);
		if (i < size - 2)
			newMatrix->setEmptyElementXY(i + 2, i, (double)a3);
	}
	return newMatrix;
}

Matrix* SparseMatrix::vectorBGenerator(int size, int f) {
	SparseMatrix* newMatrix = new SparseMatrix(size, 1);

	for (int i = 0; i < size; i++) {
		newMatrix->setEmptyElementXY(0, i, sin((i + 1)*(f + 1)));
	}
	return newMatrix;
}

Matrix* SparseMatrix::vectorXGenerator(int size) {
	SparseMatrix* newMatrix = new SparseMatrix(size, 1);

	for (int i = 0; i < size; i++) {
		newMatrix->setEmptyElementXY(0, i, 1.0 / size);
	}
	return newMatrix;
}

Matrix* SparseMatrix::diagOnesGenerator(int size) {
	SparseMatrix* newMatrix = new SparseMatrix(size);

	for (int i = 0; i < size; i++) {
		newMatrix->setEmptyElementXY(i, i, 1.0);
	}
	return newMatrix;
}

Matrix* SparseMatrix::add(const Matrix& left, const Matrix& right) const {
	Matrix* newMatrix = NULL;

	if (typeid(left) != typeid(right)) {
		newMatrix = right.add(left, right); //static virtual add as normalMatrix??
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

					if (pomRows == pomCols) {
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
