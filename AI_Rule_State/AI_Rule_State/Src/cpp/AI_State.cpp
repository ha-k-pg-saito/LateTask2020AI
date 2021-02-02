#include <time.h>
#include <math.h>
#include"../h/AI_State.h"
#include"../h/Item.h"

AI_State::AI_State()
{
	Pos = Vec2(25.f, 200.f);

	Speed = 1.f;
	Angle = 180.f;
	Timer = 0;
	Step = 0;

	Direction = Vec2(0.f, 0.f);

	ItemNumber = 0;

	srand((unsigned int)time(NULL));
}
AI_State::~AI_State()
{

}

void AI_State::Update()
{
	switch (Step)
	{
	case 0: Wait();     break;
	case 1: Move();     break;
	case 2: MoveToItem(); break;
	default:            break;
	}
}

void AI_State::Draw()
{
	Vec2 Center_Pos = Vec2(Pos.X + Supplement, Pos.Y + Supplement);

	Engine::DrawTexture(Pos.X, Pos.Y, "Enemy", 255, 0.f, 1.f, 1.f);
	//扇
	Engine::DrawFan(Center_Pos, FanDegree, Fan_Lengh, Angle, 0x9000ff00);
}

//待機
void AI_State::Wait()
{
	++Timer;
	if (Timer >= 120)
	{
		Step = 1;
		Timer = -1;
	}

	Vec2 CenterPos = Vec2(Pos.X + collision.AiSize.X / 2, Pos.Y + collision.AiSize.Y / 2);

	if (ItemManager::Instance()->Items[ItemNumber].IsActive == true)
	{
		//扇の探索判定
		for (int i = 0; i < 5; i++)
		{
			if (collision.OnCollisionArcAndPoint(
				CenterPos,
				ItemManager::Instance()->Items[i].Pos,
				FanDegree,
				Angle,
				Fan_Lengh,
				collision.ItemSize) == true)
			{
				ItemNumber = i;
				Step = 2;
				break;
			}
		}
	}
}
//移動
void AI_State::Move()
{
	++Timer;

	if (Timer == 0)
	{
		//角度
		Angle = rand() % 360;

		//ラジアン変換
		float rad = Angle * 3.14 / 180;

		Direction = Vec2(cosf(rad), sinf(rad));
	}
	//移動
	Pos.X += Direction.X * Speed;
	Pos.Y += Direction.Y * Speed;

	//画面外にいかなくする
	if (Pos.X < 0.f)
	{
		Pos.X = 0.f;
	}
	if (Pos.X > 592.f)
	{
		Pos.X = 592.f;
	}
	if (Pos.Y < 0.f)
	{
		Pos.Y = 0.f;
	}
	if (Pos.Y > 432.f)
	{
		Pos.Y = 432.f;
	}

	if (Timer >= 180)
	{
		Timer = 0;
		Step = 0;
	}

	Vec2 CenterPos = Vec2(Pos.X + collision.AiSize.X / 2, Pos.Y + collision.AiSize.Y / 2);

	//扇の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionArcAndPoint(
			CenterPos,
			ItemManager::Instance()->Items[i].Pos,
			FanDegree,
			Angle,
			Fan_Lengh,
			collision.ItemSize) == true)
		{
			ItemNumber = i;
			Step = 2;
			break;
		}
	}
}

void AI_State::MoveToItem()
{
	//ベクトルの算出
	Vec2 Vector =
		Vec2((ItemManager::Instance()->Items[ItemNumber].Pos.X + collision.ItemSize.X / 2.0f) - (Pos.X + collision.AiSize.X / 2.0f),
			(ItemManager::Instance()->Items[ItemNumber].Pos.Y + collision.ItemSize.Y / 2.0f) - (Pos.Y + collision.AiSize.Y / 2.0f));

	//単位ベクトルの算出
	float Length = sqrtf(Vector.X * Vector.X + Vector.Y * Vector.Y);
	Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);

	Pos.X += Normal.X * Speed;
	Pos.Y += Normal.Y * Speed;

	//距離
	Vec2 Distance = Vec2(ItemManager::Instance()->Items[ItemNumber].Pos.X - Pos.X,
		ItemManager::Instance()->Items[ItemNumber].Pos.Y - Pos.Y);

	//向いている角度
	Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
	if (Vector.X < 0)
	{
		Angle += 180;
	}

	//移動終了
	if (ItemManager::Instance()->Items[ItemNumber].IsActive == false)
	{
		Timer = -1;
		Step = 0;
	}
}