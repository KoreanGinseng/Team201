/*****************************************************************
 *	@file			Inoue.h
 *	@brief			�C�m�E�G�V�[���N���X
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

//! INCLUDE
#include "../SceneBase.h"
#include "../GameDefine.h"
#include "../TimeManager.h"
#include "../EffectManager.h"
#include "../SoundManager.h"
#include "../Coordinate.h"
#include "../Camera2D.h"
#include "../Player.h"
#include "../Stage.h"

//! SCENE ADD
#include	"../Ranking.h"

//! DEFINE

 /*****************************************************************
  *	@brief			�C�m�E�G�V�[���N���X
  *	@author			����D�R
  *****************************************************************/
class CInoue : public CSceneBase {
private:
	CCamera2D			m_MainCamera;
	CPlayer				m_Player;
	CStage				m_Stage[STAGE_COUNT];
	static	int			m_StageNo;

	// �G
	CEnemy*				m_pEnemyArray;
	// �A�C�e��
	CItem*				m_pItemArray;
	// �I�u�W�F�N�g
	CObject*			m_pObjArray;

	bool				m_bPoase;

public:
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	int GetSceneName(void) { return SCENENO_INOUE; }

	static	void	NextStage(void) {
		if (++m_StageNo >= STAGE_COUNT) {
			m_StageNo = 0;
		};
	}
public:
	/*****************************************************************
	 * @fn
	 * �����Ȃ��R���X�g���N�^
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	CInoue();

	/*****************************************************************
	 * @fn
	 * �����Ȃ��f�X�g���N�^
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	~CInoue();
};