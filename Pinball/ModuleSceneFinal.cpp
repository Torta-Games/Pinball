#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneFinal.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"
#include "ModulePlayer.h"
#include <string>

ModuleSceneFinal::ModuleSceneFinal(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneFinal::~ModuleSceneFinal()
{}

// Load assets
bool ModuleSceneFinal::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	score = App->player->score;

	for (int i = 0; i < 10; i++)
	{
		scoreRect[i] = { 11 * i, 0, 8, 14 };
	}

	buttonClicked = false;

	backgroundTexture = App->textures->Load("pinball/game_over_pinball.png");
	numsTexture = App->textures->Load("pinball/nums.png");
	//Disable();
	return ret;
}

// Load assets
bool ModuleSceneFinal::CleanUp()
{
	LOG("Unloading Intro scene");
	backgroundTexture = nullptr;
	numsTexture = nullptr;
	App->player->Enable();
	App->scene->Enable();
	return true;
}

// Update: draw background
update_status ModuleSceneFinal::Update()
{
	buttonRect = { 81, 548, 320, 160 };

	SDL_GetMouseState(&mouse.x, &mouse.y);

	mouseOverButton = (mouse.x >= buttonRect.x && mouse.x <= buttonRect.x + buttonRect.w &&
		mouse.y >= buttonRect.y && mouse.y <= buttonRect.y + buttonRect.h);

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && mouseOverButton)
	{
		buttonClicked = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || buttonClicked)
	{
		Disable();
	}

	App->renderer->Blit(backgroundTexture, 0, 0);

	string scoreString = to_string(score);
	int scoreXPos = 250 - (scoreString.size() * 8);

	for (unsigned int i = 0; i < scoreString.size(); i++)
	{
		int digit = scoreString[i] - '0';

		App->renderer->Blit(numsTexture, scoreXPos + (i * 10), 430, &scoreRect[digit], 0.0f);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneFinal::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
