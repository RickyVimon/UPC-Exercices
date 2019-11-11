#pragma once
#include "Module.h"
class msTimer
{
public:
	msTimer();
	~msTimer();
	void Start();
	void Read();
	void Stop();

private:
	double initialtime = 0, currentTime;
};

