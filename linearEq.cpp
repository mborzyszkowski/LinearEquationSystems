#include "normalMatrix.h"
#include "sparseMatrix.h"
#include "timer.h"
#include <iostream>
#include <fstream>

void A();
void B();
void C();
void D();
void E();
void Test();

int main()
{
	//A();
	//B();
	//C();
	//D();
	//E();
	//Test();
	return 0;
}

void A() {
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 5 + e, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;

	Matrix* A = SparseMatrix::matrixGenerator(N, a1, a2, a3);
	Matrix* b = SparseMatrix::vectorBGenerator(N, f);
	ObjectManager::clearAllObjects();
}

void B() {	//implementacja metod iteracyjnych
	Timer timer = Timer();
	std::chrono::duration<double> countedTime;

	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 5 + e, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;

	Matrix* A = SparseMatrix::matrixGenerator(N, a1, a2, a3);
	Matrix* b = SparseMatrix::vectorBGenerator(N, f);
	std::ofstream logB;
	logB.open("B.txt");


	Matrix* D = A->matrixD();
	Matrix* L = A->matrixL();
	Matrix* U = A->matrixU();

	// Jackobi x(k+1) = -D^(-1) * ((L + U)*x(k)) + (D^(-1))*b

	Matrix* reversedD = D->reverseD();
	Matrix* x1 = SparseMatrix::vectorXGenerator(N);
	Matrix* x1Pom = x1;
	Matrix* residuum1 = &((*A * *x1) - *b);
	Matrix* reverseD_M_b = &(*reversedD * *b);  reverseD_M_b->setMarked();
	Matrix* L_P_U = &(*L + *U);  L_P_U->setMarked();

	timer.startTimer();

	int spr1 = 0;
	while (residuum1->normalize() > 0.000000001) {
		x1 = &(-(*reversedD * (*L_P_U * *x1Pom)) + *reverseD_M_b);  x1->setMarked();
		ObjectManager::clearUnmarkedObjects();
		residuum1 = &((*A * *x1) - *b);
		x1Pom = x1; x1Pom->setUnMarked();
		spr1++;
	}
	//Could be:
	//Matrix* pomMatrix = &(-(*L_P_U * *x1Pom) + *b);
	//x1 = x1.forwardSubstitution(D, pomMatrix);

	countedTime = timer.getCountedTime();
	logB << "Metoda Jackobiego: Czas - " << countedTime.count() << "sec" << " Ilosc iteracji: " << spr1 << std::endl;

	// Gauss-Seidel x(k+1) = -(D + L)^(-1) * ((U)*x(k)) + (D + L)^(-1))*b
	// x2 = ((D_P_L)^-1)*(U*x2) +  ((D_P_L)^-1) * b;
	// D_P_L * x2 = -(U*x2) + b

	Matrix* x2 = SparseMatrix::vectorXGenerator(N);
	Matrix* pomMatrix = NULL;
	Matrix* residuum2 = &((*A * *x2) - *b);
	Matrix* D_P_L = &(-(*D + *L));  D_P_L->setMarked();

	timer.startTimer();

	int spr2 = 0;
	while (residuum2->normalize() > 0.000000001) {
		pomMatrix = &((*U * *x2) - *b);  x2->setUnMarked();
		x2 = x2->forwardSubstitution(D_P_L, pomMatrix);
		ObjectManager::clearUnmarkedObjects();
		residuum2 = &((*A * *x2) - *b);
		spr2++;
	}

	countedTime = timer.getCountedTime();
	logB << "Metoda Gaussa-Seidela: Czas - " << countedTime.count() << "sec" << " Ilosc iteracji: " << spr2 << std::endl;

	logB.close();
	ObjectManager::clearAllObjects();
}


void C() { //100 iter pokazac ze nie zbiega. -> Nie zbiega poniweaz A nie jest diagonalnie dominujace dla tego przypadku.
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 3, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;

	Matrix* A = SparseMatrix::matrixGenerator(N, a1, a2, a3);
	Matrix* b = SparseMatrix::vectorBGenerator(N, f);
	std::ofstream logC;
	logC.open("C.txt");


	Matrix* D = A->matrixD();
	Matrix* L = A->matrixL();
	Matrix* U = A->matrixU();

	// Jackobi
	Matrix* reversedD = D->reverseD();
	Matrix* x1 = SparseMatrix::vectorXGenerator(N);
	Matrix* x1Pom = x1;
	Matrix* residuum1 = &((*A * *x1) - *b);
	Matrix* reverseD_M_b = &(*reversedD * *b);  reverseD_M_b->setMarked();
	Matrix* L_P_U = &(*L + *U);  L_P_U->setMarked();

	logC << "Metoda Jackobiego: " << std::endl;

	double normResidum1 = residuum1->normalize();
	int spr1 = 0;
	while (normResidum1 > 0.000000001) {
		x1 = &(-(*reversedD * (*L_P_U * *x1Pom)) + *reverseD_M_b);  x1->setMarked();
		ObjectManager::clearUnmarkedObjects();
		residuum1 = &((*A * *x1) - *b);
		normResidum1 = residuum1->normalize();
		x1Pom = x1; x1Pom->setUnMarked();
		spr1++;
		logC << spr1 << "\t" << normResidum1 << std::endl;
		if (spr1 == 100)
			break;
	}

	// Gauss-Seidel
	Matrix* x2 = SparseMatrix::vectorXGenerator(N);
	Matrix* pomMatrix = NULL;
	Matrix* residuum2 = &((*A * *x2) - *b);
	Matrix* D_P_L = &(-(*D + *L));  D_P_L->setMarked();

	logC << std::endl << "Metoda Gaussa-Seidela: " << std::endl;

	double normResidum2 = residuum2->normalize();
	int spr2 = 0;
	while (normResidum2 > 0.000000001) {
		pomMatrix = &((*U * *x2) - *b);  x2->setUnMarked();
		x2 = x2->forwardSubstitution(D_P_L, pomMatrix);
		ObjectManager::clearUnmarkedObjects();
		residuum2 = &((*A * *x2) - *b);
		normResidum2 = residuum2->normalize();
		spr2++;
		logC << spr2 << "\t" << normResidum2 << std::endl;
		if (spr2 == 100)
			break;
	}

	logC.close();
	ObjectManager::clearAllObjects();
}


void D() {	//faktoryzacja LU -> L_*U_*x3 = b, y = U_*x3
	Timer timer = Timer();
	std::chrono::duration<double> countedTime;
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 3, a2 = -1, a3 = -1;
	int N = 900 + ((index % 100) / 10) * 10 + index % 10;
	int f = (index % 10000) / 1000;

	//vect y: L_*y=b  -> y = y.forwardSubstitution(L_,b)
	//vext x3: U_*x3=y -> x3 = x3.backSubstitution(U_,y)

	std::ofstream logD;
	logD.open("D.txt");
	{
		Matrix* nA = NormalMatrix::matrixGenerator(N, a1, a2, a3);
		Matrix* nb = NormalMatrix::vectorBGenerator(N, f);

		Matrix* L_ = NULL;
		Matrix* U_ = NULL;
		Matrix* x3 = new NormalMatrix(1, 1, false);
		Matrix* y = new NormalMatrix(1, 1, false);
		Matrix* residuum = NULL;

		timer.startTimer();

		nA->doolittle_fLU(&L_, &U_);
		y = y->forwardSubstitution(L_, nb);
		x3 = x3->backSubstitution(U_, y);

		residuum = &((*nA * *x3) - *nb);
		double normResiduum = residuum->normalize();

		countedTime = timer.getCountedTime();
		logD << "faktoryzacjaLU czas: " << countedTime.count() << "sec" << "  \tnorma residuum: " << normResiduum << std::endl;
	}

	logD.close();
	ObjectManager::clearAllObjects();
}

void E() {
	Timer timer = Timer();
	std::chrono::duration<double> countedTime;
	int index = 165407;
	int e = (index % 1000) / 100;
	int a1 = 5 + e, a2 = -1, a3 = -1, N = 100;
	int f = (index % 10000) / 1000;
	int tab[10] = { 100, 500, 1000, 2000, 3000, 4000, 5000 };
	// 100, 500, 1000, 2000, 3000, 4000, 5000
	// 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000
	// 16000, 17000, 18000, 19000, 20000, 30000, 40000, 50000, 60000, 70000
	// 80000, 90000, 100000, 200000, 300000, 400000, 500000, 600000
	// 700000, 800000, 900000, 1000000

	std::ofstream logE;
	logE.open("E.txt");

	for (int i = 0; i < 7; i++) {
		N = tab[i];
		logE << std::endl << "Czas wykonania dla N = " << N << " wynosi:" << std::endl;

		Matrix* A = SparseMatrix::matrixGenerator(N, a1, a2, a3);
		Matrix* b = SparseMatrix::vectorBGenerator(N, f);
		std::ofstream logC;

		Matrix* D = A->matrixD();
		Matrix* L = A->matrixL();
		Matrix* U = A->matrixU();

		// Jackobi x(k+1) = -D^(-1) * ((L + U)*x(k)) + (D^(-1))*b
		{
			Matrix* reversedD = D->reverseD();
			Matrix* x1 = SparseMatrix::vectorXGenerator(N);
			Matrix* x1Pom = x1;
			Matrix* residuum1 = &((*A * *x1) - *b);
			Matrix* reverseD_M_b = &(*reversedD * *b);  reverseD_M_b->setMarked();
			Matrix* L_P_U = &(*L + *U);  L_P_U->setMarked();

			timer.startTimer();

			int spr1 = 0;
			while (residuum1->normalize() > 0.000000001) {
				x1 = &(-(*reversedD * (*L_P_U * *x1Pom)) + *reverseD_M_b);  x1->setMarked();
				ObjectManager::clearUnmarkedObjects();
				residuum1 = &((*A * *x1) - *b);
				x1Pom = x1; x1Pom->setUnMarked();
				spr1++;
			}

			countedTime = timer.getCountedTime();
			logE << "\tCzas metody Jackobiego: " << countedTime.count() << "sec" << std::endl;
		}
		// Gauss-Seidel x(k+1) = -(D + L)^(-1) * ((U)*x(k)) + (D + L)^(-1))*b
		{
			Matrix* x2 = SparseMatrix::vectorXGenerator(N);
			Matrix* pomMatrix = NULL;
			Matrix* residuum2 = &((*A * *x2) - *b);
			Matrix* D_P_L = &(-(*D + *L));  D_P_L->setMarked();

			timer.startTimer();

			int spr2 = 0;
			while (residuum2->normalize() > 0.000000001) {
				pomMatrix = &((*U * *x2) - *b);  x2->setUnMarked();
				x2 = x2->forwardSubstitution(D_P_L, pomMatrix);
				ObjectManager::clearUnmarkedObjects();
				residuum2 = &((*A * *x2) - *b);
				spr2++;
			}

			countedTime = timer.getCountedTime();
			logE << "\tCzas metody Gaussa-Seidela: " << countedTime.count() << "sec" << std::endl;
		}

		// faktoryzacjaLU
		{
			Matrix* nA = NormalMatrix::matrixGenerator(N, a1, a2, a3);
			Matrix* nb = NormalMatrix::vectorBGenerator(N, f);

			Matrix* L_ = NULL;
			Matrix* U_ = NULL;
			Matrix* x3 = new NormalMatrix(1, 1, false);
			Matrix* y = new NormalMatrix(1, 1, false);
			Matrix* residuum = NULL;

			timer.startTimer();

			nA->doolittle_fLU(&L_, &U_);
			y = y->forwardSubstitution(L_, nb);
			x3 = x3->backSubstitution(U_, y);

			countedTime = timer.getCountedTime();
			logE << "\tCzas metody faktoryzacjaLU normal: " << countedTime.count() << "sec" << std::endl;
		}

		ObjectManager::clearAllObjects();
	}

	logE.close();
}

void Test() {
	Matrix* genTest1 = SparseMatrix::matrixGenerator(4, 3, 2, 1);
	genTest1->print();
	std::cout << std::endl;

	Matrix* genTest2 = SparseMatrix::vectorBGenerator(4, 3);
	genTest2->print();
	std::cout << std::endl;

	Matrix* genTest3 = SparseMatrix::vectorXGenerator(4);
	genTest3->print();
	std::cout << std::endl;

	Matrix* genTest4 = SparseMatrix::diagOnesGenerator(4);
	genTest4->print();
	std::cout << std::endl;

	Matrix* testN1 = new NormalMatrix(2, 3);
	testN1->setElementXY(0, 0, 1);
	testN1->setElementXY(1, 0, 2);
	testN1->setElementXY(0, 1, 3);
	testN1->setElementXY(1, 1, 4);
	testN1->print();
	std::cout << std::endl;

	Matrix* testN2 = new NormalMatrix(2, 2);
	testN2->setElementXY(0, 0, 5);
	testN2->setElementXY(1, 0, 6);
	testN2->setElementXY(0, 1, 7);
	testN2->setElementXY(1, 1, 8);
	testN2->print();
	std::cout << std::endl;

	Matrix* resultN = &(-*testN1);
	resultN->setMarked();
	resultN->print();
	std::cout << std::endl;

	SparseMatrix* sparseTest1 = new SparseMatrix(3, 2);
	sparseTest1->setElementXY(0, 0, 1);
	sparseTest1->setElementXY(0, 1, 3);
	sparseTest1->print();
	std::cout << std::endl;

	SparseMatrix* sparseTest2 = new SparseMatrix(2, 2);
	sparseTest2->setElementXY(0, 0, 1);
	sparseTest2->setElementXY(1, 0, 3);
	sparseTest2->print();
	std::cout << std::endl;

	Matrix* res = &(-*sparseTest1);
	res->setMarked();
	res->print();

	ObjectManager::clearUnmarkedObjects();
	ObjectManager::clearAllObjects();
}
