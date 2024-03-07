#pragma once
class StructureManager :public Singleton<StructureManager>
{
public:
	StructureManager();
	~StructureManager();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void GUIRender();

private:
	PalBox* palBox;
	WorkBench* workBench;
};
