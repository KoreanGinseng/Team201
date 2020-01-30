#pragma once
#include "Enemy.h"
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
public:
	CEnemyBoss3(void);
	~CEnemyBoss3(void);
	virtual void CreateMotion(const char* pName) override;
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
};

