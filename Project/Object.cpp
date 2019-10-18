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
bool CObject::Collision(CRectangle r, float& ox, float& oy)
{
	int h = r.GetHeight();
	int w = r.GetWidth();
	
	//���Ă���
	if (m_Motion.GetMotionNo() == MOTION_START)
	{
		ObjNo = 0;
	}
	//���Ă��Ȃ�
	else 
	{
		ObjNo = 1;
	}
	bool re = false;
	
	float x = m_SrcRect.GetWidth();
	float y = m_SrcRect.GetHeight();
	//�����蔻��
			CRectangle cr(m_PosX, m_PosY, m_PosX+x ,m_PosY +y);
			//�����蔻��p�̋�`
			//���E����
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;
			lrec.Expansion(0, -3);
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;
			rrec.Expansion(0, -3);
			//�I�u�W�F�N�g�����Ă��Ȃ����
			if (ObjNo == 0)
			{
			    //���Ɠ����蔻��
				if (cr.CollisionRect(lrec))
				{
					re = true;
					//���̖��܂�Ȃ̂Ń`�b�v�E�[�����`�̍��[�̒l���������l�����܂�̒l
					ox += cr.Right - lrec.Left;
					r.Left += cr.Right - lrec.Left;
					r.Right += cr.Right - lrec.Left;
				}
				//�E�Ɠ����蔻��
				if (cr.CollisionRect(rrec))
				{
					re = true;
					//�E�̖��܂�Ȃ̂Ń`�b�v�̍��[����
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
				CRectangle brec = r;
				brec.Top = brec.Bottom - 1;//
				brec.Expansion(-2, 0);//
				//���Ɠ����蔻��
				if (cr.CollisionRect(brec))
				{
					re = true;
					//���̖��܂�Ȃ̂Ń`�b�v�̏�[�����`�̉��[�̒l���������l�����܂�l
					oy += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}

				//��Ŕ͈͂����肵����p�̋�`���쐬����B
				CRectangle trec = r;
				trec.Bottom = trec.Top - 1;//
				trec.Expansion(-2, 0);//
				//��Ɠ����蔻��
				if (cr.CollisionRect(trec))
				{
					re = true;
					//��̖��܂�Ȃ̂Ń`�b�v�����[�����`�̏�[��
					oy += cr.Bottom - trec.Top;
					r.Top += cr.Bottom - trec.Top;
					r.Bottom += cr.Bottom - trec.Top;
				}
			}
	return re;
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
	MOF_PRINTLOG("%s\n", m_Motion.IsEndMotion() ? "ture" : "false");	
}