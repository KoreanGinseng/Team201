#pragma once
#include	"Mof.h"

class CCamera2D {
private:
	Vector2 m_Pos;
public:
	CCamera2D();
	~CCamera2D() {}

	Vector2 GetScroll() { return m_Pos; }

	void AddScroll(Vector2 scroll) { m_Pos += scroll; }

};