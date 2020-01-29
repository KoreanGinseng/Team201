#pragma once
#include "Shot.h"
class CRayShot :
	public CShot
{
private:
	Vector2	m_RefrectPos[3];
	float	m_RefrectRad[3];
	int		m_Timer;
	float	m_Scale[2];
	float	m_ScaleY;
	bool	m_bShot2;
	bool	m_bShot3;
	int		m_TempCount;
	CDynamicArray<CCircle> m_ColCirArray;
public:
	CRayShot(void);
	virtual ~CRayShot(void);
	virtual void Fire(const Vector2& startPos) override;
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
	CDynamicArray<CCircle>* GetShotCircle(void);
	virtual bool OverValue(CRectangle rect, Vector2& out) override;
	void Refrect(const Vector2& pos);
	void FireStop(void);
	int GetTempCount(void) const;
	bool IsRef(void) const;
};

