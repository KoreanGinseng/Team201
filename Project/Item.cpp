#include	"Item.h"

/**
 * �R���X�g���N�^
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_pMotion() ,
m_Pos(Vector2(0,0)) ,
m_Move(Vector2(0,0)) ,
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
	m_Pos.x = px;
	m_Pos.y = py;
	m_Move.x = 0.0f;
	m_Move.y = 0.0f;
	m_bShow = true;
	//�A�j���[�V�������쐬
	m_pMotion = g_pAnimManager->GetResource(FileName[ANIMATION_ITEM_1])->GetMotion();
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
	m_Move.y += GRAVITY;
	if(m_Move.y >= 20.0f)
	{
		m_Move.y = 20.0f;
	}
	//���ۂɍ��W���ړ�������
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	//�A�j���[�V�����̍X�V
	m_pMotion->AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_pMotion->GetSrcRect();
}


/**
 * �`��
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
	m_pMotion->Release();
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CItem::CollisionStage(Vector2 o){
	m_Pos.x += o.x;
	m_Pos.y += o.y;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if(o.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if(o.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if(o.x < 0 && m_Move.x > 0)
	{
		m_Move.x = 0;
	}
	else if(o.x > 0 && m_Move.x < 0)
	{
		m_Move.x = 0;
	}
}
