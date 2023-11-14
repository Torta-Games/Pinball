#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");


	LoadMap();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::LoadMap()
{
	Pinball = (App->physics->CreateChain(0, 0, pinball, 603, b2BodyType::b2_staticBody));

	Abajo_Derecha = (App->physics->CreateChain(0, 0, abajo_derecha, 36, b2BodyType::b2_staticBody));
	Abajo_Derecha->listener = this;
	Abajo_Derecha->ctype = ColliderType::TRIANGLE_RIGHT;
	
	Abajo_Izquierda = (App->physics->CreateChain(0, 0, abajo_izquierda, 34, b2BodyType::b2_staticBody));
	Abajo_Izquierda->listener = this;
	Abajo_Izquierda->ctype = ColliderType::TRIANGLE_LEFT;

	Propulsor_1 = (App->physics->CreateChain(0, 0, propulsor1, 10, b2BodyType::b2_staticBody));
	Propulsor_2 = (App->physics->CreateChain(0, 0, propulsor2, 12, b2BodyType::b2_staticBody));
	Propulsor_3 = (App->physics->CreateChain(0, 0, propulsor3, 12, b2BodyType::b2_staticBody));

	Palo_1 = (App->physics->CreateChain(0, 0, palo1, 24, b2BodyType::b2_staticBody));
	Palo_2= (App->physics->CreateChain(0, 0, palo2, 26, b2BodyType::b2_staticBody));
	Palo_3 = (App->physics->CreateChain(0, 0, palo3, 26, b2BodyType::b2_staticBody));
	Palo_4 = (App->physics->CreateChain(0, 0, palo4, 28, b2BodyType::b2_staticBody));

	Boing_1 = (App->physics->CreateChain(0, 0, boing1, 14, b2BodyType::b2_staticBody));
	Boing_2 = (App->physics->CreateChain(0, 0, boing2, 10, b2BodyType::b2_staticBody));
	Boing_3 = (App->physics->CreateChain(0, 0, boing3, 14, b2BodyType::b2_staticBody));
	Boing_4 = (App->physics->CreateChain(0, 0, boing4, 14, b2BodyType::b2_staticBody));

	circulo1 = (App->physics->CreateCircle(19, 334, 7, b2BodyType::b2_staticBody));
	circulo2 = (App->physics->CreateCircle(161, 99, 7, b2BodyType::b2_staticBody));

	boxes.add(App->physics->CreateRectangleSensor(230, 800, 220, 2));
	boxes.getLast()->data->listener = this;
	boxes.getLast()->data->ctype = ColliderType::SENSOR;

}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
