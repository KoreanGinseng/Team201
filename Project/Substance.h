#pragma once


#include		"Mof.h"
#include		"Character.h"

class CSubstance : public CCharacter {
protected:
	int						m_SubType;
	int						m_SubStatus;
	bool					m_bSelectTarget;
	bool					m_bTarget;
public:
	CSubstance() : CCharacter() {
		m_SubType = -1;
		m_SubStatus = SUBSTATUS_NOMAL;
		m_bTarget = false, m_bSelectTarget = true;
	}
	virtual ~CSubstance() {}
	void	SetTarget(const bool& target) { m_bTarget = target; }
	void	Stop(void) {

	}
	void	Back(void) {
		if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_BACK)
		{
			m_SubStatus = (m_SubStatus == SUBSTATUS_NOMAL) ? SUBSTATUS_BACK : SUBSTATUS_NOMAL;
		}
	}
	void	Trip(void) {
		if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_TRIP)
		{
			m_SubStatus = (m_SubStatus == SUBSTATUS_NOMAL) ? SUBSTATUS_BACK : SUBSTATUS_NOMAL;
		}
	}
	virtual	void	Initialize(void) override = 0;
	virtual	void	Update(void) override = 0;
	int		GetStatus(void) const { return m_SubStatus; }
	bool	IsSelectTarget(void) const { return m_bSelectTarget; }
};