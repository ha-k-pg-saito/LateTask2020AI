#ifndef AI_Rule_h_
#define AI_Rule_h_

#include"../Engine/Engine.h"
#include"Item.h"
#include"Collision.h"

//enum class=>�����^�ւ̈Öق̌^�ϊ������Ȃ�
enum class Rule
{
	HitFanArea,
	HitCircleArea,
	Non
};

class AI_Rule
{
public:
	AI_Rule();		//�R���X�g���N�^
	~AI_Rule();		//�f�X�g���N�^
	void Update();
	void Draw();

private:
	void Wait();
	void Move();

	Rule OnOff();

public:
	Vec2 m_Position;

private:
	float Speed;							//�X�s�[�h
	float Angle;							//�p�x
	int Timer;								//�^�C�}�[	
	int Step;

	int Item_Number;						//�A�C�e���̔ԍ�
	int Fan_Item_Number;					//����̃A�C�e���̔ԍ�
	int Circle_Item_Number;					//�~���̃A�C�e���̔ԍ�
	Vec2 Direction;
	Rule Now_Rules;
	
	bool Hit_Fan;							//��ɓ������Ă���
	bool Hit_Circle;						//�~�ɓ������Ă���
	Rule Hit_Last_Time;

	const float Fan_Lengh = 200.f;			//��̒���
	const float Fan_Degree = 30.f;			//�p�x
	const float Circle_Radius = 50.f;		//�~�̔��a

	Collision collision;

	Vec2 ItemsPos[5];

};
#endif

