#include <time.h>
#include <math.h>
#include"../h/AI_Rule.h"

AI_Rule::AI_Rule()
{
	m_Position = Vec2(350.f, 200.f);

	Speed = 1.f;
	Angle = 0.f;
	Timer = 0;
	Step = 0;

	Direction = Vec2(0.f, 0.f);
	Now_Rules = Rule::Non;
	Item_Number = 0;
	Fan_Item_Number = 0;
	Circle_Item_Number = 0;

	Hit_Fan = false;
	Hit_Circle = false;
	Hit_Last_Time = Rule::Non;
}
AI_Rule::~AI_Rule()
{

}

void AI_Rule::Update()
{
	switch (Step)
	{
	case 0:	Wait();	break;
	case 1:	Move();	break; 
	default:		break;
	}
}
void AI_Rule::Draw()
{
	Vec2 Center_Pos = Vec2(m_Position.X + collision.AiSize.X / 2, m_Position.Y + collision.AiSize.Y / 2);

	Engine::DrawFan(Center_Pos, 360.0f, Circle_Radius, Angle, 0xffff00ff);
	Engine::DrawFan(Center_Pos, Fan_Degree, Fan_Lengh, Angle, 0xffff0000);
	Engine::DrawTexture(m_Position.X, m_Position.Y, "Enemy", 255, 0.0f, 1.f, 1.f);
}

//待機
void AI_Rule::Wait()
{
	++Timer;
	if (Timer >= 120)
	{
		Now_Rules = Rule::Non;
		Hit_Fan = false;
		Hit_Circle = false;
		Timer = 298;
		Step = 1;
	}
}

//移動
void AI_Rule::Move()
{
	if (Now_Rules == Rule::Non)
	{
		Now_Rules = OnOff();

		++Timer;

		if (Timer >= 300)
		{
			Angle = rand() % 360;
			float rad = Angle * 3.14 / 180;
			Direction = Vec2(cosf(rad), sinf(rad));

			Timer = 0;
		}
		//移動
		m_Position.X += Direction.X * Speed;
		m_Position.Y += Direction.Y * Speed;

		//画面外にいかなくする
		if (m_Position.X < 0.f)
		{
			m_Position.X = 0.f;
		}
		if (m_Position.X > 600.f)
		{
			m_Position.X = 600.f;
		}
		if (m_Position.Y < 0.f)
		{
			m_Position.Y = 0.f;
		}
		if (m_Position.Y > 432.f)
		{
			m_Position.Y = 432.f;
		}
	}
	else if (Now_Rules == Rule::HitFanArea || Now_Rules == Rule::HitCircleArea)
	{
		//ベクトルの算出
		Vec2 Vector =
			Vec2((ItemManager::Instance()->Items[Item_Number].Pos.X + collision.ItemSize.X / 2.0f) - (m_Position.X + collision.AiSize.X / 2.0f),
				(ItemManager::Instance()->Items[Item_Number].Pos.Y + collision.ItemSize.Y / 2.0f) - (m_Position.Y + collision.AiSize.Y / 2.0f));
		//単位ベクトルの算出
		float Length = sqrtf(Vector.X * Vector.X + Vector.Y * Vector.Y);
		Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);

		//移動
		m_Position.X += Normal.X * Speed;
		m_Position.Y += Normal.Y * Speed;

		//移動終了
		if (ItemManager::Instance()->Items[Item_Number].IsActive == false)
		{
			Timer = 0;
			Step = 0;
		}

		//向いている角度
		Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			Angle += 180;
		}
	}
}

//ルール(オン・オフ法)
Rule AI_Rule::OnOff()
{
	//中心座標
	Vec2 Center_Position = Vec2(m_Position.X + collision.AiSize.X / 2, m_Position.Y + collision.AiSize.Y / 2);
	//円の座標
	Vec2 Circle_Position = Vec2(m_Position.X + collision.AiSize.X / 2.f - Circle_Radius,
		m_Position.Y + collision.AiSize.Y / 2.f - Circle_Radius);
	Vec2 CircleSize = Vec2(Circle_Radius * 2, Circle_Radius * 2);

	//扇の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionArcAndPoint(
			Center_Position,
			ItemManager::Instance()->Items[i].Pos,
			Fan_Degree,
			Angle,
			Fan_Lengh,
			collision.ItemSize) == true)
		{
			Fan_Item_Number = i;
			Hit_Fan = true;
			break;
		}
	}

	//円の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionCircleAndCircle(
			ItemManager::Instance()->Items[i].Pos,
			collision.ItemSize,
			Circle_Position,
			CircleSize) == true)
		{
			Circle_Item_Number = i;
			Hit_Circle = true;
			break;
		}
	}

	//OnOffで返す
	if (Hit_Fan == true && Hit_Circle == true)
	{
		if (Hit_Last_Time != Rule::HitFanArea)
		{
			Item_Number = Fan_Item_Number;
			Hit_Last_Time = Rule::HitFanArea;
			return Rule::HitFanArea;
		}
		else
		{
			Item_Number = Circle_Item_Number;
			Hit_Last_Time = Rule::HitCircleArea;
			return Rule::HitCircleArea;
		}
	}
	else if (Hit_Fan == true)
	{
		Item_Number = Fan_Item_Number;
		return Rule::HitFanArea;
	}
	else if (Hit_Circle == true)
	{
		Item_Number = Circle_Item_Number;
		return Rule::HitCircleArea;
	}

	return Rule::Non;
}