#include"../h/Collision.h"

Collision::Collision()
{

}
Collision::~Collision()
{

}

//�~�Ɖ~�̂����蔻��
bool Collision::OnCollisionCircleAndCircle(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos, Vec2 obj2_size)
{
	//����
	Vec2 center_pos[] =
	{
		Vec2(obj1_pos.X + obj1_size.X / 2.f,obj1_pos.Y + obj1_size.Y / 2.f),
		Vec2(obj2_pos.X + obj2_size.X / 2.f,obj2_pos.Y + obj2_size.Y / 2.f),
	};

	//���a
	float obj1_radius = obj1_size.X / 2;
	float obj2_radius = obj2_size.Y / 2;

	//����
	float a = center_pos[0].X - center_pos[1].X;
	float b = center_pos[0].Y - center_pos[1].Y;
	float c = sqrt(a * a + b * b);

	//����
	if (c <= obj1_radius + obj2_radius)
	{
		//�������Ă�
		return true;
	}
	//�������ĂȂ�
	return false;
}

//��Ɠ_�̂����蔻��
bool Collision::OnCollisionArcAndPoint(Vec2 arc_pos, Vec2 item_pos, float arc_degree, float rotate_degree, float lengh, Vec2 itemSize)
{
	Vec2 pointPos = Vec2(item_pos.X + ItemSize.X / 2, item_pos.Y + ItemSize.Y / 2);

	//����
	float x = arc_pos.X - pointPos.X;
	float y = arc_pos.Y - pointPos.Y;
	float c = sqrt(x * x + y * y);

	//�~�͈͓̔����̔���
	if (lengh < c)
	{
		return false;
	}

	//��^�J�n���̊p�x
	float start_Rad = D3DXToRadian(rotate_degree - arc_degree / 2);
	//��^�I�����̊p�x
	float end_Rad = D3DXToRadian(rotate_degree + arc_degree / 2);

	//���ꂼ���sin,cos�ϊ�=>sin,cos��double�^�̂���(float)�����Č^�ϊ�
	float start_x = (float)sin(start_Rad);
	float start_y = (float)cos(start_Rad);
	float end_x = (float)sin(end_Rad);
	float end_y = (float)cos(end_Rad);

	//�p�x�̔���
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