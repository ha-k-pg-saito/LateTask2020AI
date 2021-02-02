#ifndef STATEBASEAI_H
#define STATEBASEAI_H

#include "../Engine/Engine.h"
#include "Collision.h"

class AI_State
{
public:
	AI_State();
	~AI_State();
	void Update();
	void Draw();

private:
	void Wait();
	void Move();
	//アイテム回収行動
	void MoveToItem();

public:
	Vec2 Pos;

private:
	float Speed;
	float Angle;//角度
	int Timer;
	int Step;
	 

	Vec2 Direction;//移動時に使う向き

	int ItemNumber;//発見したアイテムの番号
	//扇の長さ
	const float Fan_Lengh = 150.f;
	//扇の角度
	const float FanDegree = 90.f;

	const int Supplement = 25.f;

	Collision collision;
};

#endif // !STATEBASEAI_H
