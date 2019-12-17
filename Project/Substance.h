#pragma once


#include		"Mof.h"
#include		"Character.h"

class CSubstance : public CCharacter {
protected:
	int						m_SubType;
	bool					m_bSelectTarget;
	bool					m_bTarget;
	bool					m_bStop;
	bool					m_bBack;
	bool					m_bTrip;
public:
	CSubstance() : CCharacter() {
		m_SubType = -1;
		m_bTarget = false, m_bSelectTarget = true;
		m_bStop = false, m_bBack = false, m_bTrip = false;
	}
	virtual ~CSubstance() {}
	void	SetTarget(const bool& target) { m_bTarget = target; }
	void	Stop(void) {
		m_bStop = true;
	}
	void	Back(void) {
		if (m_SubType != SUB_ENE)
		{
			m_bBack = true;
		}
	}
	void	Trip(void) {
		if (m_SubType != SUB_ENE)
		{
			m_bTrip = true;
		}
	}
	virtual	void	Initialize(void) override = 0;
	virtual	void	Update(void) override = 0;
	bool	IsStop(void) const { return m_bStop; }
	bool	IsBack(void) const { return m_bBack; }
	bool	IsTrip(void) const { return m_bTrip; }
	bool	IsSelectTarget(void) const { return m_bSelectTarget; }
};