#include "Framework.h"

Skill::Skill()
{
	name = "";
	damage = 0;
	pal = nullptr;
	col = nullptr;
	enemy = nullptr;
}

Skill::~Skill()
{
	delete col;
}
