#pragma once
#include	"EnemyMove.h"

class CENEMY_NOKONOKO :public CEnemyMove {
private:
	float m_fTimer;
public:
	CENEMY_NOKONOKO();
	~CENEMY_NOKONOKO();
	void Initialize();
	void Update(float Xpos, float Ypos);
	CRectangle	GetRect(void) const {
		CRectangle rect(m_fXpos, m_fYpos, m_fXpos + m_SrcRect.GetWidth(), m_fYpos + m_SrcRect.GetHeight());
		return rect;
	}
};
