/*****************************************************************
 *	@file			Player.h
 *	@brief			プレイヤークラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"
#include	"Camera2D.h"
#include	"GameDefine.h"
#include	"Character.h"
#include	"Enemy.h"
#include	"TargetObj.h"
#include	"Item.h"
#include	"Score.h"

//DEFINE
#define		PLAYER_RECTDIS		90		//プレイヤーの当たり判定矩形左右の縮める値

class CPlayer : public CCharacter
{
private:
	//プレイヤーのアニメーション
	enum tag_Animation {
		ANIM_WAIT,
		ANIM_MOVE,
		ANIM_JUMPUP,
		ANIM_JUMPDOWN,
		ANIM_SKILLSTANCE,
		ANIM_SKILLPLAY,

		ANIM_COUNT,
	};
	struct KeyConfig {
		bool	moveLeft;
		bool	moveRight;
		bool	jump;
		bool	clime;
		bool	fall;
		bool	selectNext;
		bool	selectBack;
		bool	skillStance;
		bool	skillStancePull;
		bool	skillBack;
		bool	skillStop;
		bool	skillSkip;
		bool	attack;
	};

	KeyConfig					m_KeyConfig;		//キーコンフィグ
	bool						m_bKey;				//キーボードかパッドかのフラグ
	bool						m_bJump;			//ジャンプフラグ
	std::vector<CSubstance*>	m_SkillTarget;		//スキルで選択できるリスト
	bool						m_bTrigger;			//スキルを使ったフラグ
	bool						m_bClime;			//縄を登るようのフラグ
	int							m_Target;			//ターゲットしている番号
	float						m_Skillrang;		//スキルの範囲
	CCircle						m_SkillCircle;		//スキルの円
	bool						m_bCntrl;			//操作可能フラグ

	bool						m_bSkillObjNomal;
	bool						m_bSkillObjBack;
	bool						m_bSkillObjTrip;
	bool						m_bSkillEne;

	CSpriteMotionController		m_SordMotion;

	bool						m_bAttack;

public:
	CPlayer(void);			//コンストラクタ
	~CPlayer(void);			//デストラクタ
	void Initialize(void) override;					//初期化
	void Update(void) override;						//更新
	void Render(const Vector2& screenPos) override;	//描画
	void RenderCircle(const Vector2& screenPos) override;	//Circle描画
	void Release(void) override;					//解放

	void Move(void);								//動き,移動量計算
	void Animation(void);							//アニメーション制御
	void Skill(void);								//スキル制御
	//ターゲット選択
	void TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray);

	void CollisionStage(const Vector2& over) override; //埋まり値の処理

	//Get
	bool	IsTrigger(void) { return m_bTrigger; }	//スキルを使ったかのフラグ取得
	bool	IsClime(void) { return m_bClime; }		//登る状態かのフラグ
	CRectangle GetRect(void) override;				//当たり判定用矩形の取得
	//Set
	void   SetClime(const bool& b)					//フラグのセット
	{ m_bClime = b; }
	bool   Dmg(CEnemy& ene);						//ダメージの処理
	bool   Dmg(const int& dmg);						//ダメージの処理
	void SetCntrl(const bool& b) { m_bCntrl = b; }	//操作フラグのセット
	void Heal(const int& h) { m_HP += h; }

	bool IsJump(void) const { return m_bJump; }
	bool IsObjNomal(void) const { return m_bSkillObjNomal; }
	bool IsObjBack(void) const { return m_bSkillObjBack; }
	bool IsObjTrip(void) const { return m_bSkillObjTrip; }
	bool IsEne(void) const { return m_bSkillEne; }
};

