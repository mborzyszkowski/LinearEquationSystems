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

