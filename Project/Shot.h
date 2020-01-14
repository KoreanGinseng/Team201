#pragma once
#include	"GameDefine.h"
#include	"Substance.h"

class CShot : public CSubstance
{
private:
protected:
	bool	m_bShot;
public:
	CShot(void);
	virtual ~CShot(void);
	virtual void Fire(const Vector2& startPos) = 0;
	bool	IsShot(void) const;
	void	SetShot(const bool& b);
};

