#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Substance.h"


//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECTDECREASE		10

class CEnemy : public CSubstance {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	/*float					m_PosX;
	float					m_PosY;*/
	float					m_MoveX;
	float					m_MoveY;
	//bool					m_bShow;
	bool					m_bReverse;
	/*CRectangle				m_SrcRect;*/
	
	int						m_HP;
	int						m_DamageWait;
	
	//ÉÇÅ[ÉVÉáÉìéÌóﬁíËã`
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};

	MofU32					m_DebugColor;
public:
	CEnemy();
	~CEnemy();
	void Initialize(float px,float py,int type);
	void Update(void);
	void Render(Vector2 sp);
	void RenderDebug(Vector2 sp);
	void Release(void);

	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	
	void CollisionStage(Vector2 o);
	void Damage(int dmg,bool bRev);
	
	bool GetShow(void){ return m_bShow; }
	Vector2 GetPos() { return Vector2(m_PosX, m_PosY); }
	int GetDamageWait(void){ return m_DamageWait; }
	/*CRectangle GetRect(){
		return CRectangle(m_PosX + ENEMY_RECTDECREASE,m_PosY + ENEMY_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}*/

	void TestSetColor(void) { m_DebugColor = MOF_COLOR_GREEN; }
	void Debug(void);
	
};