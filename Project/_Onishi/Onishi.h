/*****************************************************************
 *	@file			Onishi.h
 *	@brief			オオニシシーンクラス
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

//! INCLUDE
#include	"../SceneBase.h"
#include	"Enemy.h"

#define		spead 20


enum ENEMY
{
	ENEMY_KURIBO,
	ENEMY_NOKONOKO,
	ENEMY_TERESA,
};
 /*****************************************************************
  *	@brief			オオニシシーンクラス
  *	@author			井上颯騎
  *****************************************************************/
class COnishi : public CSceneBase {
private:
	bool poase;
	float time;
	float Xpos;
	float Ypos;
	float MXpos;
	float MYpos;
	bool atack;
	bool h;
	float getxpos;
	float getypos;
	float getx;
	float gety;
	bool Revers;

	int gEnemytype;
	CEnemy gEnemy;

public:
	/*****************************************************************
	 * @fn
	 * 引数なしコンストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	COnishi();

	/*****************************************************************
	 * @fn
	 * 引数なしデストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	~COnishi();

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