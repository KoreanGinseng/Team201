#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Substance.h"
#include	"_Onishi/EnemyMove.h"
#include	"_Onishi/EnemyAtack.h"
#include	"_Onishi/Enemy_BAT.h"
#include	"_Onishi/Enemy_KOTEIHOUDAI.h"
#include	"_Onishi/Enemy_KURIBO.h"
#include	"_Onishi/Enemy_TERESA.h"
#include	"_Onishi/Enemy_NOKONOKO.h"


//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECTDECREASE		10

class CEnemy : public CSubstance
{
private:
	CTexturePtr				m_pTexture;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	CEnemyMove*				m_pMove;
	CEnemyAtack*			m_pAttack;
	int						m_HP;
	int						m_DamageWait;
	
	//ÉÇÅ[ÉVÉáÉìéÌóﬁíËã`
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};

public:
	CEnemy();
	~CEnemy();
	void Initialize(float px,float py);
	void Update(const Vector2& playerPos);
	void Render(const Vector2& sp);
	void RenderDebug(const Vector2& sp);
	void Release(void);

	//Set
	void SetTexture(CTexturePtr pt) { m_pTexture = pt; }
	void SetMoveAttack(const int& no);

	//Collision
	void CollisionStage(Vector2 o);
	void Damage(int dmg,bool bRev);
	
	//Get
	bool		GetShow(void)			const { return m_bShow; }
	int			GetDamageWait(void)		const { return m_DamageWait; }
};