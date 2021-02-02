#ifndef AI_Rule_h_
#define AI_Rule_h_

#include"../Engine/Engine.h"
#include"Item.h"
#include"Collision.h"

//enum class=>整数型への暗黙の型変換をしない
enum class Rule
{
	HitFanArea,
	HitCircleArea,
	Non
};

class AI_Rule
{
public:
	AI_Rule();		//コンストラクタ
	~AI_Rule();		//デストラクタ
	void Update();
	void Draw();

private:
	void Wait();
	void Move();

	Rule OnOff();

public:
	Vec2 m_Position;

private:
	float Speed;							//スピード
	float Angle;							//角度
	int Timer;								//タイマー	
	int Step;

	int Item_Number;						//アイテムの番号
	int Fan_Item_Number;					//扇内のアイテムの番号
	int Circle_Item_Number;					//円内のアイテムの番号
	Vec2 Direction;
	Rule Now_Rules;
	
	bool Hit_Fan;							//扇に当たっている
	bool Hit_Circle;						//円に当たっている
	Rule Hit_Last_Time;

	const float Fan_Lengh = 200.f;			//扇の長さ
	const float Fan_Degree = 30.f;			//角度
	const float Circle_Radius = 50.f;		//円の半径

	Collision collision;

	Vec2 ItemsPos[5];

};
#endif

