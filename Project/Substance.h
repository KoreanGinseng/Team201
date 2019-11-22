#pragma once


#include		"Mof.h"
#include		"GameDefine.h"

class CSubstance {

protected:
	Vector2					m_Pos;
	bool					m_bShow;
	bool					m_bTarget;
	//敵はストップのみ
	bool					m_bSkill;
	//オブジェクト等の状態
	int						m_Status;
	CRectangle				m_SrcRect;

	int						m_Type;

public:
	CSubstance() {
		m_bShow = false; m_bTarget = false; m_bSkill = false;
		m_Status = STATUS_STANDARD;
	}
	virtual ~CSubstance() {}
	void	SetTarget(bool target) { m_bTarget = target; }
	void	SetSkill(void) { m_bSkill = true; }
	void	SetStatus(const int& skillNo) {
		switch (m_Status)
		{
		case STATUS_BACK:
			if (skillNo != SKILL_BACK) {

				m_Status++;

			}
			break;
		case STATUS_STANDARD:
			if (skillNo == SKILL_BACK) {

				m_Status--;

			}
			else if (skillNo == SKILL_TRIP) {

				m_Status++;
			}
			break;
		case STATUS_TRIP:
			if (skillNo != SKILL_TRIP) {

				m_Status--;
			}

			break;
		} 
	}
	virtual CRectangle GetRect() const = 0; /*{ return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }*/
	bool	IsSkill(void) { return m_bSkill; }
	int		GetStatus(void) { return m_Status; }
	int		GetType(void) { return m_Type; }
	Vector2 GetPos(void) const { return m_Pos; }

};