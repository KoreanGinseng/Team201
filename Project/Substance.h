#pragma once


#include		"Mof.h"

class CSubstance {

protected:
	float					m_PosX;
	float					m_PosY;
	bool					m_bShow;
	bool					m_bTarget;
	bool					m_bSkill;
	CRectangle				m_SrcRect;

public:
	CSubstance() { m_bShow = false, m_bTarget = false, m_bSkill = false; }
	/*virtual */~CSubstance() {}/* = 0*/;
	void	SetTarget(bool target) { m_bTarget = target; }
	void	SetSkill(void) { m_bSkill = true; }
	CRectangle GetRect() const { return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()); }
	bool	IsSkill(void) { return m_bSkill; }

};