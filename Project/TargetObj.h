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
	void Update(void) override;
	void SetType(const int& n);
	void SetStatus(const int& n);
	int  GetObjType(void) const { return m_Type; }
	bool OverValue(CRectangle rec, Vector2 & out) override;
private:
	bool CollisionRope(CRectangle rec);
	bool CollisionTree(CRectangle rec, Vector2 & out);
	bool CollisionBridge(CRectangle rec, Vector2 & out);
};

