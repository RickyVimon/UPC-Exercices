#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"

typedef unsigned __int8 Uint8;

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void SetImgui();
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}
	// Check for window events last frame
	bool GetWindowEvent(EventWindow code) const;

private:
	//const Uint8 *keyboard = NULL;
	KeyState*	keyboard;
	bool		windowEvents[WE_COUNT];
};