#include "EnemyShot.h"



CEnemyShot::CEnemyShot(void) :
CShot()
{
}


CEnemyShot::~CEnemyShot(void)
{
}

void CEnemyShot::Fire(const Vector2 & startPos)
{
	m_Pos = startPos;
	for (int i = -2; i < 3; i++)
	{
		m_WarpPos[i + 2] = m_Pos + Vector2(100 * i, 0);
	}
	m_bShot = true;
	m_No = CUtilities::Random(5);
	m_Pos = m_WarpPos[m_No];
	m_Move = Vector2(0, 0);

	m_pEnemy->SetPos(m_Pos);
	m_pEnemy->SetShow(true);
	m_pEnemy->SetDead(false);
	m_DeadTime = 300;
	m_EneMove = Vector2(0, 0);
	m_OffsetWait = 180;
	m_WaitCount = m_OffsetWait;
}

void CEnemyShot::Initialize(void)
{
	m_pEnemy = NEW CEnemyPoison();
	m_pEnemy->CreateMotion(FileName[ANIMATION_ENEMY_1 + ENEMY_POISUNMASH]);
	m_pEnemy->SetTexture(g_pTextureManager->GetTexture(FileName[TEXTURE_ENEMY_1 + ENEMY_POISUNMASH]));
	m_pEnemy->GetSrcRectArrayPointer()->Add(m_pEnemy->GetSrcAddRect());
	m_pEnemy->Initialize();
	m_pEnemyArrayPointer->Add(m_pEnemy);
}

void CEnemyShot::Update(void)
{
	if (!m_pEnemy->IsReverse() || m_pEnemy->GetMove().x > 0)
	{
		m_pEnemy->SetReverse(true);
		m_pEnemy->SetMove(Vector2(-m_pEnemy->GetMove().x, m_pEnemy->GetMove().y));
	}

	if (m_pEnemy->IsAnimStop())
	{
		m_WaitCount--;
		if (m_WaitCount < 0)
		{
			m_WaitCount = m_OffsetWait;
			m_pEnemy->SetAnimStop(false);
			m_bAnimStop = false;
			m_SubStatus = SUBSTATUS_NOMAL;
		}
		return;
	}

	if (m_DeadTime-- < 0 || m_pEnemy->IsDead())
	{
		m_pEnemy->SetDead(true);
		m_bShot = false;
	}

	m_WarpTime--;
	if (m_WarpTime < 0)
	{
		m_WarpTime = m_OffsetWarpTime;
		int no = m_No;
		while (no == m_No)
		{
			m_No = CUtilities::Random(5);
		}
		m_Pos.x = m_WarpPos[m_No].x + m_EneMove.x;
		m_pEnemy->SetPos(Vector2(m_Pos.x, m_pEnemy->GetPos().y));
	}
	m_pEnemy->Update();
	m_EneMove += m_pEnemy->GetMove();
	if (m_EneMove.y > GRAVITYMAX)
	{
		m_EneMove.y = GRAVITYMAX;
	}
}

void CEnemyShot::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pEnemy->Render(m_pEnemy->GetPos() - scroll);
}

void CEnemyShot::SetArray(CDynamicArray<CEnemy*>* pArray)
{
	m_pEnemyArrayPointer = pArray;
}

void CEnemyShot::SetWorpTime(const int & time)
{
	m_OffsetWarpTime = time;
}
