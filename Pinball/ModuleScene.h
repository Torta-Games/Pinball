#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "Animation.h"
#include <fstream>
using namespace std;


class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void LoadMap();

	bool leftTriangleColliding = false;
	bool rightTriangleColliding = false;
	bool circle1000Colliding = false;
	bool circle500Colliding = false;
	bool circle200Colliding = false;
	bool circle100Colliding = false;
	bool boing1Colliding = false;
	bool boing2Colliding = false;
	bool boing3Colliding = false;
	bool boing4Colliding = false;
	float timer = 0;

	bool rightFlipperActivated = false;
	bool leftFlipperActivated = false;

	bool piston1Enabled = false;
	bool piston2Enabled = false;
	bool piston3Enabled = false;
	bool piston4Enabled = false;
	bool piston5Enabled = false;
	bool piston6Enabled = false;
	bool coins = false;

private:
	SDL_Texture* backgroundTexture;
	SDL_Texture* backgroundTexture2;
	SDL_Texture* springTexture;
	SDL_Texture* rotatingLightsTexture;
	SDL_Texture* glow100Texture;
	SDL_Texture* glow200Texture;
	SDL_Texture* glow500Texture;
	SDL_Texture* glow1000Texture;
	SDL_Texture* glowLeftTexture;
	SDL_Texture* glowRightTexture;
	SDL_Texture* rightFlipperTexture;
	SDL_Texture* leftFlipperTexture;
	SDL_Texture* boing1Texture;
	SDL_Texture* boing2Texture;
	SDL_Texture* boing3Texture;
	SDL_Texture* boing4Texture;

	SDL_Texture* pistonTexture;
	SDL_Texture* piston1LightTexture;
	SDL_Texture* piston2LightTexture;
	SDL_Texture* piston3LightTexture;
	SDL_Texture* piston4LightTexture;
	SDL_Texture* piston5LightTexture;
	SDL_Texture* piston6LightTexture;

	SDL_Rect pistonLightEnabledRect = {0,0,480,800};
	SDL_Rect pistonLightDisabledRect = {480,0,480,800};
	SDL_Rect pistonDisabledRect = {0,0,30,33};
	SDL_Rect pistonEnabledRect = {30,0,30,33};

	PhysBody* rightFlipperBody;
	PhysBody* rightFlipperPoint;
	PhysBody* leftFlipperBody;
	PhysBody* leftFlipperPoint;

	PhysBody* springBody;
	PhysBody* springDown;
	PhysBody* circle1000Body;
	PhysBody* circle500Body;
	PhysBody* circle200Body;
	PhysBody* circle100Body;
	iPoint springPosition;
	iPoint rightFlipperPosition;
	iPoint leftFlipperPosition;

	iPoint cordsBoing1;
	iPoint cordsBoing2;
	iPoint cordsBoing3;
	iPoint cordsBoing4;

	Animation* currentAnim;
	Animation arrowLights;
	SDL_Texture* arrowLightsTexture;

	Animation* currentAnimBlueLight;
	Animation blueLightAnim;
	SDL_Texture* blueLightTexture;

	SDL_Texture* circleTexture;
	SDL_Texture* numsTexture;

	SDL_Rect scoreRect[10];

	Animation* currentAnimRightArrow;
	Animation rightArrowAnim;
	SDL_Texture* rightArrowTexture;

	Animation* currentAnimLeftArrow;
	Animation leftArrowAnim;
	SDL_Texture* leftArrowTexture;

	Animation* curretnAnimCoin;
	Animation coinAnim;
	SDL_Texture* coinTexture;
	fPoint coinPosition[5];

	int flipperFx, music, combo;

	int springForce = 0;

	double rotation = 0;

	int x, y = 0;

	int highScore = 0;

	fstream scoreFile;

	p2Point<int> ray;
	bool ray_on;

private:
	p2List<PhysBody*> boxes;
	PhysBody* Pinball;

	PhysBody* Palo_1;
	PhysBody* Palo_2;
	PhysBody* Palo_3;
	PhysBody* Palo_4;

	PhysBody* Abajo_Derecha;
	PhysBody* Abajo_Izquierda;

	PhysBody* Propulsor_1;
	PhysBody* Propulsor_2;
	PhysBody* Propulsor_3;
	PhysBody* Propulsor_4;
	PhysBody* Propulsor_5;
	PhysBody* Propulsor_6;

	PhysBody* Boing_1;
	PhysBody* Boing_2;
	PhysBody* Boing_3;
	PhysBody* Boing_4;

	PhysBody* circulo1;
	PhysBody* circulo2;
	PhysBody* circulo3;
	PhysBody* circulo10k;
	PhysBody* circulo5k;
	PhysBody* circulo1k;
	PhysBody* circulo100L;
	PhysBody* circulo100R;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;

	int pinball[603] = {
		294, 800,
		425, 723,
		430, 719,
		434, 713,
		436, 709,
		438, 703,
		438, 629,
		436, 622,
		433, 618,
		429, 613,
		408, 598,
		403, 594,
		401, 590,
		401, 549,
		399, 545,
		395, 541,
		388, 540,
		382, 541,
		379, 544,
		377, 548,
		377, 567,
		375, 570,
		372, 572,
		367, 571,
		352, 560,
		350, 557,
		349, 552,
		351, 547,
		353, 545,
		357, 543,
		362, 542,
		389, 497,
		387, 493,
		385, 490,
		386, 487,
		429, 411,
		432, 405,
		436, 401,
		441, 401,
		442, 405,
		446, 412,
		448, 417,
		449, 421,
		449, 723,
		471, 723,
		471, 440,
		471, 429,
		470, 419,
		468, 407,
		465, 399,
		458, 384,
		450, 371,
		450, 372,
		458, 351,
		468, 317,
		473, 286,
		475, 252,
		472, 220,
		466, 195,
		456, 163,
		441, 138,
		430, 120,
		417, 104,
		395, 81,
		373, 65,
		346, 51,
		313, 38,
		275, 31,
		226, 29,
		188, 35,
		149, 49,
		101, 73,
		47, 101,
		16, 119,
		10, 123,
		7, 130,
		7, 142,
		7, 250,
		7, 333,
		9, 341,
		13, 344,
		19, 345,
		24, 344,
		30, 340,
		96, 307,
		99, 303,
		100, 296,
		100, 285,
		101, 254,
		102, 136,
		104, 126,
		107, 119,
		112, 109,
		123, 94,
		140, 79,
		162, 69,
		193, 59,
		218, 55,
		246, 54,
		275, 56,
		310, 64,
		331, 72,
		349, 81,
		364, 91,
		379, 103,
		398, 122,
		421, 154,
		440, 189,
		447, 211,
		451, 232,
		453, 254,
		452, 279,
		447, 306,
		443, 323,
		440, 330,
		436, 333,
		431, 330,
		431, 324,
		434, 313,
		434, 314,
		439, 285,
		440, 257,
		435, 224,
		429, 200,
		411, 161,
		397, 142,
		384, 126,
		366, 111,
		340, 93,
		310, 80,
		286, 72,
		258, 68,
		241, 67,
		224, 68,
		200, 72,
		174, 80,
		156, 88,
		147, 94,
		157, 112,
		184, 99,
		213, 92,
		252, 90,
		271, 92,
		289, 96,
		308, 103,
		326, 111,
		342, 121,
		354, 130,
		374, 149,
		382, 160,
		395, 179,
		407, 206,
		414, 233,
		415, 248,
		415, 274,
		414, 288,
		413, 295,
		410, 299,
		406, 300,
		403, 298,
		402, 294,
		402, 289,
		403, 280,
		404, 259,
		401, 235,
		396, 216,
		389, 198,
		380, 180,
		367, 162,
		352, 146,
		336, 134,
		322, 125,
		303, 116,
		283, 109,
		266, 105,
		249, 104,
		248, 131,
		264, 132,
		289, 138,
		310, 148,
		329, 161,
		342, 173,
		353, 186,
		361, 199,
		367, 211,
		371, 223,
		374, 233,
		375, 243,
		375, 251,
		375, 255,
		372, 258,
		367, 259,
		362, 256,
		359, 251,
		357, 242,
		357, 241,
		352, 223,
		344, 208,
		334, 193,
		325, 182,
		313, 172,
		294, 161,
		275, 154,
		255, 150,
		228, 150,
		225, 150,
		224, 145,
		222, 136,
		221, 126,
		212, 128,
		199, 132,
		188, 137,
		176, 143,
		162, 151,
		149, 161,
		139, 171,
		134, 178,
		132, 182,
		140, 189,
		149, 199,
		148, 200,
		142, 209,
		137, 218,
		132, 231,
		128, 246,
		126, 257,
		126, 274,
		128, 288,
		129, 294,
		132, 296,
		134, 300,
		136, 308,
		141, 318,
		147, 329,
		155, 341,
		166, 353,
		175, 359,
		182, 363,
		183, 365,
		181, 367,
		177, 367,
		164, 377,
		160, 377,
		156, 377,
		153, 376,
		146, 369,
		122, 331,
		102, 345,
		131, 392,
		132, 397,
		131, 399,
		128, 397,
		124, 393,
		120, 393,
		95, 409,
		91, 408,
		89, 405,
		80, 390,
		54, 406,
		51, 407,
		47, 403,
		37, 386,
		14, 401,
		63, 484,
		64, 489,
		62, 494,
		63, 500,
		81, 532,
		88, 542,
		95, 543,
		100, 547,
		100, 554,
		99, 557,
		90, 565,
		82, 570,
		78, 570,
		75, 568,
		74, 564,
		74, 549,
		72, 544,
		68, 541,
		64, 540,
		58, 540,
		52, 542,
		49, 548,
		49, 589,
		48, 593,
		44, 596,
		37, 601,
		37, 600,
		21, 612,
		17, 617,
		14, 624,
		13, 628,
		13, 638,
		14, 681,
		15, 706,
		19, 714,
		24, 721,
		32, 727,
		155, 800
	};

	int abajo_izquierda[34] = {
	99, 631,
	124, 688,
	126, 697,
	124, 702,
	118, 703,
	111, 701,
	80, 684,
	76, 681,
	75, 677,
	75, 672,
	75, 629,
	75, 623,
	78, 619,
	83, 617,
	89, 618,
	91, 620,
	99, 630
	};

	int abajo_derecha[36] = {
	347, 636,
	321, 691,
	320, 697,
	322, 702,
	327, 703,
	334, 702,
	340, 699,
	367, 682,
	371, 679,
	373, 676,
	374, 669,
	374, 628,
	372, 622,
	369, 618,
	364, 617,
	358, 619,
	355, 622,
	347, 635
	};

	int propulsor4[10] = {
		39, 400,
		42, 405,
		26, 415,
		22, 410,
		35, 402
	};
	int propulsor5[10] = {
		64, 416,
		67, 420,
		82, 411,
		79, 406,
		66, 414
	};
	int propulsor6[10] = {
		108, 416,
		112, 421,
		127, 412,
		124, 407,
		111, 414
	};

	int propulsor1[10] = {
		162, 174,
		144, 191,
		139, 187,
		156, 169,
		160, 172
	};
	int propulsor2[12] = {
		171, 155,
		165, 159,
		169, 165,
		187, 153,
		184, 148,
		174, 153
	};
	int propulsor3[12] = {
		203, 142,
		197, 144,
		199, 149,
		214, 144,
		213, 139,
		205, 141
	};

	int palo1[24] = {
	411, 636,
	411, 688,
	408, 696,
	404, 702,
	320, 752,
	316, 743,
	395, 695,
	398, 690,
	401, 685,
	401, 637,
	404, 634,
	408, 634
	};

	int palo2[26] = {
	129, 740,
	125, 747,
	48, 702,
	43, 696,
	39, 689,
	38, 636,
	41, 632,
	46, 632,
	49, 635,
	49, 684,
	52, 689,
	56, 694,
	126, 737
	};

	int palo3[26] = {
	75, 183,
	75, 267,
	78, 271,
	76, 275,
	70, 276,
	66, 271,
	69, 267,
	69, 183,
	66, 177,
	69, 172,
	75, 172,
	78, 176,
	77, 180
	};

	int palo4[28] = {
	40, 225,
	40, 280,
	42, 284,
	40, 289,
	35, 289,
	32, 284,
	35, 280,
	35, 224,
	33, 221,
	33, 217,
	35, 214,
	40, 214,
	42, 217,
	42, 222
	};

	int boing1[14] = {
	35, 117,
	32, 118,
	17, 167,
	19, 171,
	23, 170,
	38, 123,
	38, 118
	};

	int boing2[10] = {
	260, 107,
	259, 131,
	252, 131,
	253, 107,
	258, 107
	};

	int boing3[14] = {
	92, 535,
	69, 494,
	66, 493,
	64, 496,
	88, 538,
	91, 540,
	93, 538
	};

	int boing4[14] = {
	382, 493,
	356, 537,
	357, 541,
	362, 541,
	386, 499,
	387, 495,
	385, 492
	};
};
