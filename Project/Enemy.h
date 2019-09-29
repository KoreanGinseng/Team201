#pragma once

#include	"Mof.h"
#include	"GameDefine.h"


//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECTDECREASE		10

class CEnemy {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	Vector2					m_Pos;
	Vector2					m_Move;
	bool					m_bShow;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	
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
	void Initialize(float px,float py,int type);
	void Update(void);
	void Render(const Vector2& sp);
	void RenderDebug(const Vector2& sp);
	void Release(void);

	//Set
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	
	//Collision
	void CollisionStage(Vector2 o);
	void Damage(int dmg,bool bRev);
	
	//Get
	bool		GetShow(void)			const { return m_bShow; }
	Vector2		GetPos(void)			const { return m_Pos; }
	int			GetDamageWait(void)		const { return m_DamageWait; }
	CRectangle	GetRect(void)			const {
		return CRectangle(m_Pos.x + ENEMY_RECTDECREASE, m_Pos.y + ENEMY_RECTDECREASE,
			m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}
};