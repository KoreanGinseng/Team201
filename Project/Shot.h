#pragma once
#include	"GameDefine.h"
#include	"Substance.h"

class CShot : public CSubstance
{
private:
	static CDynamicArray<CShot*> m_ShotLists;
protected:
	bool	m_bShot;
public:
	CShot(void);
	virtual ~CShot(void);
	virtual void Fire(const Vector2& startPos) = 0;
	bool	IsShot(void) const;
	void	SetShot(const bool& b);
	virtual void	CollisionPlayer(const Vector2& over);
	virtual bool OverValue(CRectangle rect, Vector2& over) override;
	static CDynamicArray<CShot*>* GetShotLists(void);
};

