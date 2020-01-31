#pragma once
#include "Enemy.h"
#include "PoisonShot.h"
class CEnemyPoison :
	public CEnemy
{
private:
	bool m_bDmg;
	Vector2 m_DmgScale;
	bool m_bAttack;
	CTexturePtr				m_pPoisonTexture;
	CSpriteMotionController m_PoisonMotion;
	Vector2 m_PoisonPos;
	CDynamicArray<CShot*>	m_ShotArray;
public:
	CEnemyPoison(void);
	virtual ~CEnemyPoison(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void RenderCircle(const Vector2& screenPos) override;
	void Move(void) override;
	void Animation(void) override;
	CRectangle GetRect(void) override;
	CRectangle GetSrcAddRect(void) override;
	bool Dmg(const int& dmg) override;
	bool OverValue(CRectangle rec, Vector2& out) override;
	bool IsDmg(void) const { return m_bDmg; }
	void SetDead(const bool& b) override;
};

