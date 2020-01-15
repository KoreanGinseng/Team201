#pragma once


#include		"Mof.h"
#include		"Character.h"

class CSubstance : public CCharacter {
protected:
	int						m_SubType;
	int						m_SubStatus;
	bool					m_bSelectTarget;
	bool					m_bTarget;
	bool					m_bAnimStop;
	int						m_WaitCount;
	int						m_OffsetWait;
public:
	CSubstance(void);
	virtual ~CSubstance(void) {}
	void	SetTarget(const bool& target) { m_bTarget = target; }
	void	Stop(void);
	void	Back(void);
	void	Trip(void);
	virtual	void	Initialize(void) override = 0;
	virtual	void	Update(void) override = 0;
	virtual void	Render(const Vector2& screenPos) override;
	int		GetStatus(void) const { return m_SubStatus; }
	bool	IsSelectTarget(void) const { return m_bSelectTarget; }
};