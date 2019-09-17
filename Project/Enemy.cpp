#include	"Enemy.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemy::CEnemy() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_bReverse(false) ,
m_SrcRect() ,
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
void CEnemy::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = -3.0f;
	m_MoveY = 0.0f;
	m_bReverse = true;
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		//�ړ�
		{
			"�ړ�",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}} 
		},
		//�_���[�W
		{
			"�_���[�W",
			0,210,
			60,64,
			FALSE,{{20,0,0}} 
		},
	};
	m_Motion.Create(anim,MOTION_COUNT);
}

/**
 * �X�V
 *
 */
void CEnemy::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�_���[�W���̓���
	if(m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if(m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if(m_HP <= 0)
			{
				m_bShow = false;
			}
			if(m_bReverse)
			{
				m_MoveX = -3.0f;
			}
			else
			{
				m_MoveX = 3.0f;
			}
		}
		else
		{
			if(m_MoveX > 0)
			{
				m_MoveX -= 0.2f;
				if(m_MoveX <= 0)
				{
					m_MoveX = 0;
				}
			}
			else if(m_MoveX < 0)
			{
				m_MoveX += 0.2f;
				if(m_MoveX >= 0)
				{
					m_MoveX = 0;
				}
			}
		}
	}
	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if(m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if(m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}


/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy::Render(Vector2 sp){
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
	if(m_bReverse)
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
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy::RenderDebug(Vector2 sp){
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
void CEnemy::Release(void){
	m_Motion.Release();
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
	m_HP -= dmg;
	m_DamageWait = 60;
	if(bRev)
	{
		m_MoveX = -5.0f;
		m_bReverse = false;
	}
	else
	{
		m_MoveX = 5.0f;
		m_bReverse = true;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CEnemy::CollisionStage(Vector2 o){
	m_PosX += o.x;
	m_PosY += o.y;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if(o.y < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if(o.y > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if(o.x < 0 && m_MoveX > 0)
	{
		if(m_Motion.GetMotionNo() == MOTION_DAMAGE)
		{
			m_MoveX = 0;
		}
		else
		{
			m_MoveX *= -1;
			m_bReverse = true;
		}
	}
	else if(o.x > 0 && m_MoveX < 0)
	{
		if(m_Motion.GetMotionNo() == MOTION_DAMAGE)
		{
			m_MoveX = 0;
		}
		else
		{
			m_MoveX *= -1;
			m_bReverse = false;
		}
	}
}
