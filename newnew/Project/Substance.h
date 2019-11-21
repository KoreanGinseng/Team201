#pragma once


#include		"Mof.h"
#include		"Character.h"

class CSubstance : public CCharacter {

protected:
	bool					m_bTarget;
	bool					m_bSkill;
	bool					m_bStop;
	bool					m_bBack;
	bool					m_bTrip;

public:
	CSubstance() { m_bShow = false, m_bTarget = false,
		m_bStop = false, m_bBack = false, m_bTrip = false; m_bSkill = false; }
	virtual ~CSubstance() {}
	void	SetTarget(bool target) { m_bTarget = target; }
	void	SetSkill(void) { m_bSkill = true; }
	void	SetStop(void) { m_bStop = true; }
	void	SetBack(void) { m_bBack = true; }
	void	SetTrip(void) { m_bTrip = true; }
	bool	IsSkill(void) { return m_bSkill; }
	bool	IsStop(void) { return m_bStop; }
	bool	IsBack(void) { return m_bBack; }
	bool	IsTrip(void) { return m_bTrip; }

};