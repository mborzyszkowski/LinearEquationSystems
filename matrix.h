#include<vector>

namespace normal {
	class Matrix {
	public:
		/*NxN*/
		Matrix(int n);
		/*MxN*/
		Matrix(int m, int n);
		~Matrix();
		void matrixGenerator(int a1, int a2, int a3);
		void vectorBGenerator(int f);
		void vectorXGenerator();
		void diagOnesGenerator();
		void printMatrix();
		double norm();
		void doolittle_fLU(Matrix& L, Matrix& U);
		Matrix forwardSubstitution(Matrix& eqations, Matrix& values);
		Matrix backSubstitution(Matrix& eqations, Matrix& values);
		friend const Matrix operator+ (const Matrix& left, const Matrix& right);
		friend const Matrix operator- (const Matrix& left, const Matrix& right);
		friend const Matrix operator* (const Matrix& left, const Matrix& right);
		friend const Matrix operator- (const Matrix& matrix);
	private:
		int sizeCols;
		int sizeRows;
		std::vector<std::vector<double>> values;
	};
}