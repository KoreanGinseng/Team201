#pragma once
#include "TargetObj.h"
class CCameraCntrl :
	public CTargetObj
{
private:
	CDynamicArray<CameraCntrlData> m_CntrlLists;
	bool	m_bCntrl;
public:
	CCameraCntrl(void);
	virtual ~CCameraCntrl(void);
	void Update(void) override;
	bool IsCntrl(void) const { return m_bCntrl; }
};

