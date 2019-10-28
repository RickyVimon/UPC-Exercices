#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 130;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 11, 60, 93});
	idle.frames.push_back({95, 11, 60, 94});
	idle.frames.push_back({184, 11, 60, 94});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 11, 60, 93});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 127, 61, 91});
	backward.frames.push_back({628, 127, 59, 92});
	backward.frames.push_back({713, 127, 57, 94});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 127, 58, 92});
	backward.frames.push_back({974, 127, 57, 92});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 8, 127, 55, 94 });
	forward.frames.push_back({ 77, 127, 62, 94 });
	forward.frames.push_back({ 161, 127, 66, 94 });
	forward.frames.push_back({ 258, 127, 65, 92 });
	forward.frames.push_back({ 352, 127, 56, 94 });
	forward.frames.push_back({ 432, 127, 51, 95 });
	forward.speed = 0.1f;


}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		position.x = position.x + 1;
		App->renderer->Blit(graphics, position.x, position.y, &(forward.GetCurrentFrame()), 1.3f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		position.x = position.x - 1;
		App->renderer->Blit(graphics, position.x, position.y, &(backward.GetCurrentFrame()), 1.3f);
	}
	else
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.3f);

	return UPDATE_CONTINUE;
}

