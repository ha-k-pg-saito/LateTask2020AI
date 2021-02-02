#include"../h/Item.h"

void ItemManager::Initialize()
{
	for (int i = 0; i < 5; i++)
	{
		Items[i].Initialize(0.0f, 0.0f);
	}
}

void ItemManager::Update()
{
	++Timer;
	if (Timer % 60 == 0)
	{
		float X = rand() % 400;
		float Y = rand() % 400; 
		CreateItem(X, Y);
	}
}

void ItemManager::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		if (Items[i].IsActive == false)
		{
			continue;
		}
		Items[i].Draw();
	}
}
Item* ItemManager::CreateItem(float x, float y)
{
	for (int i = 0; i < 5; i++)
	{
		if (Items[i].IsActive == false)
		{
			Items[i].Initialize(x, y);
			Items[i].IsActive = true;
			return &Items[i];
		}
	}
	return nullptr;
}