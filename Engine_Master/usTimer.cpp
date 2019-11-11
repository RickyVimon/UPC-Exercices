#include "usTimer.h"
#include "SDL.h"


usTimer::usTimer()
{
}


usTimer::~usTimer()
{
}

void usTimer::Start()
{
	initialtime = SDL_GetPerformanceCounter();
}

void usTimer::Read()
{
	currentTime = SDL_GetPerformanceCounter();
	//LOG("Time cost: %f", currentTime - initialtime);
}

void usTimer::Stop()
{

}
