#pragma once
#include "Substance.h"
class CTargetObj :
	public CSubstance
{
protected:
	int		m_Type;
	int		m_Status;
public:
	CTargetObj();
	~CTargetObj();
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	//void SetType(const int& n);
	void SetStatus(const int& n);
	int  GetObjType(void) const { return m_Type; }
	virtual bool OverValue(CRectangle rec, Vector2 & out) override;
};

