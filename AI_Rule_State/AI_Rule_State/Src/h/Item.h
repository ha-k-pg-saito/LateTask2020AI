#ifndef ITEM_H
#define ITEM_H

#include"../Engine/Engine.h"

class Item
{
public:
	void Initialize(float x, float y)
	{
		Pos = Vec2(x, y);
		IsActive = false;
	}
	void Draw()
	{
		Engine::DrawFan(Vec2(Pos.X, Pos.Y), 360.f, 20.f, 0, 0xff0000ff);
		Engine::DrawRect(Pos.X, Pos.Y , 3.0f, 3.0f, 0x0000ff);
	}

public:
	Vec2 Pos;
	bool IsActive;
};

class ItemManager
{
public:
	//シングルトン作成
	static ItemManager* Instance()
	{
		//唯一無二のインスタンス
		static ItemManager instance;
		return& instance;
	}
	void Initialize();
	void Update();
	void Draw();
	Item* CreateItem(float x, float y);

public:
	Item Items[5];

private:
	unsigned int Timer;
	ItemManager() {}
};

#endif 
