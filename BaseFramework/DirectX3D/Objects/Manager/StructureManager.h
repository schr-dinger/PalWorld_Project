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


	bool isPalBoxWork() { return palBox->PalWorkCheck(); }
	bool isWorkBenchWork() { return workBench->PalWorkCheck(); }

	PalBox* GetPalBox() { return palBox; }
	WorkBench* GetWorkBench() { return workBench; }
private:
	PalBox* palBox;
	WorkBench* workBench;
};
