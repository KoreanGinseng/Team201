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
	m_pEffect = new CEffectFade();
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

	//終了フラグの初期化
	m_bEnd = false;
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

	if (g_pInput->IsKeyPush(MOFKEY_Q)) {

		m_bEnd = true;
		m_NextSceneNo = SCENENO_GAME;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd) {

		m_bEnd = true;
		m_pEffect->Out(10);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

		m_bEnd = true;

	}
	if (m_pEffect->IsEnd() && m_bEnd) {
		m_NextSceneNo = SCENENO_TITLE;
	}
}
/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::Render() {

	RenderDebug();

}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGameClear::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 100, "ゲームクリア");
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