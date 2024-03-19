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

Vector2 RandomNum::RVector2(const Vector2& min, const Vector2& max)
{
	return Vector2(Float(min.x, max.x), Float(min.y, max.y));
}

Vector3 RandomNum::RVector3(const Vector3& min, const Vector3& max)
{
	return Vector3(Float(min.x, max.x), Float(min.y, max.y), Float(min.z, max.z));
}
