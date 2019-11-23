#include "Loading.h"



CLoading::CLoading() :
m_bEnd(false)
{
	m_bStartUp = false;
	m_bStart = false;
	m_Count = 0;
	m_CountMax = 0;
}


CLoading::~CLoading()
{
}

void CLoading::Load(void)
{
	m_Message = "�G�t�F�N�g�ǂݍ��ݒ�";
	m_CountMax = 1;
	m_Count = 0;
	g_pEffectManager->Load();
	m_Count++;

	m_Message = "�摜�f�[�^�ǂݍ��ݒ�";
	m_CountMax = TEXTURE_COUNT;
	m_Count = 0;
	for (int i = TEXTURE_PLAYER; i < TEXTURE_COUNT; i++)
	{
		g_pTextureManager->GetResource(FileName[i]);
		m_Count++;
	}

	m_Message = "�A�j���[�V�����f�[�^�ǂݍ��ݒ�";
	m_CountMax = ANIMATION_COUNT - TEXTURE_COUNT;
	m_Count = 0;
	for (int i = ANIMATION_PLAYER; i < ANIMATION_COUNT; i++)
	{
		g_pAnimManager->GetResource(FileName[i]);
		m_Count++;
	}
	m_Message = "�T�E���h�f�[�^�ǂݍ��ݒ�";
	m_CountMax = SOUND_COUNT - ANIMATION_COUNT;
	m_Count = 0;
	for (int i = SOUND_JUMP; i < SOUND_COUNT; i++)
	{
		g_pSoundManager->GetResource(FileName[i]);
		m_Count++;
	}
	m_Message = "�V�[���̓ǂݍ��ݒ�";
	m_CountMax = 1;
	m_Count = 0;
	m_pScene->Load();
	m_Count++;
}

void CLoading::Initialize(void)
{
	m_Message = "��������";
	m_CountMax = 2;
	m_Count = 0;
	g_pEffectManager->Initialize();
	m_Count++;
	m_pScene->Initialize();
	m_Count++;
}

void CLoading::Run(void) 
{
	Load();
	Initialize();
	m_bEnd = true;
	if (m_bStartUp)
	{
		m_bStart = true;
	}
	else
	{
		m_Message = "A�{�^���������Ă�������";
	}
}

void CLoading::Render(void)
{
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_COLOR_BLACK);
	if (m_bEnd)
	{
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2 - 50, g_pGraphics->GetTargetHeight() / 2, "�ǂݍ��݊����I");
	}
	else
	{
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2 - 50, g_pGraphics->GetTargetHeight() / 2, "%d / %d", m_Count, m_CountMax);
	}
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2 - 100, g_pGraphics->GetTargetHeight() / 2 - 100, "%s", m_Message.GetString());
}
