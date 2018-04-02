#include "matrix.h"
#include "timer.h"
#include <fstream>

int main()
{
	Timer timer = Timer();
	std::chrono::duration<double> countedTime;

	//A
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 5 + e, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;
	N = 5;

	sparse::Matrix A = sparse::Matrix(N);
	A.matrixGeneratr(a1, a2, a3);
	sparse::Matrix b = sparse::Matrix(N, 1);
	b.vectorBGenerator(f);

	//sparse::Matrix C = A * A;  // do poprawy


	//B

	std::ofstream logB;
	logB.open("B.txt");


	sparse::Matrix D = A.matrixD();
	sparse::Matrix L = A.matrixL();
	sparse::Matrix U = A.matrixU();
	sparse::Matrix reversedD = D.reverseD();

	// Jackobi x(k+1) = -D^(-1) * ((L + U)*x(k)) + kopia(D^(-1))*b
	
	sparse::Matrix x1 = sparse::Matrix(N, 1);
	x1.vectorXGenerator();
	sparse::Matrix residuum1 = (A*x1) - b;
	sparse::Matrix reverseD_M_b = reversedD * b;
	sparse::Matrix L_P_U = L + U;

	timer.startTimer();

	int spr1 = 0;
	while (residuum1.norm() > 0.000000001) {
		x1 = -(reversedD * (L_P_U * x1)) + reverseD_M_b;
		//Matrix pomMatrix = -(L_P_U * x1) + b;
		//x1 = x1.forwardSubstitution(D, pomMatrix);
		residuum1 = (A*x1) - b;
		spr1++;
	}

	countedTime = timer.getCountedTime();
	logB << "Czas metody Jackobiego: " << countedTime.count() << std::endl;

	// Gauss-Seidel x(k+1) = -(D + L)^(-1) * ((U)*x(k)) + kopia*(D + L)^(-1))*b
	// x2 = ((D_P_L)^-1)*(U*x2) +  ((D_P_L)^-1) * b;
	// D_P_L * x2 = -(U*x2) + b

	sparse::Matrix x2 = sparse::Matrix(N, 1);
	x2.vectorXGenerator();
	sparse::Matrix residuum2 = (A*x2) - b;
	sparse::Matrix D_P_L = -(D + L);
	
	timer.startTimer();

	int spr2 = 0;
	while (residuum2.norm() > 0.000000001) {
		sparse::Matrix pomMatrix = ((U*x2)) - b;
		x2 = x2.forwardSubstitution(D_P_L, pomMatrix);
		residuum2 = (A * x2) - b;
		spr2++;
	}

	countedTime = timer.getCountedTime();
	logB << "Czas metody Gauss-Seidel: " << countedTime.count() << std::endl;

	logB.close();

	
	// C 
	//50 - 100 iter pokazac ze nie zbiega, wyjesnic z jakiej przyczyny teorytycznej


	// D 
	//faktoryzacja LU -> L_*U_*x3 = b, y = U_*x3
	//vect y: L_*y=b  -> y = y.forwardSubstitution(L_,b)
	//vext x3: U_*x3=y -> x3 = x3.backSubstitution(U_,y)

	std::fstream logD;
	logD.open("D.txt");

	sparse::Matrix L_ = sparse::Matrix(N);
	sparse::Matrix U_ = sparse::Matrix(N);
	sparse::Matrix x3 = sparse::Matrix(N, 1);
	sparse::Matrix y = sparse::Matrix(N, 1);
	
	timer.startTimer();

	A.doolittle_fLU(L_, U_);
	y = y.forwardSubstitution(L_, b);
	x3 = x3.backSubstitution(U_, y);
	countedTime = timer.getCountedTime();
	logD << countedTime.count() << std::endl;
	
	//E wielka petla

	
	return 0;
}

