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
	void SetStatus(const int& n) { m_Status = n; }
	int  GetObjType(void) const { return m_Type; }
};

