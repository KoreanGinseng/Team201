/*****************************************************************
 *	@file			Inoue.cpp
 *	@brief			イノウエシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Inoue.h"

/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CInoue::CInoue() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CInoue::~CInoue() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
void CInoue::Load() {
	m_Stage.Load("testMap.txt");
}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void CInoue::Initialize() {
	m_Pos = Vector2(0, 0);
}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CInoue::Update() {

	Vector2 move = Vector2(0, 0);

	if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {
		move.x -= MOVESPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP)) {
		move.y += MOVESPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
		move.x += MOVESPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN)) {
		move.y -= MOVESPEED;
	}

	m_Pos += move;

	if (m_Pos != m_MainCamera.GetScroll()) {
		Vector2 d = m_Pos - m_MainCamera.GetScroll();
		d /= MOVESPEED;
		m_MainCamera.AddScroll(d);
	}

	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		PostQuitMessage(0);
	}

	/*if (g_pInput->IsKeyHold(MOFKEY_A)) {
		m_MainCamera.AddScroll(Vector2(-MOVESPEED, 0));
	}
	if (g_pInput->IsKeyHold(MOFKEY_W)) {
		m_MainCamera.AddScroll(Vector2( 0, MOVESPEED));
	}
	if (g_pInput->IsKeyHold(MOFKEY_D)) {
		m_MainCamera.AddScroll(Vector2(MOVESPEED, 0));
	}
	if (g_pInput->IsKeyHold(MOFKEY_S)) {
		m_MainCamera.AddScroll(Vector2(0, -MOVESPEED));
	}*/
}

/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CInoue::Render() {
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Pos);
	CGraphicsUtilities::RenderFillRect(screenPos.x, screenPos.y, screenPos.x + RECTSIZE, screenPos.y + RECTSIZE, MOF_COLOR_GREEN);
}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CInoue::RenderDebug() {
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Pos);
	CGraphicsUtilities::RenderString(10, 10, "camera[x]:%5.1f [y]:%5.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
	CGraphicsUtilities::RenderString(10, 30, "world [x]:%5.1f [y]:%5.1f", m_Pos.x, m_Pos.y);
	CGraphicsUtilities::RenderString(10, 50, "screen[x]:%5.1f [y]:%5.1f", screenPos.x, screenPos.y);
}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CInoue::Release() {

}