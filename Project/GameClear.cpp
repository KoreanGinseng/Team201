/*****************************************************************
 *	@file			GameClear.cpp
 *	@brief			ゲームクリアシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"GameClear.h"

/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGameClear::CGameClear() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGameClear::~CGameClear() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
bool CGameClear::Load() {

	//シーンエフェクトスタート
	m_pEffect = NEW CEffectFade();
	m_pEffect->In(10);


	return TRUE;
}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::Initialize() {

	//遷移先の初期化
	m_NextSceneNo = SCENENO_GAMECLEAR;


}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::Update() {

	UpdateDebug();

}

/*****************************************************************
* @fn
* デバッグ更新
* @param なし
* @return なし
*****************************************************************/
void CGameClear::UpdateDebug() {

	//if (g_pInput->IsKeyPush(MOFKEY_Q)) {
	//	m_NextSceneNo = SCENENO_GAME;
	//}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_pEffect->IsStart()) {
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_TITLE;

		g_pSoundManager->PlaySE("Enter.mp3");
	}
	//else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

	//}
	//if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {
	//}
}
/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::Render() {

	RenderDebug();
	g_pTextureManager->GetTexture("arigatou.png")->Render(0, 0);
}

 void CGameClear::RenderUI()
 {
	 String((g_pGraphics->GetTargetWidth() - 64 * 12) * 0.5f - 64, 740 - 32, 64, "PRESS RETURN");
	 String((g_pGraphics->GetTargetWidth() - 64 * 13) * 0.5f - 64, 840 - 32, 64, "BACK TO TITLE");
 }

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::RenderDebug() {

	//CGraphicsUtilities::RenderString(0, 100, "ゲームクリア");
}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::Release() {
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;
	}

}