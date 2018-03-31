#include <ctime>
#include "timer.h"


Timer::Timer(){
	this->startTime = 0;
	this->countedTime = 0;
}


Timer::~Timer(){
}

void Timer::startTimer() {
	this->startTime = clock();
}

float Timer::getCountedTime() {
	return clock() - this->startTime;
}
