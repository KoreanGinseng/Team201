/*****************************************************************
 *	@file			Game.h
 *	@brief			�Q�[���V�[���N���X
 *	@author			����D�R
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
	// �G
	CEnemy*				m_EnemyArray;
	// �A�C�e��
	CItem*				m_ItemArray;
	// �I�u�W�F�N�g
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

