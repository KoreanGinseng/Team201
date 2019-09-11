#pragma once
#include	"Mof.h"

class CCamera2D {
private:
	Vector2 m_Pos;
public:
	CCamera2D();
	~CCamera2D() {}

	Vector2 GetScroll() { return m_Pos; }
	CRectangle GetCameraRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + g_pGraphics->GetTargetWidth(), m_Pos.y + g_pGraphics->GetTargetHeight()); }

	void AddScroll(Vector2 scroll) { m_Pos += scroll; }

	void SetScrollX(float x) { m_Pos.x = x; }
	void SetScrollY(float y) { m_Pos.y = y; }
};