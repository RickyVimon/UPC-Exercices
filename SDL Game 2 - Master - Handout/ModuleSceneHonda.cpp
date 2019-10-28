#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 818;
	ground.h = 64;

	// Background / sky
	ceiling.x = 90;
	ceiling.y = 8;
	ceiling.w = 766;
	ceiling.h = 49;

	background.x = 120;
	background.y = 128;
	background.w = 672;
	background.h = 200;

	bathtub.x = 164;
	bathtub.y = 64;
	bathtub.w = 420;
	bathtub.h = 53;


	// flag animation
	water.frames.push_back({ 8, 448, 285, 9 });
	water.frames.push_back({ 296, 448, 285, 14 });
	water.frames.push_back({ 588, 448, 285, 20 });
	water.speed = 0.02f;

}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage2.png");
	graphics_water = App->textures->Load("honda_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();

	// TODO 0: trigger background music
	App->audio->PlayMusic("honda.ogg", 4.0f);

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading ken honda");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics_water);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{


	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, -75, 170, &ground, 1.1f);
	App->renderer->Blit(graphics, 0, 0, &background); // sea and sky
	App->renderer->Blit(graphics, -53, 0, &ceiling);
	App->renderer->Blit(graphics, 210, 140, &bathtub, 1.1f);

	App->renderer->Blit(graphics_water, 232, 155, &(water.GetCurrentFrame()), 1.1f); 



	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//close window
		App->fade->FadeToBlack(App->scene_honda, nullptr, 5.0f);
		App->CleanUp();


	}


	return UPDATE_CONTINUE;
}
