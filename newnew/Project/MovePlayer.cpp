#include "MovePlayer.h"
#include	"Player.h"


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
	m_bReverse = false;
}

void CMovePlayer::Update(void)
{
	if (!m_bMove && m_MotionNo != Player::ANIM_WAIT)
	{
		m_MotionNo = Player::ANIM_WAIT;
	}
	if (m_bMove && m_MotionNo != Player::ANIM_MOVE)
	{
		m_MotionNo = Player::ANIM_MOVE;
	}

	if (g_pInput->GetGamePadCount())
	{
		PadOparation();
	}
	else
	{
		KeyOparation();
	}

	if (!m_bClime)
	{
		m_Move.y += GRAVITY;
	}
	if (m_Move.y > 20.0f)
	{
		m_Move.y = 20.0f;
	}
	
}

void CMovePlayer::PadOparation(void)
{
	//右スティックを倒した場合、倒した方向に移動
	if (g_pGamePad->GetStickHorizontal() > 0.8f)
	{
		m_Move.x += m_Spd.x;
		m_bMove = true;
		m_bReverse = false;
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
	}
	else if (g_pGamePad->GetStickHorizontal() < -0.8f)
	{
		m_Move.x -= m_Spd.x;
		m_bMove = true;
		m_bReverse = true;
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
	}
	//スティックを離した場合（移動の操作をしていない場合）
	else
	{
		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_Move.x < 0)
		{
			m_Move.x += (m_Spd.x - 0.1f);
			if (m_Move.x > 0)
			{
				m_Move.x = 0;
			}
		}
		else if (m_Move.x > 0)
		{
			m_Move.x -= (m_Spd.x - 0.1f);
			if (m_Move.x < 0)
			{
				m_Move.x = 0;
			}
		}
		else
		{
			m_bMove = false;
		}
	}

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (g_pGamePad->IsKeyPush(XINPUT_A) && !m_bJump)
	{
		m_bJump = true;
		
		m_Move.y = PLAYER_JUMPPOW;
	}
}

void CMovePlayer::KeyOparation(void)
{
	//右スティックを倒した場合、倒した方向に移動
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT) || g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Move.x += m_Spd.x * (g_pInput->IsKeyHold(MOFKEY_LEFT) ? -1 : 1);
		m_bMove = true;
		m_bReverse = g_pInput->IsKeyHold(MOFKEY_LEFT);
	}
	//スティックを離した場合（移動の操作をしていない場合）
	else
	{
		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_Move.x != 0)
		{
			m_Move.x -= (m_Spd.x - 0.1f) * (m_Move.x < 0) ? -1 : 1;
		}
		else
		{
			m_bMove = false;
		}
	}

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		m_bJump = true;

		m_Move.y = PLAYER_JUMPPOW;
	}
}
