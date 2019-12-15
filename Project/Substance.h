#pragma once


#include		"Mof.h"
#include		"Character.h"

class CSubstance : public CCharacter {

protected:
	bool					m_bSelectTarget;
	bool					m_bTarget;
	bool					m_bSkill;
	bool					m_bStop;
	bool					m_bBack;
	bool					m_bTrip;
public:
	CSubstance() : CCharacter() {
		m_bShow = false, m_bTarget = false, m_bSelectTarget = true;
		m_bStop = false, m_bBack = false, m_bTrip = false; m_bSkill = false; }
	virtual ~CSubstance() {}
	void	SetTarget(const bool& target) { m_bTarget = target; }
	void	Stop(void) {
		m_bStop = b;
	}
	void	Back(void) {
		m_bBack = b;
	}
	void	Trip(void) {
		m_bTrip = b;
	}
	bool	IsStop(void) const { return m_bStop; }
	bool	IsBack(void) const { return m_bBack; }
	bool	IsTrip(void) const { return m_bTrip; }
	bool	IsSelectTarget(void) const { return m_bSelectTarget; }
};