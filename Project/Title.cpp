/*****************************************************************
 *	@file			Title.cpp
 *	@brief			�^�C�g���V�[���N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/

 // INCLUDE
#include "Title.h"


//�R���X�g���N�^
CTitle::CTitle(void) :
	CSceneBase()
{
}

//�f�X�g���N�^
CTitle::~CTitle(void)
{
}

//�ǂݍ���
bool CTitle::Load(void)
{

	//�V�[���G�t�F�N�g�X�^�[�g
	m_pEffect = new CEffectFade();
	m_pEffect->In(10);

	return TRUE;
}

//������
void CTitle::Initialize(void)
{
	//�J�ڐ�̏�����
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

//�X�V
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

//�`��
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

//�f�o�b�O�`��
void CTitle::RenderDebug()
{

	CGraphicsUtilities::RenderString(0, 100, "�^�C�g��");

}

//���
void CTitle::Release()
{
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;

	}

}