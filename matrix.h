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
	void vectorGenerator(int f);
	void printMatrix();
	double getElemXY(int x, int y);
	Matrix matrixD();
	Matrix matrixU();
	Matrix matrixL();
	friend Matrix operator+ (Matrix& left, Matrix& right);
	friend Matrix operator- (Matrix& left, Matrix& right);
	friend Matrix operator* (Matrix& left, Matrix& right);
private:
	int sizeCols;
	int sizeRows;
	std::vector<std::vector<int>> matrixIndexes;
	std::unordered_map<long long, double> matrixValues;
	double getNoZeroElemXY(int x, int y);
	void setElemXY(int x, int y, double val);
	void changeElemXY(int x, int y, double val);
};