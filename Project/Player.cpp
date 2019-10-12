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
m_Stock(3)
{
}

//�f�X�g���N�^
CPlayer::~CPlayer(void)
{
}

//������
void CPlayer::Initialize(void)
{
	//�摜�f�[�^�̃Z�b�g
	m_pTexture = g_pAnimManager->GetResource(FileName[0])->GetTexture();
	//�A�j���[�V�����f�[�^�̃Z�b�g
	m_pMotion = g_pAnimManager->GetResource("playerAnim.bin")->GetMotion();
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
	//�X�L���͈̔͂�������
	m_Skillrang = 0.0f;
	//
	m_CoolTime = 100.0f;
	//
	m_bTrigger = false;
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

	//�X�L��
	Skill();

	//�A�j���[�V�����X�V
	Animation();
}

//�`��
void CPlayer::Render(Vector2 screenPos)
{
	CRectangle dr = m_SrcRect;
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
	/*CGraphicsUtilities::RenderString(10, 200, "%.1f", m_Skillrang);
	CGraphicsUtilities::RenderString(10, 240, "%.1f", m_CoolTime);*/
	CGraphicsUtilities::RenderCircle(screenPos.x + m_SrcRect.GetWidth() / 2, screenPos.y + m_SrcRect.GetHeight() / 2, m_Skillrang, MOF_COLOR_RED);
	CGraphicsUtilities::RenderRect(screenPos.x + PLAYER_RECTDIS, screenPos.y + PLAYER_RECTDIS,
		screenPos.x + m_SrcRect.GetWidth() - PLAYER_RECTDIS, screenPos.y + m_SrcRect.GetHeight(), MOF_COLOR_RED);
}

//���
void CPlayer::Release(void)
{
	m_pMotion = nullptr;
	m_pTexture = nullptr;
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
		else
		{
			m_bMove = false;
		}
	}

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pGamePad->IsKeyPush(GAMEKEY_A) && !m_bJump)
	{
		Jump();
	}

	//LT�{�^�����������ꍇ�A�X�L��������
	if (g_pGamePad->GetPadState()->lZ > 500/* && m_CoolTime > 0.0f*/)
	{
		m_bTrigger = true;
	}
	else if (g_pGamePad->GetPadState()->lZ < 1)
	{
		m_bTrigger = false;
	}
	//Skill();
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
		else
		{
			m_bMove = false;
		}
	}

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		Jump();
	}

	//�X�y�[�X�L�[���������ꍇ�A�X�L��������
	if (g_pInput->IsKeyHold(MOFKEY_SPACE) /*&& m_CoolTime > 0.0f*/)
	{
		m_bTrigger = true;
	}
	else if (g_pInput->IsKeyPull(MOFKEY_SPACE))
	{
		m_bTrigger = false;
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
		m_bReverse = false;
		m_Move.x += m_Spd.x;
		//�ő呬�x�𒴂��Ȃ��悤�ɂ���
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
		break;

	case WAY_LEFT:
		m_bReverse = true;
		m_Move.x -= m_Spd.x;
		//�ő呬�x�𒴂��Ȃ��悤�ɂ���
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
		break;
	}
	m_bMove = true;
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

//�A�j���[�V��������
void CPlayer::Animation(void)
{
	//�ړ����Ȃ�ړ����[�V�����ɂ���
	if(m_bMove && m_pMotion->GetMotionNo() == ANIM_WAIT)
	{
		m_pMotion->ChangeMotion(ANIM_MOVE);
	}
	if(!m_bMove && m_pMotion->GetMotionNo() == ANIM_MOVE)
	{
		m_pMotion->ChangeMotion(ANIM_WAIT);
	}

	//�A�j���[�V�������Z
	m_pMotion->AddTimer(CUtilities::GetFrameSecond());

	//�A�j���[�V������`�X�V
	m_SrcRect = m_pMotion->GetSrcRect();
}

//�W�����v����
void CPlayer::Jump(void)
{
	//�W�����v���ʉ��̃e�X�g����
	g_pSoundManager->GetResource(FileName[10])->Play();

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

void CPlayer::Skill() {

	//�X�L���̉~�ɍ��W�┼�a����
	m_SkillCircle.x = m_Pos.x + m_SrcRect.GetWidth() / 2;
	m_SkillCircle.y = m_Pos.y + m_SrcRect.GetHeight() / 2;
	m_SkillCircle.r = m_Skillrang;

	////LT�{�^�����������ꍇ�A�X�L��������
	//if (g_pGamePad->GetPadState()->lZ > 500/*&&m_CoolTime>0.0f*/) {

	//	m_bTrigger = true;

	//}
	//else if (g_pGamePad->GetPadState()->lZ < 1) {

	//	m_bTrigger = false;

	//}

	//�X�L�����������Ă���ꍇ�^�[�Q�b�g�͈̔͂��L����
	if (m_bTrigger) {

		m_Skillrang += 10;

		/*m_CoolTime -= 0.1f;*/

		if (m_Skillrang >= PLAYER_MAXSKILLRANGE) {

			m_Skillrang = PLAYER_MAXSKILLRANGE;

		}
	}
	else {
		//�������܂��͉����ĂȂ���Ԃ�
		//�^�[�Q�b�g�͈͂�0���傫���ꍇ
		if (m_Skillrang > 0.0f) {
			//�X�L���͈͂�0�ɂ��ă^�[�Q�b�g��擪�ɖ߂�(����������)
			m_Skillrang = 0.0f;
			m_Target = 0;
			//�x�N�g���ɗv�f�������Ă���ꍇ
			if (!m_SkillTarget.empty()) {
				//�S�Ẵ^�[�Q�b�g�t���O�����낵�A�v�f��S�ăN���A����
				for (int i = 0; i < m_SkillTarget.size(); i++) {

					m_SkillTarget[i]->SetTarget(false);

				}

				m_SkillTarget.clear();

			}

		}

	}


}


void CPlayer::SkillColision(CEnemy* pene, int eneCount, CObject* pobj, int objCount) {


	list<CSubstance*> element;
	//�x�N�g���ɓ����Ă���Substance�̃^�[�Q�b�g�̏�����
	for (int i = 0; i < m_SkillTarget.size(); i++) {

		m_SkillTarget[i]->SetTarget(false);

	}
	//�x�N�g���̗v�f���N���A
	m_SkillTarget.clear();


	for (int i = 0; i < eneCount; i++) {

		if (!pene[i].GetShow()) {

			continue;

		}

		//�\������Ă��ăX�L���̉~�ɓG���������Ă���ꍇ�A���̓G�̗v�f������
		if (CollisionRectCircle(pene[i].GetRect(), m_SkillCircle)) {

			element.push_back(&pene[i]);

		}

	}

	for (int i = 0; i < objCount; i++) {

		if (!pobj[i].GetShow()) {

			continue;

		}

		//�\������Ă��ăX�L���̉~�ɓG���������Ă���ꍇ�A���̓G�̗v�f������
		if (CollisionRectCircle(pobj[i].GetRect(), m_SkillCircle)) {

			element.push_back(&pobj[i]);

		}


	}

	//List����̏ꍇ�A���������Ȃ�
	if (element.empty()) {

		return;

	}



	//�v���C���[�̈ʒu
	float stx = m_Pos.x + m_SrcRect.GetWidth()*0.5f;
	float sty = m_Pos.y + m_SrcRect.GetHeight();



		//�����v �Ɓ@v++���r���ă\�[�g����
	element.sort(
		[&](CSubstance*& v1, CSubstance*& v2) {

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

	/*int no = 0;
	for (auto itr = element.cbegin(); itr != element.cend(); ++itr) {
		MOF_PRINTLOG("%d[%f/%f]\n", no++, (*itr)->GetRect().GetCenter().x, (*itr)->GetRect().GetCenter().y);
	}*/

	//�\�[�g���ꂽ�G���I�u�W�F�N�g���x�N�g���ɓ����
	for (auto itr = element.cbegin(); itr != element.cend(); ++itr) {

		m_SkillTarget.push_back(*itr);
	}

	//LB�܂���RB�Ń^�[�Q�b�g��ύX
	if (g_pGamePad->IsKeyPush(GAMEKEY_LB)) {

		m_Target--;

		if (m_Target < 0) {

			m_Target = m_SkillTarget.size() - 1;

		}

	}
	else if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {

		m_Target++;

		if (m_Target >= m_SkillTarget.size()) {

			m_Target = 0;

		}

	}

	//�^�[�Q�b�g�����G�ɓ`����
	for (int i = 0; i < m_SkillTarget.size(); i++) {

		if (i == m_Target) {

			m_SkillTarget[i]->SetTarget(true);

		}
		else {

			m_SkillTarget[i]->SetTarget(false);

		}
	}

	//RT�g���K�[���������Ƃ��I�𒆂̓G�ɃX�L�����g�p
	if (g_pGamePad->GetPadState()->lZ < 100.0f) {
		
		m_bTrigger = false;

		m_SkillTarget[m_Target]->SetSkill();

		for (int i = 0; i < m_SkillTarget.size(); i++) {

			m_SkillTarget[i]->SetTarget(false);

		}



	}


}