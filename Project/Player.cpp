/*****************************************************************
 *	@file			Player.cpp
 *	@brief			�v���C���[�N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/

//INCLUDE
#include "Player.h"

//�R���X�g���N�^
CPlayer::CPlayer(void) :
m_pTexture(nullptr),
m_Pos(Vector2(0,0)),
m_Move(Vector2(0,0)),
m_Spd(Vector2(0,0)),
m_bJump(false),
m_HP(10),
m_Stock(3),
m_Motion()
{
}

//�f�X�g���N�^
CPlayer::~CPlayer(void)
{
}

//������
void CPlayer::Initialize(void)
{
	//���W�̏�����
	m_Pos = Vector2(g_pGraphics->GetTargetWidth() / 2, 0);
	//�ړ��ʂ̏�����
	m_Move = Vector2(0, 0);
	//�ړ����x�̏�����
	m_Spd = Vector2(PLAYER_SPEED, PLAYER_JUMPPOW);
	//HP�̏�����
	m_HP = PLAYER_MAXHP;
	//�c�@�̏�����
	m_Stock = PLAYER_MAXSTOCK;
	//�W�����v�t���O�̏�����
	m_bJump = false;
	//�p���[�A�b�v�t���O�̏�����
	m_bPowUp = false;

	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
			180,192,
			TRUE,{{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,4,0},{5,6,0}}
		},
	};
	m_Motion.Create(anim, ANIM_COUNT);
}

//�X�V
void CPlayer::Update(void)
{
	//�R���g���[���[���ڑ�����Ă��邩
	if (g_pInput->GetGamePadCount())
	{
		//�R���g���[���[���͂ł̈ړ��ʍX�V
		PadOparation();
	}

	//�L�[�{�[�h���͂ł̈ړ��ʍX�V
	KeyOparation();

	//�ړ�
	Move();

	//�A�j���[�V�������Z
	m_Motion.AddTimer(CUtilities::GetFrameSecond());

	//�A�j���[�V������`�X�V
	m_SrcRect = m_Motion.GetSrcRect();
}

//�`��
void CPlayer::Render(Vector2 screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y, m_SrcRect);
}

//�f�o�b�O�`��
void CPlayer::RenderDebug(Vector2 screenPos)
{

}

//���
void CPlayer::Release(void)
{

}

//�p�b�h�I�y���[�V����
void CPlayer::PadOparation(void)
{
	//�X�e�B�b�N���E�����ɓ|�����ꍇ�A�|���������Ɉړ�
	if (g_pGamePad->GetStickHorizontal() > 0.8f)
	{
		MoveAdd(WAY_RIGHT);
	}
	else if (g_pGamePad->GetStickHorizontal() < -0.8f)
	{
		MoveAdd(WAY_LEFT);
	}
	//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else
	{
		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_Move.x > 0)
		{
			MoveSub(WAY_RIGHT);
		}
		else if (m_Move.x < 0)
		{
			MoveSub(WAY_LEFT);
		}
	}

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pGamePad->IsKeyPush(GAMEKEY_A) && !m_bJump)
	{
		Jump();
	}
}

//�L�[�I�y���[�V����
void CPlayer::KeyOparation(void)
{
	//�X�e�B�b�N���E�����ɓ|�����ꍇ�A�|���������Ɉړ�
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		MoveAdd(WAY_RIGHT);
	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT)) 
	{
		MoveAdd(WAY_LEFT);
	}
	//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else
	{
		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_Move.x > 0)
		{
			MoveSub(WAY_RIGHT);
		}
		else if (m_Move.x < 0) 
		{
			MoveSub(WAY_LEFT);
		}
	}

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		Jump();
	}
}

//�ړ�
void CPlayer::Move(void)
{
	//�ړ��ʂɏd�͂�������
	m_Move.y += GRAVITY;
	m_Pos += m_Move;
}

//��������
void CPlayer::MoveAdd(WAY w)
{
	switch(w)
	{
	case WAY_RIGHT:
		m_Move.x += m_Spd.x;
		//�ő呬�x�𒴂��Ȃ��悤�ɂ���
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
		break;
	case WAY_LEFT:
		m_Move.x -= m_Spd.x;
		//�ő呬�x�𒴂��Ȃ��悤�ɂ���
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
		break;
	}
}

//��������
void CPlayer::MoveSub(WAY w)
{
	switch (w)
	{
	case WAY_RIGHT:
		m_Move.x -= m_Spd.x - 0.1f;
		//�[���ȉ��ɂȂ�Ȃ��悤�ɂ���
		if (m_Move.x < 0)
		{
			m_Move.x = 0;
		}
		break;
	case WAY_LEFT:
		m_Move.x += m_Spd.x - 0.1f;
		//�[���ȏ�ɂȂ�Ȃ��悤�ɂ���
		if (m_Move.x > 0)
		{
			m_Move.x = 0;
		}
		break;
	}
}

//�W�����v����
void CPlayer::Jump(void)
{
	//�W�����v���ʉ��̃e�X�g����
	//g_pSoundManager->Start(SUD_SOUNDEFFECT, SOUND_EFFECT);

	//�W�����v�t���O�𗧂Ă�
	m_bJump = true;

	//�p���[�A�b�v�t���O�������Ă���ꍇ�A�W�����v�͏㏸
	if (m_bPowUp)
	{
		m_Move.y = PLAYER_HIGHJUMPPOW;
	}
	else
	{
		m_Move.y = PLAYER_JUMPPOW;
	}
}

//�����蔻��
void CPlayer::CollisionStage(Vector2 o) {
	m_Pos += o;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ���������
	if (o.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
		if (m_bJump)
		{
			m_bJump = false;
		}
	}
	else if (o.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if ((o.x < 0 && m_Move.x > 0) || (o.x > 0 && m_Move.x < 0))
	{
		m_Move.x = 0;
	}
}