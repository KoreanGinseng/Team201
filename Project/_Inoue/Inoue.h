/*****************************************************************
 *	@file			Inoue.h
 *	@brief			イノウエシーンクラス
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

//! INCLUDE
#include	"../SceneBase.h"
#include	"../Camera2D.h"
#include	"../Coordinate.h"
#include	"../Stage.h"

//! DEFINE
#define		RECTSIZE	10
#define		MOVESPEED	10
#define		STAGECOUNT	3

 /*****************************************************************
  *	@brief			イノウエシーンクラス
  *	@author			井上颯騎
  *****************************************************************/
class CInoue : public CSceneBase {
private:
	CCamera2D	m_MainCamera;
	Vector2		m_Pos;
	CStage		m_Stage[STAGECOUNT];

	int			m_StageNo;

public:
	/*****************************************************************
	 * @fn
	 * 引数なしコンストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	CInoue();

	/*****************************************************************
	 * @fn
	 * 引数なしデストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	~CInoue();

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

	CRectangle	GetRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + RECTSIZE, m_Pos.y + RECTSIZE); }
};