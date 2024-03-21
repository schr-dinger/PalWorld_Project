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


	WorkBench* GetBench() { return workBench; }

private:
	PalBox* palBox;
	WorkBench* workBench;
};
