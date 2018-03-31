#include <ctime>

class Timer{
public:
	Timer();
	~Timer();
	void startTimer();
	float getCountedTime();
private:
	float startTime;
	float countedTime;
};

