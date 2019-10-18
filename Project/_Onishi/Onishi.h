/*****************************************************************
 *	@file			Onishi.h
 *	@brief			オオニシシーンクラス
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

 //! INCLUDE
#include	"../SceneBase.h"
#include	"EnemyMove.h"
#include	"Enemy_KURIBO.h"
#include	"Enemy_NOKONOKO.h"
#include	"Enemy_TERESA.h"
#include	"Enemy_BAT.h"
#include	"Enemy_KOTEIHOUDAI.h"
#include	"../Enemy_TESTBOS.h"
#include	"../ENEMY_FLOATING.h"
#include	"../Atack_KURIBO.h"
#include	"../Atack_NOKONOKO.h"
#include	"../Atack_TERESA.h"
#include	"../Atack_BAT.h"
#include	"../Atack_KOTEIHOUDAI.h"
#include	"../Atack_TESTBOS.h"
#define		spead 20
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
	CEnemyMove* gEnemy;
	CEnemy_KURIBO*	gKURIBO;
	CENEMY_NOKONOKO*	gNOKONOKO;
	CENEMY_TERESA*	gTERESA;
	CENEMY_BAT*	gBAT;
	CENEMY_KOTEIHOUDAI*	gKOTEIHOUDAI;
	CEnemy_TESTBOS* gTESTBOS;
	CENEMY_FLOATING* gFLOATING;
	CEnemyAtack* gAtack;
	CAtack_KURIBO* gAtack_KURIBO;
	CAtack_TESTBOS* gAtack_TESTBOS;
	
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