#include "Framework.h"

Pal::Pal()
{
	name = "";
	modelName = "";
	skill[0] = nullptr;
	skill[1] = nullptr;
	skill[2] = nullptr;
	icon = nullptr;
	iconC = nullptr;
	isUIOn = false;
	onUITime = 0.0f;
}

Pal::~Pal()
{
	delete skill[0];
	delete skill[1];
	delete skill[2];
	
}
