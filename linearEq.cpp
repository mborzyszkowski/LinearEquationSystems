#include "matrix.h"
#include "timer.h"
#include <iostream>

int main()
{
	//A
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 5 + e, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;

	
	//N = 1000;

	Matrix A = Matrix(N);
	A.matrixGeneratr(a1, a2, a3);
	Matrix b = Matrix(N, 1);
	b.vectorBGenerator(f);
	
	
	//B

	Matrix D = A.matrixD();
	Matrix L = A.matrixL();
	Matrix U = A.matrixU();
	Matrix reversedD = D.reverseD();

	// Jackobi x(k+1) = -D^(-1) * ((L + U)*x(k)) + kopia(D^(-1))*b
	// residium: norm (Ax - b) > 10^-9

	
	// Matrix z = A * A; popr bo wchodzi na zera z prawej macierzy
	// Jackobi
	
	Matrix x = Matrix(N, 1);
	x.vectorXGenerator();
	Matrix residuum = (A*x) - b;
	Matrix reverseD_M_b = reversedD * b;
	Matrix L_P_U = L + U;

	Timer timer = Timer();
	timer.startTimer();

	int spr = 0;
	while (residuum.norm() > 0.000000001) {
		x = -(reversedD * (L_P_U * x)) + reverseD_M_b;
		residuum = (A*x) - b;
		spr++;
	}

	std::chrono::duration<double> creationTime = timer.getCountedTime();
	std::cout << creationTime.count();

	// Gauss-Seidel

	// Gauss x(k+1) = -(D + L)^(-1) * ((U)*x(k)) + kopia*(D + L)^(-1))*b

	// count Jackobi / Gauss-Seidel spr time norma 10^-9
	// podstawianie w przod jako '/' <- dolna macierz
	// podstawianie w tyl <- gorna macierz

	
	return 0;
}

