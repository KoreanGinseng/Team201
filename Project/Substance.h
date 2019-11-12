#pragma once


#include		"Mof.h"

class CSubstance {

protected:
	Vector2					m_Pos;
	bool					m_bShow;
	bool					m_bTarget;
	bool					m_bSkill;
	bool					m_bStop;
	bool					m_bBack;
	bool					m_bTrip;
	CRectangle				m_SrcRect;

public:
	CSubstance() { m_bShow = false, m_bTarget = false, m_bSkill = false,
				   m_bStop = false,m_bBack = false,m_bTrip = false; }
	virtual ~CSubstance() {}
	void	SetTarget(bool target) { m_bTarget = target; }
	void	SetSkill(void) { m_bSkill = true; }
	void	SetStop(void) { m_bStop = true; }
	void	SetBack(void) { m_bBack = true; }
	void	SetTrip(void) { m_bTrip = true; }
	virtual CRectangle GetRect() const = 0; /*{ return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }*/
	bool	IsSkill(void) { return m_bSkill; }
	bool	IsStop(void) { return m_bStop; }
	bool	IsBack(void) { return m_bBack; }
	bool	IsTrip(void) { return m_bTrip; }
	Vector2 GetPos(void) const { return m_Pos; }

};