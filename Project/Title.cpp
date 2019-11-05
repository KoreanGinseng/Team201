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

}

//更新
void CTitle::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextSceneNo = SCENENO_GAME;
		ReNum::GetInstance().SetReNum();
	}
}

//描画
void CTitle::Render()
{
	
}

//デバッグ描画
void CTitle::RenderDebug()
{

}

//解放
void CTitle::Release()
{

}