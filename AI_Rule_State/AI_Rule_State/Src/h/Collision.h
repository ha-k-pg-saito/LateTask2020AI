#ifndef COLLISION_H
#define COLLISION_H

#include"../Engine/Engine.h"

class Collision
{
public:
	Collision();
	~Collision();

public:
	//â~Ç∆â~ÇÃìñÇΩÇËîªíË
	bool OnCollisionCircleAndCircle(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos, Vec2 obj2_size);
	//ì_Ç∆êÓÇÃìñÇΩÇËîªíË
	bool OnCollisionArcAndPoint(Vec2 fan_pos, Vec2 point_pos, float arc_Degree, float rotate_Degree, float lengh, Vec2 itemSize);

public:
	const Vec2 ItemSize = Vec2(20.f, 20.f);
	const Vec2 AiSize = Vec2(50.f, 50.f);
};

#endif // !COLLISION_H

