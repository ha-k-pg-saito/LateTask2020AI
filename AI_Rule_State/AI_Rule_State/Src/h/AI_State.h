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
	//�A�C�e������s��
	void MoveToItem();

public:
	Vec2 Pos;

private:
	float Speed;
	float Angle;//�p�x
	int Timer;
	int Step;
	 

	Vec2 Direction;//�ړ����Ɏg������

	int ItemNumber;//���������A�C�e���̔ԍ�
	//��̒���
	const float Fan_Lengh = 150.f;
	//��̊p�x
	const float FanDegree = 90.f;

	const int Supplement = 25.f;

	Collision collision;
};

#endif // !STATEBASEAI_H
