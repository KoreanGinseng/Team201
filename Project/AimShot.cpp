#include "AimShot.h"



CAimShot::CAimShot(void) :
CShot()
{
}


CAimShot::~CAimShot(void)
{
}

void CAimShot::Fire(const Vector2 & startPos)
{
	m_Pos = startPos;
	Vector2 d = Vector2(
		CCordinate::GetPlayerPos().x + 192 * 0.5f,
		CCordinate::GetPlayerPos().y + 192 * 0.5f)
		- m_Pos;
	float fd = sqrtf(d.x * d.x + d.y * d.y);
	Vector2 dd = d / fd;
	m_Spd = Vector2(12, 12);
	m_Move = dd * m_Spd;
	m_RotateRad = atan2f(d.y, d.x);
}

void CAimShot::Update(void)
{
}

void CAimShot::Render(const Vector2 & screenPos)
{
}
