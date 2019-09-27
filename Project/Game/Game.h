/*****************************************************************
 *	@file			Game.h
 *	@brief			ゲームシーンクラス
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

//! INCLUDE
#include	"../SceneBase.h"

#include	"../Stage.h"
#include	"../Player.h"
#include	"../Camera2D.h"
#include	"../EffectManager.h"
#include	"../SoundManager.h"


 /*****************************************************************
  *	@brief			ゲームシーンクラス
  *	@author			井上颯騎
  *****************************************************************/
class CGame : public CSceneBase {
private:
	CCamera2D			m_MainCamera;
	CPlayer				m_Player;
	CStage				m_Stage[STAGE_COUNT];
	/*CEffectManager		m_EffectManager;
	CSoundManager		m_SoundManager;*/

	int					m_StageNo;
	// 敵
	CEnemy*				m_EnemyArray;
	// アイテム
	CItem*				m_ItemArray;
	// オブジェクト
	CObject*			m_pObjArray;
public:
	/*****************************************************************
	 * @fn
	 * 引数なしコンストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	CGame();

	/*****************************************************************
	 * @fn
	 * 引数なしデストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	~CGame();

	/*****************************************************************
	 * @fn
	 * 必要な素材の読み込み
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void Load();

	/*****************************************************************
	 * @fn
	 * 初期化
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void Initialize();

	/*****************************************************************
	 * @fn
	 * 更新
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void Update();

	/*****************************************************************
	 * @fn
	 * 描画
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void Render();

	/*****************************************************************
	 * @fn
	 * デバッグ描画
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void RenderDebug();

	/*****************************************************************
	 * @fn
	 * 解放
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void Release();
};