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
	m_SkillCircle(),
	m_bCntrl(true)
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
	m_pTexture = g_pTextureManager->GetTexture(FileName[TEXTURE_PLAYER]);
	SpriteAnimationCreate* pAnim;
	pAnim = g_pAnimManager->GetAnimation(FileName[ANIMATION_PLAYER])->GetAnim();
	m_Motion.Create(pAnim, ANIM_COUNT);
	m_SrcRectArray.Add(GetSrcRect());
	m_bDead = false;
	m_bReverse = false;
	//���W�̏�����
	m_Pos = Vector2(200, 768);
	//HP�̏�����
	m_HP = PLAYER_MAXHP;
	m_bClime = false;
	//�X�L���͈̔͂�������
	m_Skillrang = 0.0f;
	m_Target = 0;
	m_bTrigger = false;
	m_DamageWait = 0;
	m_bAttack = false;
	if (g_pInput->GetGamePadCount())
	{
		m_bKey = false;
	}

	if (CCordinate::IsLastBoss())
	{
		CAnimationData* pData = g_pAnimManager->GetAnimation("PlayerAnim002.bin");
		m_SordMotion.Create(pData->GetAnim(), pData->GetAnimCount());
		m_pTexture = g_pTextureManager->GetTexture(pData->GetTextureName());
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

	//
	if (GetRect().Left < CCordinate::GetStageRect().Left)
	{
		m_Move.x = 0;
		m_Pos.x = CCordinate::GetStageRect().Left - PLAYER_RECTDIS;
	}
	else if (GetRect().Right > CCordinate::GetStageRect().Right)
	{
		m_Move.x = 0;
		m_Pos.x = CCordinate::GetStageRect().Right - GetRect().GetWidth() - PLAYER_RECTDIS;
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

#ifdef _DEBUG
	Vector2 mousePos;
	g_pInput->GetMousePos(mousePos);
	if (g_pInput->IsKeyHold(MOFKEY_LSHIFT))
	{
		m_Pos = CCamera2D::GetSScroll() + mousePos;
	}
#endif // _DEBUG


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
	if (CCordinate::IsLastBoss())
	{
		dr = m_SordMotion.GetSrcRect();
	}

	//���]�t���O�������Ă���Ƃ��`���`�𔽓]
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pTexture->Render(screenPos.x, screenPos.y, dr);
#ifdef _DEBUG
	if (gbDebug)
	{
		//Vector2 scroll = CCamera2D::GetSScroll();
		CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
				screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
		}
		CGraphicsUtilities::RenderRect(GetAttackRect() - scroll, MOF_COLOR_GREEN);
	}
#endif // _DEBUG
}

void CPlayer::RenderCircle(const Vector2 & screenPos)
{
	CRectangle dr = GetSrcRect();
	if (CCordinate::IsLastBoss())
	{
		dr = m_SordMotion.GetSrcRect();
	}
	//���]�t���O�������Ă���Ƃ��`���`�𔽓]
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	//CGraphicsUtilities::RenderFillCircle(m_SkillCircle.x - scroll.x, m_SkillCircle.y - scroll.y, m_SkillCircle.r, MOF_ARGB(128, 255, 0, 0));
	//204,62,233
	//120,0,193
	CGraphicsUtilities::RenderFillCircle(m_SkillCircle.x - scroll.x, m_SkillCircle.y - scroll.y, m_SkillCircle.r, MOF_ARGB(128, 120, 0, 193));
	for (int i = m_SkillCircle.r - 1; i < m_SkillCircle.r + 1; i++)
	{
		CGraphicsUtilities::RenderCircle(m_SkillCircle.x - scroll.x, m_SkillCircle.y - scroll.y, i, MOF_ARGB(255, 120, 0, 193));
	}
	m_pTexture->Render(screenPos.x, screenPos.y, dr, MOF_ARGB(128, 255, 255, 255));
}

//���
void CPlayer::Release(void)
{
	CCharacter::Release();
	m_SkillTarget.clear();
	m_pTexture = nullptr;
	m_SordMotion.Release();
}

void CPlayer::Move(void)
{
	m_KeyConfig.moveRight = m_bKey ? g_pInput->IsKeyHold(MOFKEY_RIGHT) : (g_pGamePad->GetStickHorizontal() > 0.8f);
	m_KeyConfig.moveLeft = m_bKey ? g_pInput->IsKeyHold(MOFKEY_LEFT) : (g_pGamePad->GetStickHorizontal() < -0.8f);
	m_KeyConfig.jump = m_bKey ? g_pInput->IsKeyHold(MOFKEY_UP) : (g_pGamePad->IsKeyPush(XINPUT_A));
	m_KeyConfig.clime = m_bKey ? g_pInput->IsKeyHold(MOFKEY_UP) : (g_pGamePad->GetStickVertical() > 0.8f);
	m_KeyConfig.fall = m_bKey ? g_pInput->IsKeyHold(MOFKEY_DOWN) : (g_pGamePad->GetStickVertical() < -0.8f);

	if (m_KeyConfig.skillStance && !m_bMove && !m_bJump && !m_bClime && !m_bAttack)
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
		if (m_bClime)
		{
			m_Move.y -= GRAVITY;
		}
		m_Move.y += GRAVITY;
		if (m_Move.y > 20.0f)
		{
			m_Move.y = 20.0f;
		}
		return;
	}

	//�E�X�e�B�b�N��|�����ꍇ�A�|���������Ɉړ�
	if (m_KeyConfig.moveRight && m_bCntrl && !m_bAttack)
	{
		m_Move.x += PLAYER_SPEED;
		m_bMove = true;
		m_bReverse = false;
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
	}
	else if (m_KeyConfig.moveLeft && m_bCntrl && !m_bAttack)
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
	if (m_KeyConfig.jump && !m_bJump && !m_bClime && m_bCntrl && !m_bAttack)
	{
		m_bJump = true;
		m_Move.y = PLAYER_JUMPPOW;
		g_pSoundManager->PlaySE("jump09.mp3");
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
	CSpriteMotionController* pMotion;
	if (CCordinate::IsLastBoss())
	{
		pMotion = &m_SordMotion;
	}
	else
	{
		pMotion = &m_Motion;
	}
	if (m_bJump && pMotion->GetMotionNo() != ANIM_JUMPUP && m_Move.y < 0)
	{
		pMotion->ChangeMotion(ANIM_JUMPUP);
	}
	else if (m_bJump && pMotion->GetMotionNo() != ANIM_JUMPDOWN && m_Move.y >= 0)
	{
		pMotion->ChangeMotion(ANIM_JUMPDOWN);
	}
	else if (m_bMove && pMotion->GetMotionNo() != ANIM_MOVE && !m_bJump)
	{
		pMotion->ChangeMotion(ANIM_MOVE);
	}
	else if (m_bTrigger && pMotion->GetMotionNo() != ANIM_SKILLSTANCE && !m_bJump && !m_bMove)
	{
		pMotion->ChangeMotion(ANIM_SKILLSTANCE);
	}
	else if (pMotion->GetMotionNo() != ANIM_WAIT && !m_bJump && !m_bMove && !m_bTrigger && !m_bAttack)
	{
		pMotion->ChangeMotion(ANIM_WAIT);
	}
	if (m_bAttack && CCordinate::IsLastBoss() && !m_bJump && !m_bTrigger && !m_bMove)
	{
		if (pMotion->GetMotionNo() != ANIM_COUNT)
		{
			pMotion->ChangeMotion(ANIM_COUNT);
		}
	}
	pMotion->AddTimer(CUtilities::GetFrameSecond());
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
	m_KeyConfig.selectNext = m_bKey ? g_pInput->IsKeyPush(MOFKEY_X) : g_pGamePad->IsKeyPush(XINPUT_R_BTN);
	m_KeyConfig.selectBack = m_bKey ? g_pInput->IsKeyPush(MOFKEY_Z) : g_pGamePad->IsKeyPush(XINPUT_L_BTN);
	m_KeyConfig.skillBack = m_bKey ? g_pInput->IsKeyPush(MOFKEY_A) : (g_pGamePad->IsKeyPush(XINPUT_X));
	m_KeyConfig.skillStop = m_bKey ? g_pInput->IsKeyPush(MOFKEY_S) : (g_pGamePad->IsKeyPush(XINPUT_Y));
	m_KeyConfig.skillSkip = m_bKey ? g_pInput->IsKeyPush(MOFKEY_D) : (g_pGamePad->IsKeyPush(XINPUT_B));
	m_KeyConfig.skillStancePull = m_bKey ? g_pInput->IsKeyPull(MOFKEY_SPACE) : g_pGamePad->IsKeyPull(XINPUT_L_TRIGGER);
	m_KeyConfig.attack = m_bKey ? g_pInput->IsKeyPull(MOFKEY_C) : g_pGamePad->IsKeyPull(XINPUT_R_TRIGGER);

	m_bSkillEne = false;
	m_bSkillObjBack = false;
	m_bSkillObjNomal = false;
	m_bSkillObjTrip = false;

	if (m_KeyConfig.attack && m_bCntrl && CCordinate::IsLastBoss() && !m_bMove && !m_bJump && !m_bTrigger)
	{
		m_bAttack = true;
	}
	if (m_bAttack)
	{
		if (m_SordMotion.GetMotionNo() == ANIM_COUNT && m_SordMotion.IsEndMotion())
		{
			m_bAttack = false;
		}
	}

	//LT�{�^�����������ꍇ�A�X�L��������
	if (m_KeyConfig.skillStance && !m_bMove && !m_bJump && !m_bClime && m_bCntrl && !m_bAttack)
	{
		if (!g_pSoundManager->GetSoundSE("Skill.mp3")->GetSoundBuffer()->IsPlay())
		{
			g_pSoundManager->GetSoundSE("Skill.mp3")->GetSoundBuffer()->Play();
		}
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
		if (m_SkillTarget.size() > 0)
		{
			if (m_SkillTarget[m_Target]->GetSubType() == SUB_ENE)
			{
				m_bSkillEne = true;
			}
			else
			{
				switch (m_SkillTarget[m_Target]->GetStatus())
				{
				case SUBSTATUS_NOMAL:
					m_bSkillObjNomal = true;
					break;
				case SUBSTATUS_BACK:
					m_bSkillObjBack = true;
					break;
				case SUBSTATUS_TRIP:
					m_bSkillObjTrip = true;
					break;
				default:
					break;
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

		//if (!g_pSoundManager->GetSoundSE("Skill.mp3")->IsPlay())
		//{
		//	//g_pSoundManager->GetSoundSE("Skill.mp3")->GetSoundBuffer()->SetLoop(TRUE);
		//	g_pSoundManager->PlaySE("Skill.mp3");
		//}
	}
	else
	{
		g_pSoundManager->GetSoundSE("Skill.mp3")->GetSoundBuffer()->Stop();
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

#include	"Shot.h"
void CPlayer::TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray) {

	std::list<CSubstance*> element;
	//�x�N�g���ɓ����Ă���Substance�̃^�[�Q�b�g�̏�����
	for (int i = 0; i < m_SkillTarget.size(); i++)
	{
		m_SkillTarget[i]->SetTarget(false);
	}
	//�x�N�g���̗v�f���N���A
	m_SkillTarget.clear();

	for (int i = 0; i < CShot::GetShotLists()->GetArrayCount(); i++)
	{
		if (!CShot::GetShotLists()->GetData(i)->IsShow() || !CShot::GetShotLists()->GetData(i)->IsSelectTarget())
		{
			MOF_PRINTLOG("CONTINUE\n");
			continue;
		}
		MOF_PRINTLOG("TRUE\n");

		//�\������Ă��ăX�L���̉~��TAMA���������Ă���ꍇ�A���̓G�̗v�f������
		if (CollisionRectCircle(CShot::GetShotLists()->GetData(i)->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>(CShot::GetShotLists()->GetData(i)));
		}
	}

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


	if (m_Target > m_SkillTarget.size() - 1)
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

	if (!prec.CollisionRect(erec))
	{
		return false;
	}

	if (ene.GetEnemyType() == ENEMY_MASH || ene.GetEnemyType() == ENEMY_POISUNMASH)
	{
		if (prec.Bottom - 5 < erec.Top && prec.Bottom + 5 > erec.Top)
		{
			m_Move.y = PLAYER_JUMPPOW * 0.5f;
			ene.Dmg(1);
			return false;
		}
	}
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	m_KeyConfig.skillStance = false;
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
	g_pSoundManager->PlaySE("Dmg.mp3");
	return true;
}

bool CPlayer::Dmg(const int & dmg)
{
	if (m_DamageWait > 0)
	{
		return false;
	}
	m_HP -= dmg;
	m_DamageWait = 60;
	if (m_HP < 0)
	{
		m_bDead = true;
	}

	g_pSoundManager->PlaySE("Dmg.mp3");
	return true;
}

bool CPlayer::IsAttack(void) const
{
	return m_bAttack;
}

CRectangle CPlayer::GetAttackRect(void)
{
	CRectangle rect(0, 0, 0, 0);
	if (m_bAttack)
	{
		rect = CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SordMotion.GetSrcRect().GetWidth(), m_Pos.y + m_SordMotion.GetSrcRect().GetHeight());
		rect.Expansion(-80, -40);
		rect.Left += 100;
		if (m_bReverse)
		{
			rect -= Vector2(100, 0);
		}
	}
	return rect;
}
