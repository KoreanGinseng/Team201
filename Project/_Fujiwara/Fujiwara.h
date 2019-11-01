/*****************************************************************
 *	@file			Fujiwara.h
 *	@brief			フジワラシーンクラス
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

//! INCLUDE
#include	"../SceneBase.h"
#include    <string>

#define		FONT_SIZE		32.0f
//追加
#define		INI_X	100
#define		INI_Y	600
#define		MAX_HEART		3
 /*****************************************************************
  *	@brief			フジワラシーンクラス
  *	@author			井上颯騎
  *****************************************************************/
class CFujiwara : public CSceneBase {
private:
	int X;
	int Y;
	CTexture* m_pFontTexture;
	int Lenth;
	int time;
	int num;
	
	//ハート表示
	CTexture m_pHeatTexture;
	int Hposx;
	int Hposy;
	int HP;


public:
	/*****************************************************************
	 * @fn
	 * 引数なしコンストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	CFujiwara();

	/*****************************************************************
	 * @fn
	 * 引数なしデストラクタ
	 * @param なし
	 * @return なし
	 *****************************************************************/
	~CFujiwara();

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

	/*****************************************************************
	 * @fn
	 * 解放
	 * @param なし
	 * @return なし
	 *****************************************************************/
	void String(int sx, int sy, int fontsize, const char* str);
	void String(int sx, int sy, int fontsize, const int& time);
	void RenHp(int hp,int hx,int hy);


	
};