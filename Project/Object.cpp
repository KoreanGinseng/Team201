#include "Object.h"



CObject::CObject()
{
}


CObject::~CObject()
{
}

void CObject::Initialize(float px, float py) {
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�I�u�W�F�N�g",
			0,0,
			64,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"�I�u�W�F�N�g�G���h",
			0,64,
			64,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	if (m_bMotionEnd)
	{
		m_Motion.ChangeMotion(MOTION_END);
	}
}

void CObject::Update(void) {
	//��\��
	if (!m_bShow)
	{
		return;
	}

	if (m_bMotionEnd)
	{
		//m_Motion.AddTimer(CUtilities::GetFrameSecond());
	}

	m_SrcRect = m_Motion.GetSrcRect();
}

void CObject::Render(Vector2 sp) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(sp.x, sp.y, m_SrcRect);
}

void CObject::RenderDebug(Vector2 sp) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr(sp.x, sp.y, sp.x + m_SrcRect.GetWidth(), sp.y + m_SrcRect.GetHeight());
	CGraphicsUtilities::RenderRect(hr, MOF_XRGB(255, 0, 0));
}

void CObject::Release(void) {
	m_Motion.Release();
}