/*****************************************************************
 *	@file			Game.h
 *	@brief			Q[V[NX
 *	@author			δγιDR
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

// INCLUDE
#include "SceneBase.h"
#include "GameDefine.h"
#include "Camera2D.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "TargetObj.h"
#include "Stage.h"
#include "MapObj.h"
#include "BackChip.h"

class CGame :
	public CSceneBase
{
private:
	CCamera2D			m_MainCamera;
	CStage				m_Stage[STAGE_COUNT];

	int					m_StageNo;

	bool				m_bPoase;
	bool				m_bClear;

	CPlayer						m_Player;
	CDynamicArray<CEnemy*>		m_pEnemyArray;
	CDynamicArray<CItem*>		m_pItemArray;
	CDynamicArray<CTargetObj*>	m_pTargetObjArray;
	CDynamicArray<CMapObj*>		m_pMapObjArray;
	CDynamicArray<CBackChip*>	m_pBackChipArray;

	void Collosion(void);

public:
	CGame(void);
	~CGame(void) override;
	bool Load(void) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(void) override;
	void RenderUI(void) override;
	void RenderDebug(void) override;
	void Release(void) override;

	void UpdateDebug(void);

	int GetSceneName(void) { return SCENENO_GAME; }
	void SetStageNo(const int& no);
};

