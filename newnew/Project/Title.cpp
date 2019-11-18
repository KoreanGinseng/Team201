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

	//シーンエフェクトスタート
	m_pEffect = new CEffectFade();
	m_pEffect->In(10);

	return TRUE;
}

//初期化
void CTitle::Initialize()
{
	//遷移先の初期化
	m_NextSceneNo = SCENENO_TITLE;


}

//更新
void CTitle::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_NextSceneNo = SCENENO_GAME;
	}

	UpdateDebug();
	
}

//描画
void CTitle::Render()
{

	RenderDebug();

}

void CTitle::RenderUI()
{
}

void CTitle::UpdateDebug() {

	if (g_pInput->IsKeyPush(MOFKEY_Q)) {

		m_NextSceneNo = SCENENO_GAME;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		m_pEffect->Out(10);

	}

	if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {

		m_NextSceneNo = SCENENO_GAME;
	}

}

//デバッグ描画
void CTitle::RenderDebug()
{

	CGraphicsUtilities::RenderString(0, 100, "タイトル");

}

//解放
void CTitle::Release()
{
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;

	}

}