#pragma once
class AStarManager : public Singleton<AStarManager>
{
public:
	AStarManager();
	~AStarManager();

	void Update();
	void Render();

	AStar* GetAStar() { return aStar; }
private:
	AStar* aStar;
};

