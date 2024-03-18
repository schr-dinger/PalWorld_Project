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

	Transform* GetPalBox() { return palBox->GetBuilding(); }
	Transform* GetWorkBench() { return workBench->GetBuilding(); }

	bool isPalBoxWork() { return palBox->PalWorkCheck(); }
	bool isWorkBenchWork() { return workBench->PalWorkCheck(); }

private:
	PalBox* palBox;
	WorkBench* workBench;
};
