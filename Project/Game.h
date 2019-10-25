/*****************************************************************
 *	@file			Game.h
 *	@brief			ゲームシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

// INCLUDE
#include "SceneBase.h"
#include "GameDefine.h"
#include "TimeManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Coordinate.h"
#include "Camera2D.h"
#include "Player.h"
#include "Stage.h"

class CGame :
	public CSceneBase
{
private:
	CCamera2D			m_MainCamera;
	CPlayer				m_Player;
	CStage				m_Stage[STAGE_COUNT];
	static	int			m_StageNo;
	
	// 敵
	CEnemy*				m_pEnemyArray;
	// アイテム
	CItem*				m_pItemArray;
	// オブジェクト
	CObject*			m_pObjArray;

	bool				m_bPoase;

public:
	CGame(void);
	~CGame(void);
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	int GetSceneName(void) { return SCENENO_GAME; }

	static	void	NextStage(void) {
		if (++m_StageNo >= STAGE_COUNT) {
			m_StageNo = 0;
		};
	}
};

