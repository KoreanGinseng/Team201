#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Substance.h"
#include	"_Onishi/EnemyMove.h"
#include	"_Onishi/EnemyAtack.h"


//当たり判定減衰幅
#define		ENEMY_RECTDECREASE		10

class CEnemy : public CSubstance
{
private:
	CTexturePtr				m_pTexture;
	bool					m_bShow;
	CEnemyMove*				m_pMove;
	CEnemyAtack*			m_pAttack;
	int						m_HP;
	int						m_StopWait;
	int						m_StopWaitOffset;
	int						m_DamageWait;
	int						m_Type;

	//モーション種類定義
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

	void MotionCreate(std::shared_ptr<CAnimationData> m) { m_pMove->MotionCreate(m); }

	//Set
	void SetTexture(CTexturePtr pt) { m_pTexture = pt; }
	void SetMoveAttack(const int& no);

	//Collision
	void CollisionStage(Vector2 o);
	bool Collision(CRectangle r, Vector2& o);
	void Damage(int dmg,bool bRev);
	
	//Get
	bool		GetShow(void)			const { return m_bShow; }
	int			GetDamageWait(void)		const { return m_DamageWait; }
	//CRectangle  GetRect(void)			const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }
	CRectangle  GetRect(void)			const { return m_pMove->GetRect(); }
	int			GetType(void)			const { return m_Type; }
};