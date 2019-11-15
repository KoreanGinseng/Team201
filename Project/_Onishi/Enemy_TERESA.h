/**
 * @file Enemy_TERESA.h
 * @brief テレサ
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"EnemyMove.h"

class CENEMY_TERESA :public CEnemyMove {
private:
public:
	CENEMY_TERESA();
	~CENEMY_TERESA();
	void Initialize();
	void Update(float Xpos, float Ypos);
	CRectangle	GetRect(void) const {
		CRectangle rect(m_fXpos, m_fYpos, m_fXpos + m_SrcRect.GetWidth(), m_fYpos + m_SrcRect.GetHeight());
		rect.Expansion(-6, -6);
		return rect;
	}
};