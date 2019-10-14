#pragma once


#include		"Mof.h"

class CSubstance {

protected:
	Vector2					m_Pos;
	bool					m_bShow;
	bool					m_bTarget;
	bool					m_bSkill;
	CRectangle				m_SrcRect;

public:
	CSubstance() { m_bShow = false, m_bTarget = false, m_bSkill = false; }
	virtual ~CSubstance() {}
	void	SetTarget(bool target) { m_bTarget = target; }
	void	SetSkill(void) { m_bSkill = true; }
	CRectangle GetRect() const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }
	bool	IsSkill(void) { return m_bSkill; }
	Vector2 GetPos(void) const { return m_Pos; }

};