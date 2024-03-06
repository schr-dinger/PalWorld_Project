#pragma once
class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	~PlayerManager();

    void Update();
    void Render();
    void GUIRender();

    Player* GetPlayer() { return player; }

private:
    Player* player;
};

