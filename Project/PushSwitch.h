#pragma once
#include "TargetObj.h"
class CPushSwitch :
	public CTargetObj
{
private:
	CTexturePtr m_pSuittiTexture;
	Vector2 m_SuittiPos;
	int		m_Way;
	bool	m_bOnPlayer;
	Vector2 m_OffsetPos;
	float	m_OnMoveY;
public:
	CPushSwitch(void);
	virtual ~CPushSwitch(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	CRectangle GetRect(void) override;
	bool OverValue(CRectangle rec, Vector2& out) override;
	int GetWay(void) const;
	void SetOnPlayer(const bool& b);
};

