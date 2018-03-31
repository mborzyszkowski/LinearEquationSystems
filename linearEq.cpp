#include "matrix.h"
#include "timer.h"

int main()
{
	//A
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 5 + e, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;

	//N *= 100;	
	Timer timer = Timer();
	timer.startTimer();

	N = 1000;

	Matrix A = Matrix(N);
	A.matrixGeneratr(a1, a2, a3);
	//A.printMatrix();

	
	//B.printMatrix();
	

	//double aa = A.getElemXY(2, 2);
	//double bb = A.getElemXY(10, 0);


	Matrix b = Matrix(N, 1);
	b.vectorGenerator(f);
	/*
	Matrix D = A.matrixD();
	D.printMatrix();
	Matrix L = A.matrixL();
	L.printMatrix();
	Matrix U = A.matrixU();
	U.printMatrix();
	*/

	Matrix B = A * b;
	//b.printMatrix();
	

	double creationTime = timer.getCountedTime() / CLOCKS_PER_SEC;


	//B
	// count Jackobi / Gauss-Seidel spr time norma 10^-9
	// podstawianie w przod jako '/' <- dolna macierz
	// podstawianie w tyl <- gorna macierz

	// dod, odj, mnorzenie liczba kolumn == liczba wierszy

	// Jackobi x(k+1) = -D^(-1) * ((L + U)*x(k)) + kopia(D^(-1))*b

	// Gauss x(k+1) = -(D + L)^(-1) * ((U)*x(k)) + kopia*(D + L)^(-1))*b

	
	return 0;
}

