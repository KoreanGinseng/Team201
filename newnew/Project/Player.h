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
#include	"Character.h"
#include	"Enemy.h"
#include	"TargetObj.h"
#include	"Item.h"
#include	"Score.h"
#include	"MovePlayer.h"

//DEFINE
#define		PLAYER_RECTDIS		90

namespace Player {
	enum tag_Animation {
		ANIM_WAIT,
		ANIM_MOVE,

		ANIM_COUNT,
	};
}

class CPlayer : public CCharacter
{
private:

	typedef enum tag_WAY {
		WAY_LEFT,
		WAY_RIGHT,
	}WAY;

	std::vector<CSubstance*>	m_SkillTarget;
	bool						m_bTrigger;
	bool						m_bClime;
	int							m_HP;
	int							m_Target;
	float						m_CoolTime;
	float						m_Skillrang;
	CCircle						m_SkillCircle;

public:
	CPlayer(void);
	~CPlayer(void);
	void Initialize(void);
	void Update(void);
	void Render(Vector2 screenPos);
	void RenderDebug(Vector2 screenPos);
	void Release(void);
	
	void Animation(void);

	//Skill
	void Skill(void);
	//void SkillColision(CEnemy* pene, int eneCount, CTargetObj* pobj, int objCount);
	void TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray);

	//Collision
	void CollisionStage(const Vector2& over) override;

	//Get
	bool	IsTrigger(void) { return m_bTrigger; }
	bool	IsClime(void) { return m_bClime; }
	int		GetHp(void) { return m_HP; }
	CRectangle GetRect(void) const override { 
		CRectangle r = CCharacter::GetRect();
		r.Expansion(-PLAYER_RECTDIS, 0);
		r.Top += 20;
		r.Bottom -= 10;
		return r;
	}
	//Set
	void   SetClime(const bool& b) { m_bClime = b; }


	bool   Dmg(CEnemy& ene);
};

