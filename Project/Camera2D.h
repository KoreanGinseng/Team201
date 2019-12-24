/*****************************************************************
 *	@file			Camera2D.h
 *	@brief			2DƒJƒƒ‰ƒNƒ‰ƒX
 *	@author			ˆäãéD‹R
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"

class CCamera2D {
private:
	Vector2 m_Pos;
	static Vector2 m_sPos;
public:
	CCamera2D();
	~CCamera2D() {}
	void Update(const Vector2& centerPos, const CRectangle& prec, const CRectangle& srec);

	void AddScroll(const Vector2& scroll) { m_Pos += scroll; }

	//Get
	Vector2 GetScroll() const { return m_Pos; }
	CRectangle GetRect() const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + g_pGraphics->GetTargetWidth(), m_Pos.y + g_pGraphics->GetTargetHeight()); }
	static Vector2 GetSScroll() { return m_sPos; }
	//Set
	void SetScrollX(const float& x) { m_Pos.x = x; }
	void SetScrollY(const float& y) { m_Pos.y = y; }
};