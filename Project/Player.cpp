#include		"Player.h"
#include		"GameDefine.h"

//�Q�[���p�b�h����L�[�{�[�h�ւ̐؂�ւ��t���O
bool	g_OperationDebug = true;
//�L�[�{�[�h�A�Q�[���p�b�h�̃e�X�g������@�̐����̕\���t���O
bool	g_PadRenderDebug = false;
bool	g_KeyRenderDebug = false;

CPlayer::CPlayer() {
	//�I�u�W�F�N�g�������̏�����
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

}

void CPlayer::PadOperation() {

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

	CGraphicsUtilities::RenderCircle(scroll.x + PLAYER_WIDTH / 2, scroll.y + PLAYER_HEIGHT / 2, 512, MOF_COLOR_RED);

}

void CPlayer::RenderState() {
	//HP�̒l�ɂ���ăP�[�W�̒�����ω�
	CRectangle rec(0, 0, 532 * (m_Hp*0.01f), 64);

	m_HpTexture.Render(248, 150, rec);


	
}

void CPlayer::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 30, MOF_XRGB(0, 255, 0), "�e�X�g������@�����̕\��:�L�[�{�[�h�̏ꍇ0�L�[ : �Q�[���p�b�h�̏ꍇSTRAT�{�^��");
	CGraphicsUtilities::RenderString(0, 60, MOF_XRGB(0, 255, 0), "�Q�[���p�b�h�ɐڑ�����Ă����Ԃł��G���^�[�L�[�ő�����L�[�{�[�h�Ɛ؂�ւ��\");
	CGraphicsUtilities::RenderString(0, 90, MOF_XRGB(0, 255, 0), "m_MoveX %.f m_MoveY %.f m_bPowerUp %d m_bJump %d m_Hp %d m_Life %d", m_MoveX, m_MoveY, m_bPowerUp, m_bJump, m_Hp, m_Life);

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