/*****************************************************************
 *	@file			GameOver.cpp
 *	@brief			ゲームオーバーシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"GameOver.h"

/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGameOver::CGameOver() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGameOver::~CGameOver() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
bool CGameOver::Load() {

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
void CGameOver::Initialize() {
	//遷移先の初期化
	m_NextSceneNo = SCENENO_GAMEOVER;
}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CGameOver::Update() {

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_pEffect->IsStart())
	{
		m_NextSceneNo = SCENENO_TITLE;
		m_pEffect->Out(10);
	}

	//UpdateDebug();

}

/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGameOver::Render() {

	String((g_pGraphics->GetTargetWidth() - 128 * 8) * 0.5f - 128, 540 - 64, 128, "GAMEOVER");
	String((g_pGraphics->GetTargetWidth() - 64 * 12) * 0.5f - 64, 740 - 32, 64, "PRESS RETURN");
	String((g_pGraphics->GetTargetWidth() - 64 * 13) * 0.5f - 64, 840 - 32, 64, "BACK TO TITLE");
	
	g_pGraphics->SetBlending(Blending::BLEND_SUB);
	String((g_pGraphics->GetTargetWidth() - 128 * 8) * 0.5f - 128, 540 - 64, 128, "GAMEOVER", MOF_XRGB(128, 128, 0));
	String((g_pGraphics->GetTargetWidth() - 64 * 12) * 0.5f - 64, 740 - 32, 64, "PRESS RETURN", MOF_XRGB(128, 128, 0));
	String((g_pGraphics->GetTargetWidth() - 64 * 13) * 0.5f - 64, 840 - 32, 64, "BACK TO TITLE", MOF_XRGB(128, 128, 0));
	g_pGraphics->SetBlending(Blending::BLEND_NORMAL);

	RenderDebug();
}
 void CGameOver::RenderUI()
 {
 }
/*****************************************************************
* @fn
* デバッグ更新
* @param なし
* @return なし
*****************************************************************/
void CGameOver::UpdateDebug() {

	if (g_pInput->IsKeyPush(MOFKEY_Q)) {
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAME;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_pEffect->IsStart()) {
		m_pEffect->Out(10);
	}
	else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

	}
	if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {

		/*m_NextSceneNo = SCENENO_RANKING;
		m_NextSceneNo = SCENENO_GAME;*/
	}
}
/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGameOver::RenderDebug() {

	//CGraphicsUtilities::RenderString(0, 100, "ゲームオーバー");

}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CGameOver::Release() {
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;
	}

}