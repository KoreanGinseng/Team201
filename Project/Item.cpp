#include	"Item.h"

/**
 * �R���X�g���N�^
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CItem::~CItem(){
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
void CItem::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim = {
		"�A�C�e��",
		0,0,
		32,32,
		TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}} 
	};
	m_Motion.Create(anim);
}

/**
 * �X�V
 *
 */
void CItem::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
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
}


/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::Render(Vector2 sp){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(sp.x, sp.y, m_SrcRect);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::RenderDebug(Vector2 sp){
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
void CItem::Release(void){
	m_Motion.Release();
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CItem::CollisionStage(Vector2 o){
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
		m_MoveX = 0;
	}
	else if(o.x > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

void CItem::Tracking()
{
	
}
