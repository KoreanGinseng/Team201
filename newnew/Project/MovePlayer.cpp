#include "MovePlayer.h"



CMovePlayer::CMovePlayer()
{
}


CMovePlayer::~CMovePlayer()
{
}

void CMovePlayer::Initialize(void)
{
	m_bClime = false;
	m_bJump = false;
}

void CMovePlayer::Update(void)
{
	PadOparation();
	KeyOparation();

	if (!m_bClime)
	{
		m_Move.y += GRAVITY;
	}
	if (m_Move.y > 20.0f)
	{
		m_Move.y = 20.0f;
	}
	if (m_Move.x < 0)
	{
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
	}
	else if(m_Move.x > 0)
	{
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
	}
}

void CMovePlayer::PadOparation(void)
{
	//�E�X�e�B�b�N��|�����ꍇ�A�|���������Ɉړ�
	float s = g_pGamePad->GetStickHorizontal() * 10;
	std::roundf(s);
	s /= 10.0f;
	if (s != 0)
	{
		m_Move.x += m_Spd.x * s;
	}
	//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else
	{
		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_Move.x != 0)
		{
			m_Move.x -= (m_Spd.x - 0.1f) * s;
		}
		else
		{
			m_bMove = false;
		}
	}

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pGamePad->IsKeyPush(XINPUT_A) && !m_bJump)
	{
		m_bJump = true;
		
		m_Move.y = PLAYER_JUMPPOW;
	}
}

void CMovePlayer::KeyOparation(void)
{
	//�E�X�e�B�b�N��|�����ꍇ�A�|���������Ɉړ�
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT) || g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Move.x += m_Spd.x * (g_pInput->IsKeyHold(MOFKEY_LEFT) ? -1 : 1);
	}
	//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else
	{
		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_Move.x != 0)
		{
			m_Move.x -= (m_Spd.x - 0.1f) * (m_Move.x < 0) ? -1 : 1;
		}
		else
		{
			m_bMove = false;
		}
	}

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		m_bJump = true;

		m_Move.y = PLAYER_JUMPPOW;
	}
}
