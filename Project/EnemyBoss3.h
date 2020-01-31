#pragma once
#include "Enemy.h"
#include "EnemyShot.h"
#include "SordShot.h"

class CEnemyBoss3 :
	public CEnemy
{
private:
	Vector2 m_HandPos1;
	Vector2 m_HandPos2;
	Vector2 m_MovePos1;
	Vector2 m_MovePos2;
	CTexturePtr m_pHandTexture1;
	CTexturePtr m_pHandTexture2;
	bool m_bMoveHand;

	CTexturePtr	m_pBossTexture;
	bool m_bBossChange;

	int m_StartTime;
	int	m_ChangeTime;
	int m_FlashAlpha;

	int m_AttackList[3];
	int m_AttackNo;
	bool m_bBossAttack;

	CSordShot m_SordShot;
	CEnemyShot m_EneShot;

	void AttackReset(void);

	void Attack(void);
public:
	CEnemyBoss3(void);
	~CEnemyBoss3(void);
	virtual void CreateMotion(const char* pName) override;
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
	virtual void RenderCircle(const Vector2& screenPos) override;
	CRectangle GetRect(void) override;
	CRectangle GetSrcAddRect(void) override;
};

