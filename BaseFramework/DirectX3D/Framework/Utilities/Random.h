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
};
