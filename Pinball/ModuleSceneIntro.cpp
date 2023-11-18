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
	circulo1->body->GetFixtureList()->SetSensor(true);
	circulo1->ctype = ColliderType::CIRCLE_TP1;
	circulo2 = (App->physics->CreateCircle(161, 99, 7, b2BodyType::b2_staticBody));
	circulo2->body->GetFixtureList()->SetSensor(true);
	circulo2->ctype = ColliderType::CIRCLE_TP2;

	boxes.add(App->physics->CreateRectangleSensor(230, 800, 220, 2));
	boxes.getLast()->data->listener = this;
	boxes.getLast()->data->ctype = ColliderType::SENSOR;

}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
