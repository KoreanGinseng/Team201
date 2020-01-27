#pragma once
#include "TargetObj.h"
class CMoveFloor :
	public CTargetObj
{
private:
	float	m_BackPos;
	float	m_NomalPos;
	float	m_TripPos;
	bool	m_bChange;
	int		m_PrevSubStatus;
	int		m_ColorType;
	int		m_RectType;
public:
	CMoveFloor(void);
	~CMoveFloor(void);
	void Initialize(void) override;
	void Update(void) override;
	void SetColorType(const int& t);
	void SetRectType(const int& t);
	bool OverValue(CRectangle rec, Vector2 & out) override;
};

