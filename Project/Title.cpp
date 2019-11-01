/*****************************************************************
 *	@file			Title.cpp
 *	@brief			タイトルシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

 // INCLUDE
#include "Title.h"


//コンストラクタ
CTitle::CTitle() :
	CSceneBase()
{
}

//デストラクタ
CTitle::~CTitle()
{
}

//読み込み
bool CTitle::Load()
{
	return TRUE;
}

//初期化
void CTitle::Initialize()
{
	//終了フラグの初期化
	m_bEnd = false;
	//遷移先の初期化
	m_NextSceneNo = SCENENO_TITLE;


}

//更新
void CTitle::Update()
{

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		m_bEnd = true;
		m_NextSceneNo = SCENENO_GAME;

	}
	
}

//描画
void CTitle::Render()
{

	RenderDebug();

}

//デバッグ描画
void CTitle::RenderDebug()
{

	CGraphicsUtilities::RenderString(0, 100, "タイトル");

}

//解放
void CTitle::Release()
{

}