#pragma once
#include "TargetObj.h"
class CCameraCntrl :
	public CTargetObj
{
private:
	bool	m_bCntrl;
	bool	m_bEndCntrl;
	int		m_MoveType;
public:
	CCameraCntrl(void);
	virtual ~CCameraCntrl(void);
	void Initialize(void) override;
	void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
	bool IsCntrl(void) const { return m_bCntrl; }
	bool IsEndCntrl(void) const { return m_bEndCntrl; }
	void SetEnd(const bool& b) { m_bEndCntrl = b; }
	int	 GetMoveType(void) const { return m_MoveType; }
};

