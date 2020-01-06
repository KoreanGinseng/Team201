#include "Effect.h"



CEffect::CEffect(void) :
m_pTexture(nullptr),
m_Motion(),
m_bShow(false),
m_Pos(Vector2(0, 0))
{
}


CEffect::~CEffect(void)
{
}

bool CEffect::IsShow(void) const
{
	return m_bShow;
}

void CEffect::Start(const Vector2 & pos)
{
	//�����ʒu�ɍ��W�Z�b�g
	m_Pos = pos;
	//�\���t���OON
	m_bShow = true;
	//�A�j���[�V������擪�ɃZ�b�g����
	m_Motion.SetTime(0);
}

bool CEffect::Load(const std::string& str)
{
	//�f�[�^�����݂��Ȃ��ꍇ�ǂݍ���
	if (CAnimationManager::GetAnimation(str) == nullptr)
	{
		CAnimationManager::Load(str);
	}
	CAnimationData* pData = CAnimationManager::GetAnimation(str);
	//�f�[�^���������ǂݍ��߂Ă��Ȃ��ꍇ���s
	if (pData == nullptr)
	{
		return false;
	}
	//�摜�����݂��Ȃ��ꍇ�ǂݍ���
	std::string texName = pData->GetTextureName();
	if (CTextureManager::GetTexture(texName) == nullptr)
	{
		CTextureManager::Load(texName.c_str());
	}
	m_pTexture = CTextureManager::GetTexture(texName);
	//�摜���������ǂݍ��߂Ă��Ȃ��ꍇ���s
	if (m_pTexture == nullptr)
	{
		return false;
	}
	//���[�V�����̍쐬
	int animCount = pData->GetAnimCount();
	SpriteAnimationCreate* pAnim = pData->GetAnim();
	m_Motion.Create(pAnim, animCount);
	return true;
}

void CEffect::Update(void)
{
	//�\���t���O�������Ă��Ȃ��ꍇ�X�L�b�v
	if (!m_bShow)
	{
		return;
	}
	//�A�j���[�V�������X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	//�A�j���[�V�������I�����Ă���΃t���O��܂�
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

void CEffect::Render(void)
{
	//�\���t���O�������Ă��Ȃ��ꍇ�X�L�b�v
	if (!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_Pos.x, m_Pos.y, m_Motion.GetSrcRect());
}

void CEffect::Release(void)
{
	m_pTexture = nullptr;
	m_Motion.Release();
}
