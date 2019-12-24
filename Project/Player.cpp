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
CCharacter(),
m_bKey(true),
m_bJump(false),
m_SkillTarget(),
m_bTrigger(false),
m_bClime(false),
m_Target(0),
m_Skillrang(0),
m_SkillCircle()
{
	CCordinate::SetPlayerPos(&m_Pos);
}

//�f�X�g���N�^
CPlayer::~CPlayer(void)
{
	Release();
}

//������
void CPlayer::Initialize(void)
{
	//�摜�̃Z�b�g
	m_pTexture = g_pTextureManager->GetResource(FileName[TEXTURE_PLAYER]);
	SpriteAnimationCreate* pAnim;
	pAnim = g_pAnimManager->GetResource(FileName[ANIMATION_PLAYER])->GetAnim();
	m_Motion.Create(pAnim, ANIM_COUNT);
	m_SrcRectArray.Add(GetSrcRect());
	m_bDead = false;
	m_bReverse = false;
	//���W�̏�����
	m_Pos = Vector2(9600, 768);
	m_Pos = Vector2(4000, 192);
	m_Pos = Vector2(960, 768);
	m_Pos = Vector2(200, 768);
	//HP�̏�����
	m_HP = PLAYER_MAXHP;
	m_bClime = false;
	//�X�L���͈̔͂�������
	m_Skillrang = 0.0f;
	m_Target = 0;
	m_bTrigger = false;
	m_DamageWait = 0;
	if (g_pInput->GetGamePadCount())
	{
		m_bKey = false;
	}
}

//�X�V
void CPlayer::Update(void)
{
	//�X�L��
	Skill();

	//MOVE
	Move();
	m_Pos += m_Move;

	//�A�j���[�V�����X�V
	Animation();

	//
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	if (GetRect().Left < CCordinate::GetStageRect().Left)
	{
		m_Pos.x = CCordinate::GetStageRect().Left;
	}
	else if (GetRect().Right > CCordinate::GetStageRect().Right)
	{
		m_Pos.x = CCordinate::GetStageRect().Right - GetRect().GetWidth();
	}
	if (GetRect().Top > CCordinate::GetStageRect().Bottom)
	{
		m_DamageWait = 60;
		m_HP--;
		m_Pos = CCordinate::GetSavePoint();
	}

	if (m_HP <= 0)
	{
		m_bDead = true;
	}
}

//�`��
void CPlayer::Render(const Vector2& screenPos)
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
#ifdef _DEBUG
	Vector2 scroll = CCamera2D::GetSScroll();
	CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
	CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
	for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
	{
		CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
			screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
	}
#endif // _DEBUG
}

//���
void CPlayer::Release(void)
{
	CCharacter::Release();
	m_SkillTarget.clear();
	m_pTexture = nullptr;
}

void CPlayer::Move(void)
{
	m_KeyConfig.moveRight   = m_bKey ? g_pInput->IsKeyHold(MOFKEY_RIGHT)  : (g_pGamePad->GetStickHorizontal() > 0.8f);
	m_KeyConfig.moveLeft    = m_bKey ? g_pInput->IsKeyHold(MOFKEY_LEFT)   : (g_pGamePad->GetStickHorizontal() < -0.8f);
	m_KeyConfig.jump        = m_bKey ? g_pInput->IsKeyHold(MOFKEY_UP)     : (g_pGamePad->IsKeyPush(XINPUT_A));
	m_KeyConfig.clime       = m_bKey ? g_pInput->IsKeyHold(MOFKEY_UP)     : (g_pGamePad->GetStickVertical() > 0.8f);
	m_KeyConfig.fall        = m_bKey ? g_pInput->IsKeyHold(MOFKEY_DOWN)   : (g_pGamePad->GetStickVertical() < -0.8f);

	if (m_KeyConfig.skillStance && !m_bMove && !m_bJump && !m_bClime)
	{
		return;
	}

	//�E�X�e�B�b�N��|�����ꍇ�A�|���������Ɉړ�
	if (m_KeyConfig.moveRight)
	{
		m_Move.x += PLAYER_SPEED;
		m_bMove = true;
		m_bReverse = false;
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
	}
	else if (m_KeyConfig.moveLeft)
	{
		m_Move.x -= PLAYER_SPEED;
		m_bMove = true;
		m_bReverse = true;
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
	}
	//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else
	{
		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_Move.x < 0)
		{
			m_Move.x += (PLAYER_SPEED - 0.1f);
			if (m_Move.x > 0)
			{
				m_Move.x = 0;
			}
		}
		else if (m_Move.x > 0)
		{
			m_Move.x -= (PLAYER_SPEED - 0.1f);
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

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (m_KeyConfig.jump && !m_bJump && !m_bClime)
	{
		m_bJump = true;
		m_Move.y = PLAYER_JUMPPOW;
	}
	else if (m_KeyConfig.clime && m_bClime)
	{
		m_Move.y = -3.0f;
	}
	else if (m_KeyConfig.fall && m_bClime)
	{
		m_Move.y = 3.0f;
	}
	else if (m_bClime)
	{
		m_Move.y = 0;
	}

	if (m_bClime)
	{
		m_Move.y -= GRAVITY;
	}
	m_Move.y += GRAVITY;
	if (m_Move.y > 20.0f)
	{
		m_Move.y = 20.0f;
	}
}

//�A�j���[�V��������
void CPlayer::Animation(void)
{
	if (m_bJump && m_Motion.GetMotionNo() != ANIM_JUMPUP && m_Move.y < 0)
	{
		m_Motion.ChangeMotion(ANIM_JUMPUP);
	}
	else if (m_bJump && m_Motion.GetMotionNo() != ANIM_JUMPDOWN && m_Move.y >= 0)
	{
		m_Motion.ChangeMotion(ANIM_JUMPDOWN);
	}
	else if (m_bMove && m_Motion.GetMotionNo() != ANIM_MOVE && !m_bJump)
	{
		m_Motion.ChangeMotion(ANIM_MOVE);
	}
	else if (m_bTrigger && m_Motion.GetMotionNo() != ANIM_SKILLSTANCE && !m_bJump && !m_bMove)
	{
		m_Motion.ChangeMotion(ANIM_SKILLSTANCE);
	}
	else if (m_Motion.GetMotionNo() != ANIM_WAIT && !m_bJump && !m_bMove && !m_bTrigger)
	{
		m_Motion.ChangeMotion(ANIM_WAIT);
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

//�����蔻��
void CPlayer::CollisionStage(const Vector2& over)
{
	m_Pos += over;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ���������
	if (over.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
		m_bJump = false;
	}
	else if (over.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if ((over.x < 0 && m_Move.x > 0) || (over.x > 0 && m_Move.x < 0))
	{
		m_Move.x = 0;
	}
}

CRectangle CPlayer::GetRect(void)
{
	CRectangle r = CCharacter::GetRect();
	r.Expansion(-PLAYER_RECTDIS, 0);
	r.Top += 20;
	r.Bottom -= 30;
	return r;
}

void CPlayer::Skill(void)
{
	m_KeyConfig.skillStance = m_bKey ? g_pInput->IsKeyHold(MOFKEY_SPACE) : g_pGamePad->IsKeyHold(XINPUT_L_TRIGGER);
	m_KeyConfig.selectNext  = m_bKey ? g_pInput->IsKeyPush(MOFKEY_X)     : g_pGamePad->IsKeyPush(XINPUT_R_BTN);
	m_KeyConfig.selectBack  = m_bKey ? g_pInput->IsKeyPush(MOFKEY_Z)     : g_pGamePad->IsKeyPush(XINPUT_L_BTN);
	m_KeyConfig.skillBack   = m_bKey ? g_pInput->IsKeyPush(MOFKEY_A)     : (g_pGamePad->IsKeyPush(XINPUT_X));
	m_KeyConfig.skillStop   = m_bKey ? g_pInput->IsKeyPush(MOFKEY_S)     : (g_pGamePad->IsKeyPush(XINPUT_Y));
	m_KeyConfig.skillSkip   = m_bKey ? g_pInput->IsKeyPush(MOFKEY_D)     : (g_pGamePad->IsKeyPush(XINPUT_B));
	m_KeyConfig.skillStancePull = m_bKey ? g_pInput->IsKeyPull(MOFKEY_SPACE) : g_pGamePad->IsKeyPull(XINPUT_L_TRIGGER);
	//LT�{�^�����������ꍇ�A�X�L��������
	if (m_KeyConfig.skillStance && !m_bMove && !m_bJump && !m_bClime)
	{
		m_bTrigger = true;
		if (!m_SkillTarget.empty())
		{
			//LB�܂���RB�Ń^�[�Q�b�g��ύX
			if (m_KeyConfig.selectBack)
			{
				if (--m_Target < 0)
				{
					m_Target = m_SkillTarget.size() - 1;
				}
			}
			else if (m_KeyConfig.selectNext)
			{
				if (++m_Target >= m_SkillTarget.size())
				{
					m_Target = 0;
				}
			}

			//�X�L���̔ԍ�
			int skillNo = -1;

			//�߂�
			if (m_KeyConfig.skillBack)
			{
				skillNo = XINPUT_X;
			}
			//�~�߂�
			else if (m_KeyConfig.skillStop)
			{
				skillNo = XINPUT_Y;
			}
			//��΂�
			else if (m_KeyConfig.skillSkip)
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

					//�X�L���ԍ��̃X�L�����Z�b�g����
					switch (skillNo)
					{
					case XINPUT_X:
						m_SkillTarget[m_Target]->Back();
						break;
					case XINPUT_Y:
						m_SkillTarget[m_Target]->Stop();
						break;
					case XINPUT_B:
						m_SkillTarget[m_Target]->Trip();
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
	else if (m_KeyConfig.skillStancePull)
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
		if (!(*peneArray)[i]->IsShow() || !(*peneArray)[i]->IsSelectTarget())
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
		if (!(*pobjArray)[i]->IsShow() || !(*pobjArray)[i]->IsSelectTarget())
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
		if (!(*pItemArray)[i]->IsShow() || !(*pItemArray)[i]->IsSelectTarget())
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
			m_Move.x = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_Move.x = 5.0f;
			m_bReverse = true;
		}
		//m_Motion.ChangeMotion(MOTION_DAMAGE);
	}
	return true;
}