#pragma once
#include "Enemy.h"
#include "AimShot.h"
class CEnemyOct :
	public CEnemy
{
private:
	CAimShot m_AimShot;
	CSpriteMotionController m_ShotMotion;
	CTexturePtr m_pShotTexture;
	bool		m_bShotEffect;
public:
	CEnemyOct(void);
	~CEnemyOct(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	CRectangle GetRect(void) override;
	CRectangle GetSrcAddRect(void) override;
};

