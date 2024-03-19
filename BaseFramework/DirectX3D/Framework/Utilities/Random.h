#pragma once
class RandomNum : public Singleton<RandomNum>
{
private:
	default_random_engine* randomEngine;

public:
	RandomNum();
	~RandomNum();

	int Int(int min = 0, int max = 1);
	float Float(float min = 0.0f, float max = 1.0f);
	Vector2 RVector2(const Vector2& min, const Vector2& max);
	Vector3 RVector3(const Vector3& min, const Vector3& max);
};
