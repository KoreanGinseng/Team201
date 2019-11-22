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
m_bClime(false),
m_HP(0)
{
}

//�f�X�g���N�^
CPlayer::~CPlayer(void)
{
}

//������
void CPlayer::Initialize(void)
{
	//
	m_pTexture = g_pTextureManager->GetResource(FileName[TEXTURE_PLAYER]);
	CreateMove(0);
	m_MvCntrl.Initialize();
	m_Anim.Initialize();
	CreateAnim(FileName[ANIMATION_PLAYER]);
	m_MvCntrl.SetSpd(PLAYER_SPEED, PLAYER_JUMPPOW);
	//
	m_bDead = false;
	//
	m_bReverse = false;
	//���W�̏�����
	m_Pos = Vector2(960, 768);
	m_Pos = Vector2(9600, 768);
	//m_Pos = Vector2(4000, 192);
	//HP�̏�����
	m_HP = PLAYER_MAXHP;
	//
	m_bClime = false;
	//�X�L���͈̔͂�������
	m_Skillrang = 0.0f;
	m_Target = 0;
	//
	m_CoolTime = 100.0f;
	//
	m_bTrigger = false;
	//
	m_DamageWait = 0;
}

//�X�V
void CPlayer::Update(void)
{
	//MOVE
	m_MvCntrl.Update();
	m_Pos += m_MvCntrl.GetMove();

	//�X�L��
	Skill();

	//�A�j���[�V�����X�V
	Animation();

	//
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	if (m_HP <= 0)
	{
		m_bDead = true;
	}

	m_bReverse = static_cast<CMovePlayer*>(m_MvCntrl.GetInstance())->GetReverse();
}

//�`��
void CPlayer::Render(Vector2 screenPos)
{
	//
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	CRectangle dr = GetSrcRect();
	//���]�t���O�������Ă���Ƃ��`���`�𔽓]
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, dr);

	RenderDebug(screenPos);
}

//�f�o�b�O�`��
void CPlayer::RenderDebug(Vector2 screenPos)
{
	CGraphicsUtilities::RenderCircle(screenPos.x + GetSrcRect().GetWidth() / 2, screenPos.y + GetSrcRect().GetHeight() / 2, m_Skillrang, MOF_COLOR_RED);
	CGraphicsUtilities::RenderRect(screenPos.x + PLAYER_RECTDIS, screenPos.y + PLAYER_RECTDIS,
		screenPos.x + GetSrcRect().GetWidth() - PLAYER_RECTDIS, screenPos.y + GetSrcRect().GetHeight(), MOF_COLOR_RED);
}

//���
void CPlayer::Release(void)
{
	CCharacter::Release();
	m_SkillTarget.clear();
	m_pTexture = nullptr;
}

//�A�j���[�V��������
void CPlayer::Animation(void)
{
	if (m_MvCntrl.GetMotionNo() != m_Anim.GetMotionNo())
	{
		m_Anim.ChangeAnim(m_MvCntrl.GetMotionNo());
	}

	m_Anim.Update();
}

//�����蔻��
void CPlayer::CollisionStage(const Vector2& over)
{
	m_Pos += over;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ���������
	if (over.y < 0 && m_MvCntrl.GetMove().y > 0)
	{
		m_MvCntrl.SetMove(m_MvCntrl.GetMove().x, 0);
		static_cast<CMovePlayer*>(m_MvCntrl.GetInstance())->ResetJump();
	}
	else if (over.y > 0 && m_MvCntrl.GetMove().y < 0)
	{
		m_MvCntrl.SetMove(m_MvCntrl.GetMove().x, 0);
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if ((over.x < 0 && m_MvCntrl.GetMove().x > 0) || (over.x > 0 && m_MvCntrl.GetMove().x < 0))
	{
		m_MvCntrl.SetMove(0, m_MvCntrl.GetMove().y);
	}
}

void CPlayer::Skill()
{
	//LT�{�^�����������ꍇ�A�X�L��������
	if (g_pGamePad->IsKeyHold(XINPUT_L_TRIGGER) || g_pInput->IsKeyHold(MOFKEY_SPACE))
	{
		m_bTrigger = true;
		if (!m_SkillTarget.empty())
		{
			//LB�܂���RB�Ń^�[�Q�b�g��ύX
			if (g_pGamePad->IsKeyPush(XINPUT_L_BTN) || g_pInput->IsKeyPush(MOFKEY_Z))
			{
				if (--m_Target < 0)
				{
					m_Target = m_SkillTarget.size() - 1;
				}
			}
			else if (g_pGamePad->IsKeyPush(XINPUT_R_BTN) || g_pInput->IsKeyPush(MOFKEY_X))
			{
				if (++m_Target >= m_SkillTarget.size())
				{
					m_Target = 0;
				}
			}

			//�X�L���̔ԍ�
			int skillNo = -1;

			//�߂�
			if (g_pGamePad->IsKeyPush(XINPUT_X) || g_pInput->IsKeyPush(MOFKEY_A))
			{
				skillNo = XINPUT_X;
			}
			//�~�߂�
			else if (g_pGamePad->IsKeyPush(XINPUT_Y) || g_pInput->IsKeyPush(MOFKEY_S))
			{
				skillNo = XINPUT_Y;
			}
			//��΂�
			else if (g_pGamePad->IsKeyPush(XINPUT_B) || g_pInput->IsKeyPush(MOFKEY_D))
			{
				skillNo = XINPUT_B;
			}

			//X||Y||B�̂����ꂩ���������ꍇ
			if (skillNo != -1)
			{
				g_pScore->AddSkillCount();
				if (!m_SkillTarget.empty())
				{
					m_bTrigger = false;
					m_SkillTarget[m_Target]->SetSkill();

					//�X�L���ԍ��̃X�L�����Z�b�g����
					switch (skillNo)
					{
					case XINPUT_X:
						m_SkillTarget[m_Target]->SetBack();
						break;
					case XINPUT_Y:
						m_SkillTarget[m_Target]->SetStop();
						break;
					case XINPUT_B:
						m_SkillTarget[m_Target]->SetTrip();
						break;
					}
					for (int i = 0; i < m_SkillTarget.size(); i++)
					{
						m_SkillTarget[i]->SetTarget(false);
					}
				}
			}
		}
	}
	else if (g_pGamePad->IsKeyPull(XINPUT_L_TRIGGER) || g_pInput->IsKeyPull(MOFKEY_SPACE))
	{
		m_bTrigger = false;
	}

	//�X�L���̉~�ɍ��W�┼�a����
	m_SkillCircle.x = m_Pos.x + GetSrcRect().GetWidth() / 2;
	m_SkillCircle.y = m_Pos.y + GetSrcRect().GetHeight() / 2;
	m_SkillCircle.r = m_Skillrang;

	//�X�L�����������Ă���ꍇ�^�[�Q�b�g�͈̔͂��L����
	if (m_bTrigger)
	{
		m_Skillrang += 10;
		/*m_CoolTime -= 0.1f;*/
		if (m_Skillrang >= PLAYER_MAXSKILLRANGE)
		{
			m_Skillrang = PLAYER_MAXSKILLRANGE;
		}
	}
	else 
	{
		//�������܂��͉����ĂȂ���Ԃ�
		//�^�[�Q�b�g�͈͂�0���傫���ꍇ
		if (m_Skillrang > 0.0f)
		{
			//�X�L���͈͂�0�ɂ��ă^�[�Q�b�g��擪�ɖ߂�(����������)
			m_Skillrang = 0.0f;
			m_Target = 0;
			//�x�N�g���ɗv�f�������Ă���ꍇ
			if (!m_SkillTarget.empty()) 
			{
				//�S�Ẵ^�[�Q�b�g�t���O�����낵�A�v�f��S�ăN���A����
				for (int i = 0; i < m_SkillTarget.size(); i++)
				{
					m_SkillTarget[i]->SetTarget(false);
				}
				m_SkillTarget.clear();
			}
		}
	}
}


void CPlayer::TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray) {

	std::list<CSubstance*> element;
	//�x�N�g���ɓ����Ă���Substance�̃^�[�Q�b�g�̏�����
	for (int i = 0; i < m_SkillTarget.size(); i++)
	{
		m_SkillTarget[i]->SetTarget(false);
	}
	//�x�N�g���̗v�f���N���A
	m_SkillTarget.clear();


	for (int i = 0; i < peneArray->GetArrayCount(); i++)
	{
		if (!(*peneArray)[i]->IsShow())
		{
			continue;
		}

		//�\������Ă��ăX�L���̉~�ɓG���������Ă���ꍇ�A���̓G�̗v�f������
		if (CollisionRectCircle((*peneArray)[i]->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>((*peneArray)[i]));
		}
	}

	for (int i = 0; i < pobjArray->GetArrayCount(); i++)
	{
		if (!(*pobjArray)[i]->IsShow())
		{
			continue;
		}

		//�\������Ă��ăX�L���̉~�ɓG���������Ă���ꍇ�A���̓G�̗v�f������
		if (CollisionRectCircle((*pobjArray)[i]->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>((*pobjArray)[i]));
		}
	}

	for (int i = 0; i < pItemArray->GetArrayCount(); i++)
	{
		if (!(*pItemArray)[i]->IsShow())
		{
			continue;
		}

		//�\������Ă��ăX�L���̉~�ɓG���������Ă���ꍇ�A���̓G�̗v�f������
		if (CollisionRectCircle((*pItemArray)[i]->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>((*pItemArray)[i]));
		}
	}

	//List����̏ꍇ�A���������Ȃ�
	if (element.empty())
	{
		return;
	}

	//�v���C���[�̈ʒu
	float stx = m_Pos.x + GetSrcRect().GetWidth() * 0.5f;
	float sty = m_Pos.y + GetSrcRect().GetHeight();

	//�����v �Ɓ@v++���r���ă\�[�g����
	element.sort(
		[&](CSubstance*& v1, CSubstance*& v2)
		{
			CRectangle rec1 = v1->GetRect();
			CRectangle rec2 = v2->GetRect();

			Vector2 cv1 = rec1.GetCenter();
			Vector2 cv2 = rec2.GetCenter();

			float dx1 = cv1.x - stx;
			float dy1 = cv1.y - sty;
			float d1 = (dx1*dx1 + dy1 * dy1);

			float dx2 = cv2.x - stx;
			float dy2 = cv2.y - sty;
			float d2 = (dx2*dx2 + dy2 * dy2);
			if (d1 > d2) {
				return false;
			}
			return true;
		}
	);

	//�\�[�g���ꂽ�G���I�u�W�F�N�g���x�N�g���ɓ����
	for (auto itr = element.cbegin(); itr != element.cend(); ++itr) 
	{
		m_SkillTarget.push_back(*itr);
	}

	
	if (m_Target > m_SkillTarget.size()-1)
	{
		m_Target = m_SkillTarget.size() - 1;
	}

	//�^�[�Q�b�g�����G�ɓ`����
	for (int i = 0; i < m_SkillTarget.size(); i++)
	{
		if (i == m_Target)
		{
			m_SkillTarget[i]->SetTarget(true);
		}
		else
		{
			m_SkillTarget[i]->SetTarget(false);
		}
	}
}

bool CPlayer::Dmg(CEnemy& ene)
{
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	m_DamageWait = 60;
	if (m_HP > 0)
	{
		g_pScore->AddDamageCount();
		m_HP--;

		if (prec.Left < erec.Left)
		{
			m_MvCntrl.SetMove(-5.0f, m_MvCntrl.GetMove().y);
			m_bReverse = false;
		}
		else
		{
			m_MvCntrl.SetMove(5.0f, m_MvCntrl.GetMove().y);
			m_bReverse = true;
		}
		//m_Motion.ChangeMotion(MOTION_DAMAGE);
	}
	return true;
}