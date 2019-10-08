#include		"Player.h"
#include		"GameDefine.h"

//�Q�[���p�b�h����L�[�{�[�h�ւ̐؂�ւ��t���O
bool	g_OperationDebug = true;
//�L�[�{�[�h�A�Q�[���p�b�h�̃e�X�g������@�̐����̕\���t���O
bool	g_PadRenderDebug = false;
bool	g_KeyRenderDebug = false;

CPlayer::CPlayer() : m_SkillTarget(NULL) {
	//�I�u�W�F�N�g�������̏�����
	m_Skillrang = 0.0f;

	m_CoolTime = 0.0f;

	m_Target = 0;

	m_PosX = 0;
	m_PosY = 0;

	m_MoveX = 0;
	m_MoveY = 0;

	m_MoveX2 = 0;
	m_MoveY2 = 0;

	m_Hp = PLAYER_MAXHP;
	m_Life = PLAYER_MAXLIFE;

	m_bJump = false;
	m_bPowerUp = false;
	m_bTrigger = false;
	m_bSkill = false;


}

CPlayer::~CPlayer() {

	Release();

}

bool CPlayer::Load() {
	//HP�e�N�X�`���[�̓ǂݍ���
	if (!m_HpTexture.Load("Hp.png")) {

		return false;

	}

	return true;

}

void CPlayer::Initialize() {
	//�X�L���͈̔͂�������
	m_Skillrang = 0.0f;
	
	m_CoolTime = 100.0f;

	m_bTrigger = false;

	//���W�̏�����
	m_PosX = g_pGraphics->GetTargetWidth() / 2;
	m_PosY = 0;
	//�ړ��ʂ̏�����
	m_MoveX = 0;
	m_MoveY = 0;
	//HP�̏�����
	m_Hp = PLAYER_MAXHP;
	//�c�@�̏�����
	m_Life = PLAYER_MAXLIFE;
	//�W�����v�t���O�̏�����
	m_bJump = false;
	//�p���[�A�b�v�t���O�̏�����
	m_bPowerUp = false;
	//�X�L���̔����t���O��������
	m_bTrigger = false;


}

void CPlayer::Update() {

	
	//����̍X�V
	Operation();
	//�c�@�����̍X�V
	LifeDecrease();

	
}

void CPlayer::Operation() {

	//�G���^�[�L�[���������ꍇ�A�Q�[���p�b�h����L�[�{�[�h�ɑ����؂�ւ���
	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		g_OperationDebug = !g_OperationDebug;
	}

	//�R���g���[���[��PC�ɐڑ�����Ă���ꍇ����ł���
	if (g_pInput->GetGamePadCount() && g_OperationDebug) {

		g_KeyRenderDebug = false;

		//�X�^�[�g�{�^�����������ꍇ�A�e�X�g������@�̐�����\��
		if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

			g_PadRenderDebug = !g_PadRenderDebug;
		}

		PadOperation();


	}
	//�L�[�{�[�h����
	else {

		g_PadRenderDebug = false;

		//0�L�[���������ꍇ�A�e�X�g������@�̐�����\��
		if (g_pInput->IsKeyPush(MOFKEY_0)) {

			g_KeyRenderDebug = !g_KeyRenderDebug;
		}

		KeyOperation();
	}

}

void CPlayer::TestPadOperation() {

	//�_���[�W�̃e�X�g����
	if (g_pGamePad->IsKeyPush(GAMEKEY_X)) {

		m_Hp -= 5;

	}//�p���[�A�b�v�̃e�X�g����
	else if (g_pGamePad->IsKeyPush(GAMEKEY_Y)) {

		m_bPowerUp = !m_bPowerUp;

	}//�G�t�F�N�g�̃e�X�g����
	else if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {

		g_pEffectManager->Start(m_PosX + PLAYER_WIDTH * 0.5f, m_PosY + PLAYER_HEIGHT * 0.5f, EFC_TEST);

	}//�T�E���h�̍Đ��e�X�g
	else if (g_pGamePad->IsKeyPush(GAMEKEY_LB)) {

		g_pSoundManager->Start(SUD_SOUNDBGM, SOUND_BGM);

	}//�T�E���h�̃X�g�b�v�e�X�g1
	else if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM, STOP_SUDDEN);

	}//�T�E���h�̃X�g�b�v�e�X�g2
	else if (g_pGamePad->IsKeyPush(GAMEKEY_BACK)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM,STOP_GRADUALLY);

	}

}

void CPlayer::TestKeyOperation() {

	//�_���[�W�̃e�X�g����
	if (g_pInput->IsKeyPush(MOFKEY_1)) {

		m_Hp -= 5;

	}//�p���[�A�b�v�̃e�X�g����
	else if (g_pInput->IsKeyPush(MOFKEY_2)) {

		m_bPowerUp = !m_bPowerUp;

	}//�G�t�F�N�g�̃e�X�g����
	else if (g_pInput->IsKeyPush(MOFKEY_3)) {

		g_pEffectManager->Start(m_PosX + PLAYER_WIDTH * 0.5f, m_PosY + PLAYER_HEIGHT * 0.5f, EFC_TEST);

	}//�T�E���h�̍Đ��e�X�g
	else if (g_pInput->IsKeyPush(MOFKEY_4)) {

		g_pSoundManager->Start(SUD_SOUNDBGM, SOUND_BGM);

	}//�T�E���h�̃X�g�b�v�e�X�g1
	else if (g_pInput->IsKeyPush(MOFKEY_5)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM, STOP_SUDDEN);

	}//�T�E���h�̃X�g�b�v�e�X�g2
	else if (g_pInput->IsKeyPush(MOFKEY_6)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM, STOP_GRADUALLY);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_7)) {

		g_pSoundManager->SetVolume(SUD_SOUNDEFFECT,0.5f);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_8)) {

		g_pSoundManager->SetVolume(SUD_SOUNDBGM,0.5f);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_9)) {

		g_pSoundManager->AllSetVolume(1.0f);

	}

}

void CPlayer::PadOperation() {

	//�X�L���̍X�V
	Skill();
	//�e�X�g����p
	TestPadOperation();

	//�X�e�B�b�N���E�����ɓ|�����ꍇ�A�|���������Ɉړ�
	if (g_pGamePad->GetStickHorizontal() > 0.8f) {

		m_MoveX += 0.3f;
		m_MoveX2 += 2.5f;
		if (m_MoveX > PLAYER_MAXSPEED) {

			m_MoveX = PLAYER_MAXSPEED;

		}
		if (m_MoveX2 > PLAYER_MAXSPEED * 2) {

			m_MoveX2 = PLAYER_MAXSPEED * 2;

		}
	}
	else if (g_pGamePad->GetStickHorizontal() < -0.8f) {

		m_MoveX -= 0.3f;
		m_MoveX2 -= 2.5f;
		if (m_MoveX < -PLAYER_MAXSPEED) {

			m_MoveX = -PLAYER_MAXSPEED;

		}
		if (m_MoveX2 < -PLAYER_MAXSPEED * 2) {

			m_MoveX2 = -PLAYER_MAXSPEED * 2;

		}
	}//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else {

		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_MoveX > 0) {

			m_MoveX -= 0.2f;

			if (m_MoveX < 0) {

				m_MoveX = 0;
			}

		}
		else if(m_MoveX<0){

			m_MoveX += 0.2f;

			if (m_MoveX > 0) {

				m_MoveX = 0;
			}

		}
		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_MoveX2 > 0) {

			m_MoveX2 -= 2.5f;

			if (m_MoveX2 < 0) {

				m_MoveX2 = 0;
			}

		}
		else if (m_MoveX2 < 0) {

			m_MoveX2 += 2.5f;

			if (m_MoveX2 > 0) {

				m_MoveX2 = 0;
			}

		}
	}

	//�ړ��ʂ����W�ɉ��Z
	m_PosX += m_MoveX;

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pGamePad->IsKeyPush(GAMEKEY_A)&&!m_bJump) {

		//�W�����v���ʉ��̃e�X�g����
		g_pSoundManager->Start(SUD_SOUNDEFFECT, SOUND_EFFECT);

		m_bJump = true;

		//�p���[�A�b�v�t���O�������Ă���ꍇ�A�W�����v�͏㏸
		if (m_bPowerUp) {

			m_MoveY = PLAYER_HIGHJUMP;

		}
		else {

			m_MoveY = PLAYER_JUMP;

		}
		
	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

	

}

void CPlayer::KeyOperation() {

	//�e�X�g����p
	TestKeyOperation();

	//�X�e�B�b�N���E�����ɓ|�����ꍇ�A�|���������Ɉړ�
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {

		m_MoveX += 0.2f;
		m_MoveX2 += 2.5f;
		if (m_MoveX > PLAYER_MAXSPEED) {

			m_MoveX = PLAYER_MAXSPEED;

		}
		if (m_MoveX2 > PLAYER_MAXSPEED * 2) {

			m_MoveX2 = PLAYER_MAXSPEED * 2;

		}

	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {

		m_MoveX -= 0.2f;
		m_MoveX2 -= 2.5f;

		if (m_MoveX < -PLAYER_MAXSPEED) {

			m_MoveX = -PLAYER_MAXSPEED;

		}
		if (m_MoveX2 < -PLAYER_MAXSPEED * 2) {

			m_MoveX2 = -PLAYER_MAXSPEED * 2;

		}

	}//�X�e�B�b�N�𗣂����ꍇ�i�ړ��̑�������Ă��Ȃ��ꍇ�j
	else {

		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_MoveX > 0) {

			m_MoveX -= 0.3f;

			if (m_MoveX < 0) {

				m_MoveX = 0;
			}

		}
		else if (m_MoveX < 0) {

			m_MoveX += 0.3f;

			if (m_MoveX > 0) {

				m_MoveX = 0;
			}

		}

		//�ړ��ʂ�0�Ȃ珈���ɓ���Ȃ�
		//�ړ��ʂ����݂���ꍇ�A���X�Ɉړ��ʂ�0�ɂ���
		if (m_MoveX2 > 0) {

			m_MoveX2 -= 2.5f;

			if (m_MoveX2 < 0) {

				m_MoveX2 = 0;
			}

		}
		else if (m_MoveX2 < 0) {

			m_MoveX2 += 2.5f;

			if (m_MoveX2 > 0) {

				m_MoveX2 = 0;
			}

		}
	}

	//�ړ��ʂ����W�ɉ��Z
	m_PosX += m_MoveX;

	//A�{�^�����������W�����v�t���O�������Ă��Ȃ��ꍇ�W�����v����
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump) {

		//�W�����v���ʉ��̃e�X�g����
		g_pSoundManager->Start(SUD_SOUNDEFFECT, SOUND_EFFECT);

		m_bJump = true;

		//�p���[�A�b�v�t���O�������Ă���ꍇ�A�W�����v�͏㏸
		if (m_bPowerUp) {

			m_MoveY = PLAYER_HIGHJUMP;

		}
		else {

			m_MoveY = PLAYER_JUMP;

		}

	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

}

void CPlayer::Skill() {

	//�X�L���̉~�ɍ��W�┼�a����
	m_SkillCircle.x = m_PosX + PLAYER_WIDTH / 2;
	m_SkillCircle.y = m_PosY + PLAYER_HEIGHT / 2;
	m_SkillCircle.r = m_Skillrang;

	//LT�{�^�����������ꍇ�A�X�L��������
	if (g_pGamePad->GetPadState()->lZ > 500&&m_CoolTime>0.0f) {

		m_bTrigger = true;

	}
	else if (g_pGamePad->GetPadState()->lZ < 1) {

		m_bTrigger = false;

	}

	//�X�L�����������Ă���ꍇ�^�[�Q�b�g�͈̔͂��L����
	if (m_bTrigger) {

		m_Skillrang += 10;

		m_CoolTime -= 0.1f;

		if (m_Skillrang >= PLAYER_MAXSKILLRANGE) {

			m_Skillrang = PLAYER_MAXSKILLRANGE;

		}
	}
	else {

	
		if (m_Skillrang > 0.0f) {

			m_Skillrang = 0.0f;
			m_Target = 0;

			if (!m_SkillTarget.empty()) {

				for (int i = 0; i < m_SkillTarget.size(); i++) {

					m_SkillTarget[i]->SetTarget(false);

				}

				m_SkillTarget.clear();

			}

		}

	}

}


void CPlayer::SkillColision(CEnemy* pene, int eneCount, CObject* pobj, int objCount) {
	//���[�J���Ȃ�s���邪�����o���Ƃ���
	//�\������Ă���v�f����T���A���̐��𐔂���
		//�v�f�̐������p�������ɁA�i�[�����v�f���������Ă���

		//�\������Ă���G�̗v�f�������Ɋi�[
	list<CSubstance*> element;

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
	float stx = m_PosX + PLAYER_WIDTH * 0.5f;
	float sty = m_PosY + PLAYER_HEIGHT;
	/*float stx = m_PosX + m_Motion.GetStrRect().GetWidth()*0.5f;
		float sty = m_m_PosX + m_Motion.GetStrRect().GetHeight();*/

	

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

	
	if (g_pGamePad->IsKeyPush(GAMEKEY_LB)) {

		m_Target--;

		if (m_Target < 0) {

			m_Target = m_SkillTarget.size();

		}

	}else if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {

		m_Target++;

		if (m_Target >= m_SkillTarget.size()) {

			m_Target = 0;

		}

	}

	for (int i = 0; i < m_SkillTarget.size(); i++) {

		if (i == m_Target) {

			m_SkillTarget[i]->SetTarget(true);

		}
		else {

			m_SkillTarget[i]->SetTarget(false);

		}
	}


	if (g_pGamePad->GetPadState()->lZ < -500) {
		//�t�@���X�Ȃ��ĉ~�͕\������Ȃ�������I�ɂ��̊֐��ɂ͓���
		m_bTrigger = false;

		for (int i = 0; i < m_SkillTarget.size(); i++) {

			m_SkillTarget[i]->SetTarget(false);

		}

	}

	for (int i = 0; i < m_SkillTarget.size(); i++) {

		MOF_PRINTLOG("%d[%f]\n", i, m_SkillTarget[i]->IsTarget());

	}
	
}

void CPlayer::LifeDecrease() {
	//HP��0�ȉ��ɂȂ����ꍇ�c�@�����炵HP�������l�ɖ߂�
	if (m_Hp <= 0) {

		m_Life--;

		m_Hp = PLAYER_MAXHP;
	}
}

void CPlayer::Render(Vector2 scroll) {

	//�v���C���[(��)�̕`��
	CGraphicsUtilities::RenderRect(scroll.x, scroll.y, scroll.x + PLAYER_WIDTH, scroll.y + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	//�v���C���[��HP�̕`��
	RenderState();
	//�f�o�b�N�̕`��
	RenderDebug();

	CGraphicsUtilities::RenderCircle(scroll.x+PLAYER_WIDTH / 2, scroll.y + PLAYER_WIDTH / 2,m_Skillrang, MOF_COLOR_RED);

}

void CPlayer::RenderState() {
	//HP�̒l�ɂ���ăP�[�W�̒�����ω�
	CRectangle rec(0, 0, 532 * (m_Hp*0.01f), 64);

	m_HpTexture.Render(248, 150, rec);


	
}

void CPlayer::RenderDebug() {

	/*CGraphicsUtilities::RenderString(0, 30, MOF_XRGB(0, 255, 0), "�e�X�g������@�����̕\��:�L�[�{�[�h�̏ꍇ0�L�[ : �Q�[���p�b�h�̏ꍇSTRAT�{�^��");*/
	CGraphicsUtilities::RenderString(0, 60, MOF_XRGB(0, 255, 0), "�Q�[���p�b�h�ɐڑ�����Ă����Ԃł��G���^�[�L�[�ő�����L�[�{�[�h�Ɛ؂�ւ��\");
	CGraphicsUtilities::RenderString(0, 90, MOF_XRGB(0, 255, 0), "m_MoveX %.f m_MoveY %.f m_bPowerUp %d m_bJump %d m_Hp %d m_Life %d m_PosX %.f", m_MoveX, m_MoveY, m_bPowerUp, m_bJump, m_Hp, m_Life,m_PosX);
	
	/*CGraphicsUtilities::RenderString(0, 30, "Effect�{�����[��%f BGM�{�����[��%f", g_pSoundManager->RenderDebug(SUD_SOUNDBGM), g_pSoundManager->RenderDebug(SUD_SOUNDEFFECT));*/

	if (g_KeyRenderDebug) {

		CGraphicsUtilities::RenderString(0, 120, MOF_XRGB(255, 0, 0), "1�L�[�ŋ^���_���[�W: 2�L�[�ŋ���: 3�L�[�ŃG�t�F�N�g: 4�L�[��BGM�Đ�: 5�L�[��BGM�}��~: ");
		CGraphicsUtilities::RenderString(0, 150, MOF_XRGB(255, 0, 0), "6�L�[��BGM���X�ɒ�~");
	}
	
	if (g_PadRenderDebug) {

		CGraphicsUtilities::RenderString(0, 120, MOF_XRGB(255, 0, 0), "�X�e�B�b�N�ňړ�: A�{�^���ŃW�����v: X�{�^���ŋ^���_���[�W Y�{�^���ŋ���: RB�{�^���ŃG�t�F�N�g:");
		CGraphicsUtilities::RenderString(0, 150, MOF_XRGB(255, 0, 0), " LB�{�^����BGM�Đ�: START�{�^����BGM�}��~: BACK�{�^����BGM���X�ɒ�~");

	}
	
	
}

void CPlayer::Release() {
	//HP�e�N�X�`���[(��)�̉��
	m_HpTexture.Release();
}

void CPlayer::CollisionStage(Vector2 o) {
	m_PosX += o.x;
	m_PosY += o.y;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ���������
	if (o.y < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
		}
	}
	else if (o.y > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if ((o.x < 0 && m_MoveX>0) || (o.x > 0 && m_MoveX < 0))
	{
		m_MoveX = 0;
	}
}