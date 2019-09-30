/*****************************************************************
 *	@file			Game.h
 *	@brief			ゲームシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

// INCLUDE
#include "SceneBase.h"
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
	int					m_StageNo;
	// 敵
	CEnemy*				m_EnemyArray;
	// アイテム
	CItem*				m_ItemArray;
	// オブジェクト
	CObject*			m_pObjArray;

	CTexture m_PlayerTex;

public:
	CGame(void);
	~CGame(void);
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

