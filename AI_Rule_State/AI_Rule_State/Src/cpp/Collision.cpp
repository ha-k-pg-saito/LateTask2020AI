#include"../h/Collision.h"

Collision::Collision()
{

}
Collision::~Collision()
{

}

//円と円のあたり判定
bool Collision::OnCollisionCircleAndCircle(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos, Vec2 obj2_size)
{
	//中央
	Vec2 center_pos[] =
	{
		Vec2(obj1_pos.X + obj1_size.X / 2.f,obj1_pos.Y + obj1_size.Y / 2.f),
		Vec2(obj2_pos.X + obj2_size.X / 2.f,obj2_pos.Y + obj2_size.Y / 2.f),
	};

	//半径
	float obj1_radius = obj1_size.X / 2;
	float obj2_radius = obj2_size.Y / 2;

	//距離
	float a = center_pos[0].X - center_pos[1].X;
	float b = center_pos[0].Y - center_pos[1].Y;
	float c = sqrt(a * a + b * b);

	//判定
	if (c <= obj1_radius + obj2_radius)
	{
		//当たってる
		return true;
	}
	//当たってない
	return false;
}

//扇と点のあたり判定
bool Collision::OnCollisionArcAndPoint(Vec2 arc_pos, Vec2 item_pos, float arc_degree, float rotate_degree, float lengh, Vec2 itemSize)
{
	Vec2 pointPos = Vec2(item_pos.X + ItemSize.X / 2, item_pos.Y + ItemSize.Y / 2);

	//距離
	float x = arc_pos.X - pointPos.X;
	float y = arc_pos.Y - pointPos.Y;
	float c = sqrt(x * x + y * y);

	//円の範囲内かの判定
	if (lengh < c)
	{
		return false;
	}

	//扇型開始線の角度
	float start_Rad = D3DXToRadian(rotate_degree - arc_degree / 2);
	//扇型終了線の角度
	float end_Rad = D3DXToRadian(rotate_degree + arc_degree / 2);

	//それぞれのsin,cos変換=>sin,cosがdouble型のため(float)をつけて型変換
	float start_x = (float)sin(start_Rad);
	float start_y = (float)cos(start_Rad);
	float end_x = (float)sin(end_Rad);
	float end_y = (float)cos(end_Rad);

	//角度の判定
	if (start_x * end_y - end_x * start_y > 0)
	{
		if (start_x * y - x * start_y < 0) return false;
		if (end_x * y - x * end_y > 0) return false;
		return true;
	}
	else 
	{
		if (start_x * y - x * start_y > 0) return true;
		if (end_x * y - x * end_y < 0) return true;
		return false;
	}
}