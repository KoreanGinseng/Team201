/**
 * @file Enemy_BAT.h
 * @brief 蝙蝠の動き
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"EnemyMove.h"

class CENEMY_BAT :public CEnemyMove {
private:
	float	m_TurnLeft;
	float	m_TurnRight;

	enum BAT_ANIM
	{
		BAT_MOVE,
		BAT_DOWN,
		BAT_ANIMCOUNT,
	};
public:
	CENEMY_BAT();
	~CENEMY_BAT();
	void Initialize();
	void Update(float Xpos, float Ypos);
	CRectangle	GetRect(void) const {
		CRectangle rect(m_fXpos, m_fYpos, m_fXpos + m_SrcRect.GetWidth(), m_fYpos + m_SrcRect.GetHeight());
		rect.Expansion(-6, -6);
		rect.Top += 12;
		return rect;
	}
};
