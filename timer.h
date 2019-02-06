#ifndef TIMER_H
#define TIMER_H

#include <chrono>


class Timer{
public:
	Timer();
	~Timer();
	void startTimer();
	std::chrono::duration<double> getCountedTime();
private:
	std::chrono::high_resolution_clock::time_point startTime;
};

#endif // !TIMER_H
