#include	"Enemy.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemy::CEnemy() :
m_pTexture(nullptr) ,
m_bShow(false) ,
m_HP(0) ,
m_DamageWait(0) {
}

/**
 * �f�X�g���N�^
 *
 */
CEnemy::~CEnemy(){
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�^�C�v
 */
void CEnemy::Initialize(float px,float py) {
	m_pMove->Initialize();
	m_pMove->SetPos(Vector2(px, py));
	m_pMove->SetReverse(true);
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;
}

/**
 * �X�V
 *
 */
void CEnemy::Update(const Vector2& playerPos) {
	//��\��
	if(!m_bShow)
	{
		return;
	}
	
	m_pMove->Update(playerPos.x, playerPos.y);

	if (m_pMove->GetAttack())
	{
		m_pAttack->KUpdate(m_pMove->GetPos().x, m_pMove->GetPos().y, m_pMove->GetReverce());
	}

	//���ۂɍ��W���ړ�������
	m_Pos = m_pMove->GetPos();
	m_Pos += m_pMove->GetSpd();
	m_pMove->SetPos(m_Pos);
	m_SrcRect = m_pMove->GetSrcRect();

	//�_���[�W�̃C���^�[�o�������炷
	if(m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}


/**
 * �`��
 */
void CEnemy::Render(const Vector2& sp){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if(m_DamageWait % 4 >= 2)
	{
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if(m_pMove->GetReverce())
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(sp.x, sp.y, dr);
}

/**
 * �f�o�b�O�`��
 */
void CEnemy::RenderDebug(const Vector2& sp){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr(sp.x, sp.y, sp.x + m_SrcRect.GetWidth(), sp.y + m_SrcRect.GetHeight());
	CGraphicsUtilities::RenderRect(hr, MOF_XRGB(255,0,0));
}

/**
 * ���
 *
 */
void CEnemy::Release(void) {
 	delete	m_pMove;
 	m_pMove = nullptr;
 	delete	m_pAttack;
 	m_pAttack = nullptr;
}

/**
 * �_���[�W����
 * �������̂g�o�����炵�g�o���O�ȉ��ɂȂ�ΓG����������
 *
 * ����
 * [in]			dmg				�_���[�W
 * [in]			bRev			���]�t���O
 */
void CEnemy::Damage(int dmg,bool bRev){

}

/**
 * �X�e�[�W�Ƃ̓�����
 */
void CEnemy::CollisionStage(Vector2 o) {
	m_Pos += o;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if(o.y < 0 && m_pMove->GetSpd().y > 0)
	{
		m_pMove->ResetSpd(WAY_Y);
	}
	else if(o.y > 0 && m_pMove->GetSpd().y < 0)
	{
		m_pMove->ResetSpd(WAY_Y);
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if(o.x < 0 && m_pMove->GetSpd().x > 0)
	{
		m_pMove->Reverse();
	}
	else if(o.x > 0 && m_pMove->GetSpd().x < 0)
	{
		m_pMove->Reverse();
	}
	m_pMove->SetPos(m_Pos);
}


void CEnemy::SetMoveAttack(const int& no)
{
	switch (no)
	{
	case ENEMY_KURIBO:
		m_pMove = new CEnemy_KURIBO();
		m_pAttack = new CEnemyAtack();
		break;
	case ENEMY_NOKONOKO:
		m_pMove = new CENEMY_NOKONOKO();
		break;
	case ENEMY_TERESA:
		m_pMove = new CENEMY_TERESA();
		break;
	case ENEMY_BAT:
		m_pMove = new CENEMY_BAT();
		break;
	case ENEMY_KOTEIHOUDAI:
		m_pMove = new CENEMY_KOTEIHOUDAI();
		break;
	default:
		break;
	}
}