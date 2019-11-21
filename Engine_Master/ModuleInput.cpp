#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleModelLoader.h"
#include "MathGeoLib/include/Math/MathAll.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput()
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::PreUpdate()
{
	memset(windowEvents, false, WE_COUNT * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	SDL_PumpEvents();
	static SDL_Event event;
	//SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			windowEvents[WE_QUIT] = true;
			return UPDATE_STOP;
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				App->window->WindowResized(event.window.data1, event.window.data2);
			break;

		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
			{
				App->camera->ZoomIn();
			}
			else if (event.wheel.y < 0)
			{
				App->camera->ZoomOut();
			}
			break;

		case SDL_MOUSEMOTION:
			if (event.motion.state & SDL_BUTTON_RMASK) {
				if (math::Abs(event.motion.xrel) > 1.5) {
					App->camera->Rotate(Y, event.motion.xrel * 0.03); //0.03 is a reductor factor to adjust the speed of the mouse to the same functionallity with the arrow keys
				}

				if (math::Abs(event.motion.yrel) > 1.5) {
					App->camera->Rotate(Z, event.motion.yrel * 0.03);
				}
			}
			break;

		case SDL_DROPFILE:
			App->moduleloader->LoadModel(event.drop.file);
			SDL_free(event.drop.file);
			break;
		}

	}	
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	//keyboard = SDL_GetKeyboardState(NULL);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
