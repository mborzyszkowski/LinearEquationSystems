#include "timer.h"


Timer::Timer(){
	this->startTime = std::chrono::high_resolution_clock::now();
}

Timer::~Timer(){
}

void Timer::startTimer() {
	this->startTime = std::chrono::high_resolution_clock::now();
}

std::chrono::duration<double> Timer::getCountedTime() {
	return std::chrono::duration_cast<std::chrono::duration<double>>
		(std::chrono::high_resolution_clock::now() - this->startTime);
}
