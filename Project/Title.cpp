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
	g_pSoundManager->LoadBGM("Title_BGM.mp3");
	if (!m_Movie.Load("op.wmv"))
	{
		return FALSE;
	}
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
	g_pSoundManager->StopBGM();
	g_pSoundManager->SetVolumeBGM("Title_BGM.mp3", 0.7f);
	g_pSoundManager->PlayBGM("Title_BGM.mp3");
	m_bMovie = false;
}

//更新
void CTitle::Update(void)
{
	
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
	if (g_pGamePad->IsKeyPush(XINPUT_DP_UP) || g_pGamePad->GetStickVertical() > 0.8f || g_pInput->IsKeyPush(MOFKEY_UP))
	{
		if (--m_SelectNo < 0)
		{
			m_SelectNo = 1;
		}
	}
	else if (g_pGamePad->IsKeyPush(XINPUT_DP_DOWN) || g_pGamePad->GetStickVertical() < -0.8f || g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		if (++m_SelectNo > 1)
		{
			m_SelectNo = 0;
		}
	}

	if ((g_pInput->IsKeyPush(MOFKEY_RETURN) || g_pGamePad->IsKeyPush(XINPUT_A)) && !m_bMovie)
	{
		switch (m_SelectNo)
		{
		case 0:
		{
			g_pSoundManager->PlaySE("Enter.mp3");
			m_Movie.Play();
			m_bMovie = true;
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
		g_pSoundManager->GetSoundBGM("Title_BGM.mp3")->Stop();
	}
	if (m_bMovie)
	{
		if (g_pInput->IsKeyPush(MOFKEY_NUMPAD0))
		{
			m_Movie.Stop();
		}
		m_Movie.Update();
		if (!m_Movie.IsPlay())
		{
			m_Movie.Stop();
			m_NextSceneNo = SCENENO_GAME;
			m_pEffect->Out(10);
		}
	}

}

//描画
void CTitle::Render(void)
{
	g_pTextureManager->GetTexture("bg6.png")->Render(0, 0);

	RenderDebug();
	float scale = 0.4f;
	float x = (g_pGraphics->GetTargetWidth() - m_pTexture->GetWidth() * scale) * 0.5f;
	float y = (g_pGraphics->GetTargetHeight() - m_pTexture->GetHeight() * scale) * 0.5f;
	m_pTexture->RenderScale(x, y, scale);
	int fontSize = 64;
	float sx1 = (g_pGraphics->GetTargetWidth() - fontSize * 9) * 0.5f - fontSize;
	float sy1 = g_pGraphics->GetTargetHeight() * 0.5f + 200;
	float sx2 = (g_pGraphics->GetTargetWidth() - fontSize * 4) * 0.5f - fontSize;
	float sy2 = g_pGraphics->GetTargetHeight() * 0.5f + 300;
	float sx3 = (g_pGraphics->GetTargetWidth() - fontSize * 2 * 12) * 0.5f - fontSize * 2;
	float sy3 = g_pGraphics->GetTargetHeight() * 0.5f/* - 300*/;
	CGraphicsUtilities::RenderFillRect(sx1, sy1 + 100 * m_SelectNo, sx1 + fontSize * (9 + 2), sy1 + 64 + 100 * m_SelectNo, MOF_ARGB(m_Alpha, 180, 180, 180));
	for (int i = 1; i <= 10; i++)
	{
		String(sx3 + i, sy3, fontSize * 2, "TIMEOPERATOR", MOF_COLOR_BLACK);
	}
	for (int i = 1; i <= 10; i++)
	{
		String(sx3 - i, sy3, fontSize * 2, "TIMEOPERATOR", MOF_COLOR_BLACK);
	}
	String(sx3, sy3, fontSize * 2, "TIMEOPERATOR");
	g_pGraphics->SetBlending(Blending::BLEND_ADD);
	String(sx3, sy3, fontSize * 2, "TIMEOPERATOR", MOF_XRGB(201, 140, 53));
	g_pGraphics->SetBlending(Blending::BLEND_NORMAL);

	String(sx1, sy1, fontSize, "GAMESTART");
	String(sx2, sy2, fontSize, "EXIT");

	if (m_bMovie)
	{
		m_Movie.Render(0, 0);
	}
}

void CTitle::RenderUI()
{
}

void CTitle::UpdateDebug() {
}

//デバッグ描画
void CTitle::RenderDebug()
{

	//CGraphicsUtilities::RenderString(0, 100, "タイトル");

}

//解放
void CTitle::Release()
{
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;

	}
	m_Movie.Release();
}