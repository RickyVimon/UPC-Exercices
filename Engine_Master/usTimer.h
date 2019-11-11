#pragma once
class usTimer
{
public:
	usTimer();
	~usTimer();
	void Start();
	void Read();
	void Stop();

private:
	double initialtime = 0, currentTime;
};

