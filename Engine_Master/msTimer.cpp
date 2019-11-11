#include "msTimer.h"
#include "SDL.h"


msTimer::msTimer()
{
}


msTimer::~msTimer()
{
}

void msTimer::Start()
{
	initialtime = SDL_GetTicks();
}

void msTimer::Read()
{ 
	currentTime = SDL_GetTicks();
	float out = currentTime - initialtime;
	LOG("Time cost: %f", out);
}

void msTimer::Stop()
{

}
