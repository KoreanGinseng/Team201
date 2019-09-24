#include "Object.h"



CObject::CObject()
{
}


CObject::~CObject()
{
}

void CObject::Initialize(float px, float py) {
	m_PosX = px;
	m_PosY = py;
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
		{
			"�I�u�W�F�N�g�`�F���W�P",
			0,0,
			64,64,
			FALSE,{{5,3,0},{5,2,0},{5,1,0},{5,0,0}},
		},
		{
			"�I�u�W�F�N�g�`�F���W�Q",
			0,64,
			64,64,
			FALSE,{{5,3,0},{5,2,0},{5,1,0},{5,0,0}}
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
	//��ɃA�j���[�V�����𓮂���
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	//���݂̃A�j���[�V���������������؂�ւ���
	if (m_Motion.GetMotionNo() == MOTION_CHANGE1 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_END);
	}
	if (m_Motion.GetMotionNo() == MOTION_CHANGE2 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_START);
	}
	//if (m_bMotionEnd)
	//{
	//}

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

void CObject::ChangeEnd()
{
	//������x�ʂ邽�߂Ƀt���O��off�ɂ���
	bFlag = false;
}
void CObject::Change()
{
	//��񂵂��ʂ�Ȃ��悤�ɂ��邽��
	if (bFlag)
	{
		return;
	}
	bFlag = true;
	//�F����ԐF��
	if (m_Motion.GetMotionNo() == MOTION_START)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE1);
	}
	if (m_Motion.GetMotionNo() == MOTION_END)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE2);
	}
	
//	else if (m_Motion.GetMotionNo() != MOTION_END)
//	{
		//m_Motion.AddTimer(STOPBITS_20);
//		m_Motion.AddTimer(CUtilities::GetFrameSecond());
//	}


	//�ԐF����F��
	/*if (m_Motion.GetMotionNo() == MOTION_END)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE2);
	}

	else if (m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_START);
	}

	else if (m_Motion.GetMotionNo() != MOTION_START)
	{
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
	}*/

	MOF_PRINTLOG("%s\n", m_Motion.IsEndMotion() ? "ture" : "false");
	


	
}