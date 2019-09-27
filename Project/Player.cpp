#include		"Player.h"
#include		"GameDefine.h"


bool	bDebug = true;

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


}

CPlayer::~CPlayer() {


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
	//m_PosX = 0;
	m_PosX = 256.0f;
	//m_PosY = 0;
	m_PosY = 1344.0f;
	//�ړ��ʂ̏�����
	m_MoveX = 0;
	m_MoveY = 0;
	//HP�̏�����
	m_Hp = PLAYER_MAXHP;
	//�c�@�̏�����
	m_Life = PLAYER_MAXLIFE;
	//�W�����v�t���O�̏�����
	m_bJump = false;

}

void CPlayer::Update() {

	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		bDebug = !bDebug;
	}

	if (bDebug)
	{
		Debug();
	}

	//�R���g���[���[��PC�ɐڑ�����Ă���ꍇ����ł���
	else if (g_pInput->GetGamePadCount()) {

		PadOperation();
		//�_���[�W�̃e�X�g����
		if (g_pGamePad->IsKeyPush(GAMEKEY_X)) {

			m_Hp -= 5;

		}

	}
	//�L�[�{�[�h����
	else {
		KeyOperation();
	}
	//�c�@�����̍X�V
	LifeDecrease();

	
}

void CPlayer::PadOperation() {

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

		m_bJump = true;

		m_MoveY = -10.0f;
	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

	////�Ƃ肠�����c���W��300�̈ʒu���X�e�[�W��
	//if (m_PosY > 300) {
	//	m_PosY = 300;
	//	m_MoveY = 0;
	//	if (m_bJump) {
	//		m_bJump = false;
	//	}
	//}

}

void CPlayer::KeyOperation() {

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

		m_bJump = true;

		m_MoveY = -10.0f;
	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

	////�Ƃ肠�����c���W��300�̈ʒu���X�e�[�W��
	//if (m_PosY > 100) {
	//	m_PosY = 100;
	//	m_MoveY = 0;
	//	if (m_bJump) {
	//		m_bJump = false;
	//	}
	//}
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
	//CGraphicsUtilities::RenderRect(m_PosX, m_PosY, m_PosX + PLAYER_WIDTH, m_PosY + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderRect(scroll.x, scroll.y, scroll.x + PLAYER_WIDTH, scroll.y + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	//�v���C���[��HP�̕`��
	RenderState();

	RenderDebug();

	CGraphicsUtilities::RenderCircle(scroll.x + PLAYER_WIDTH / 2, scroll.y + PLAYER_HEIGHT / 2, 512, MOF_COLOR_RED);

}

void CPlayer::RenderState() {
	//HP�̒l�ɂ���ăP�[�W�̒�����ω�
	CRectangle rec(0, 0, 532 * (m_Hp*0.01f), 64);

	m_HpTexture.Render(248, 150, rec);


	
}

void CPlayer::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 50, MOF_XRGB(255, 0, 0), "m_MoveX %.f m_MoveY %.f m_bJump %d m_Hp %d m_Life %d", m_MoveX,m_MoveY,m_bJump,m_Hp,m_Life);
	CGraphicsUtilities::RenderString(0, 100, MOF_XRGB(255, 0, 0), "�X�e�B�b�N�ňړ�: A�{�^���ŃW�����v: X�{�^���ŋ^���_���[�W");
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

#ifdef _DEBUG
void CPlayer::Debug()
{
	int s = 5;
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_PosX -= s;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_PosX += s;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_PosY -= s;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_PosY += s;
	}
}
#endif	//_DEBUG