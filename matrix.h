#include <vector>
#include <unordered_map>

class Matrix {
public:
	/*NxN*/
	Matrix(int n);
	/*MxN*/
	Matrix(int m, int n);
	~Matrix();
	void matrixGeneratr(int a1, int a2, int a3);
	void vectorBGenerator(int f);
	void vectorXGenerator();
	void printMatrix();
	double getElemXY(int x, int y);
	double norm();
	Matrix matrixD();
	Matrix matrixU();
	Matrix matrixL();
	Matrix reverseD();
	friend const Matrix operator+ (const Matrix& left, const Matrix& right);
	friend const Matrix operator- (const Matrix& left, const Matrix& right);
	friend const Matrix operator* (const Matrix& left, const Matrix& right);
	friend const Matrix operator- (const Matrix& matrix);
private:
	int sizeCols;
	int sizeRows;
	std::vector<std::vector<int>> matrixIndexes;
	std::unordered_map<long long, double> matrixValues;
	double getNoZeroElemXY(int x, int y) const;
	void setElemXY(int x, int y, double val);
	void changeElemXY(int x, int y, double val);
};