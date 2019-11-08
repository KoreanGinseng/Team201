/**
 * @file EnemyMove.h
 * @brief “G‚Ì“®‚«
 * @author ‘å¼‰i‰“
 * @date XV“úi11/8j
 */
#pragma once
#include	"Mof.h"
#include	"EnemyAtack.h"
#include	"..\EnemyDefine.h"





class CEnemyMove {
protected:
	bool m_bEnd;
	bool m_bRevers;
	float m_fXpos;
	float m_fYpos;
	float m_fMoveX;
	float m_fMoveY;
	float m_fEnemySpeed;

private:
	
	float m_fAtackTimer;
	float m_fCooltime;
	CEnemyAtack*	m_Atack;
	//CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	//CTexture	m_Texture;
public:
	CEnemyMove();
	~CEnemyMove();
	virtual void Initialize() = 0;
	virtual void Update(float Xpos, float Ypos) = 0;
	virtual void Render(float Xpos, float Ypos) = 0;
	virtual void Release()=0;
	void CollisionStage(float ox, float oy, int Type);
	/*virtual void Initialize(int Type) = 0;
	virtual void Update(float Xpos, float Ypos, int Type) = 0;
	virtual void Render(float Xpos, float Ypos, int Type) = 0;*/
	float GetXpos(void) { return m_fXpos; };
	float GetYpos(void) { return m_fYpos; };
	bool getRevers(void) { return m_bRevers; }

	void KUpdate(float Xpos,float Ypos);
	void NUpdate(void);
	void TUpdate(float Xpos, float Ypos);
	void BUpdate(float Xpos, float Ypos);
	void KOUpdate(void);
	bool GetDead() { return m_bEnd; }
	void Gravity() {
		m_fMoveY += GRAVITY;
		if (m_fMoveY >= 20.0f) {
			m_fMoveY = 20.0f;
		}
	}
	void AtackRange(float Xpos, float Ypos){
		if (m_fYpos - 50 < Ypos&&m_fYpos + 10 > Ypos) {
			if (m_bRevers) {
				if (m_fXpos + 50 > Xpos&&m_fXpos < Xpos) {
					m_fMoveX = 0;
					return ;
				}
			}
			else {
				if (m_fXpos - 50 < Xpos&&m_fXpos > Xpos) {
					m_fMoveX = 0;
					return ;
				}
			}
		}
	}
};








