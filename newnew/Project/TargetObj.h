#pragma once
#include "Substance.h"
class CTargetObj :
	public CSubstance
{
private:
	int		m_Type;
	int		m_Status;
public:
	CTargetObj();
	~CTargetObj();
	void Initialize(void) override;
	void SetStatus(const int& n) { m_Status = n; m_Anim.ChangeAnim(m_Status); }
	int  GetObjType(void) const { return m_Type; }
};

