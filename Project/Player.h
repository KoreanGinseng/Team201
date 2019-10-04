/*****************************************************************
 *	@file			Player.h
 *	@brief			プレイヤークラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"
#include	"GameDefine.h"
#include	"GamePad.h"
#include	"SoundManager.h"

//DEFINE
#define		PLAYER_RECTDIS		40

class CPlayer
{
private:

	typedef enum tag_WAY {
		WAY_LEFT,
		WAY_RIGHT,
	}WAY;

	CTexturePtr m_pTexture;
	Vector2		m_Pos;
	Vector2		m_Move;
	Vector2		m_Spd;
	bool		m_bMove;
	bool		m_bReverse;
	bool		m_bJump;
	bool		m_bPowUp;
	bool		m_bTrigger;
	int			m_HP;
	int			m_Stock;
	CMotionPtr  m_pMotion;
	CRectangle  m_SrcRect;

	void PadOparation(void);
	void KeyOparation(void);

	void Move(void);
	void MoveAdd(WAY w);
	void MoveSub(WAY w);
	void Animation(void);
	void Jump(void);
	void Skill(void);
	void SkillColision(CEnemy* pene, int eneCount, CObject* pobj, int objCount);

	enum tag_Animation {
		ANIM_WAIT,
		ANIM_MOVE,

		ANIM_COUNT,
	};

public:
	CPlayer(void);
	~CPlayer(void);
	void Initialize(void);
	void Update(void);
	void Render(Vector2 screenPos);
	void RenderDebug(Vector2 screenPos);
	void Release(void);
	
	//Collision
	void CollisionStage(Vector2 o);

	//Get
	Vector2 GetPos(void) const { return m_Pos; }
	Vector2 GetSpd(void) const { return m_Spd; }
	CRectangle GetRect(void) const { return CRectangle(m_Pos.x + PLAYER_RECTDIS, m_Pos.y + PLAYER_RECTDIS,
		m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDIS, m_Pos.y + m_SrcRect.GetHeight()); }
	bool	IsTrigger(void) { return m_bTrigger; }
};

