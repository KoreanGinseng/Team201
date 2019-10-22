#pragma once
#include	"EnemyMove.h"
class CENEMY_KOTEIHOUDAI :public CEnemyMove {
private:
	float m_fAtackTimer;
	float m_fCooltime;
public:
	CENEMY_KOTEIHOUDAI();
	~CENEMY_KOTEIHOUDAI();
	void Initialize();
	void Update(float Xpos, float Ypos);
	CRectangle	GetRect(void) const {
		CRectangle rect(m_fXpos, m_fYpos, m_fXpos + m_SrcRect.GetWidth(), m_fYpos + m_SrcRect.GetHeight());
		rect.Expansion(-6, -6);
		return rect;
	}
};

