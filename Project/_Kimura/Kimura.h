/*****************************************************************
 *	@file			Kimura.h
 *	@brief			キムラシーンクラス
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

//! INCLUDE

#include	"../SceneBase.h"
//#include	"../GameDefine.h"
#include	"../Player.h"

 /*****************************************************************
  *	@brief			キムラシーンクラス
  *	@author			井上颯騎
  *****************************************************************/
class CKimura : public CSceneBase {
private:
	CPlayer			m_Player;

public:
	/*****************************************************************
	 * @fn
	 * 引数なしコンストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	CKimura();

	/*****************************************************************
	 * @fn
	 * 引数なしデストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	~CKimura();

	/*****************************************************************
	 * @fn
	 * 必要な素材の読み込み
	 * @param なし
	 * @return なし
	 *****************************************************************/
	bool Load();

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