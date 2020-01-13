/*****************************************************************
 *	@file			Title.cpp
 *	@brief			タイトルシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

 // INCLUDE
#include "Title.h"


//コンストラクタ
CTitle::CTitle(void) :
	CSceneBase()
{
}

//デストラクタ
CTitle::~CTitle(void)
{
}

//読み込み
bool CTitle::Load(void)
{

	//シーンエフェクトスタート
	m_pEffect = new CEffectFade();
	m_pEffect->In(10);

	return TRUE;
}

//初期化
void CTitle::Initialize(void)
{
	//遷移先の初期化
	m_NextSceneNo = SCENENO_TITLE;

	m_pTexture = g_pTextureManager->GetTexture("Title.png");
	m_SelectNo = 0;
	m_RectColor = MOF_ARGB(180, 64, 64, 64);
	int fontSize = 64;
	float sx1 = (g_pGraphics->GetTargetWidth() - fontSize * 9) * 0.5f;
	float sy1 = g_pGraphics->GetTargetHeight() * 0.5f + 200;
	float sx2 = (g_pGraphics->GetTargetWidth() - fontSize * 4) * 0.5f;
	float sy2 = g_pGraphics->GetTargetHeight() * 0.5f + 300;
	m_Rect = CRectangle(sx1, sy1, sx1 + fontSize * (9 + 2), sy1 + 64);
	m_bAlphaUp = false;
	m_Alpha = 0;
}

//更新
void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_NextSceneNo = SCENENO_GAME;
	}

	UpdateDebug();
	
	if (m_bAlphaUp)
	{
		m_Alpha -= 5;
		if (m_Alpha < 100)
		{
			m_Alpha = 100;
			m_bAlphaUp = false;
		}
	}
	else
	{
		m_Alpha += 5;
		if (m_Alpha > 180)
		{
			m_Alpha = 180;
			m_bAlphaUp = true;
		}
	}
	if (g_pGamePad->IsKeyPush(XINPUT_DP_UP) || g_pGamePad->GetStickVertical() > 0.8f)
	{
		if (--m_SelectNo < 0)
		{
			m_SelectNo = 1;
		}
	}
	else if (g_pGamePad->IsKeyPush(XINPUT_DP_DOWN) || g_pGamePad->GetStickVertical() < -0.8f)
	{
		if (++m_SelectNo > 1)
		{
			m_SelectNo = 0;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) || g_pGamePad->IsKeyPush(XINPUT_A))
	{
		switch (m_SelectNo)
		{
		case 0:
		{
			m_pEffect->Out(10);
			break;
		}
		case 1:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			break;
		}
	}
	if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {

		m_NextSceneNo = SCENENO_GAME;
	}
}

//描画
void CTitle::Render()
{
	RenderDebug();
	float scale = 0.4f;
	float x = (g_pGraphics->GetTargetWidth() - m_pTexture->GetWidth() * scale) * 0.5f;
	float y = (g_pGraphics->GetTargetHeight() - m_pTexture->GetHeight() * scale) * 0.5f;
	m_pTexture->RenderScale(x, y, scale);
	int fontSize = 64;
	float sx1 = (g_pGraphics->GetTargetWidth() - fontSize * 9) * 0.5f;
	float sy1 = g_pGraphics->GetTargetHeight() * 0.5f + 200;
	float sx2 = (g_pGraphics->GetTargetWidth() - fontSize * 4) * 0.5f;
	float sy2 = g_pGraphics->GetTargetHeight() * 0.5f + 300;
	CGraphicsUtilities::RenderFillRect(sx1, sy1 + 100 * m_SelectNo, sx1 + fontSize * (9 + 2), sy1 + 64 + 100 * m_SelectNo, MOF_ARGB(m_Alpha, 180, 180, 180));
	String(sx1, sy1, fontSize, "GameStart");
	String(sx2, sy2, fontSize, "Exit");
}

void CTitle::RenderUI()
{
}

void CTitle::UpdateDebug() {
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