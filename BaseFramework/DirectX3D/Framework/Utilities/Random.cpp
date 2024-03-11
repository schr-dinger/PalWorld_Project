#include "Framework.h"
#include "Random.h"

RandomNum::RandomNum()
{
	random_device rd;
	randomEngine = new default_random_engine(rd());
}

RandomNum::~RandomNum()
{
	delete randomEngine;
}

int RandomNum::Int(int min, int max)
{
	uniform_int_distribution<int> result(min, max);

	return result(*randomEngine);
}

float RandomNum::Float(float min, float max)
{
	uniform_real_distribution<float> result(min, max);

	return result(*randomEngine);
}