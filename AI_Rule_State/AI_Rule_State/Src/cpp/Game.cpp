#include<time.h>
#include"../h/Game.h"

Game::Game()
{
	ItemManager::Instance()->Initialize();

}

Game::~Game()
{
}

void Game::Update()
{
	AI_R.Update();
	AI_S.Update();
	
		ItemManager::Instance()->Update();
	
	//AI_Rとアイテムのあたり判定
	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionCircleAndCircle(
			ItemManager::Instance()->Items[i].Pos,
			collision.ItemSize,
			AI_R.m_Position,
			collision.AiSize) == true)
		{
			ItemManager::Instance()->Items[i].IsActive = false;
		}
	}

	//AI_Sとアイテムのあたり判定
	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionCircleAndCircle(
			ItemManager::Instance()->Items[i].Pos,
			collision.ItemSize,
			AI_S.Pos,
			collision.AiSize) == true)
		{
			ItemManager::Instance()->Items[i].IsActive = false;
		}
	}

}

void Game::Draw()
{
	Engine::StartDrawing(0);
	AI_R.Draw();
	AI_S.Draw();
	ItemManager::Instance()->Draw();
	Engine::FinishDrawing();
}


