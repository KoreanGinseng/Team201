#pragma once
#include	"GameDefine.h"

class CObject
{
protected:
	Vector2			m_Pos;			//���W
	CTexturePtr		m_pTexture;		//�摜�|�C���^
	bool			m_bShow;		//�\���t���O
public:
	CObject();																//�R���X�g���N�^
	virtual ~CObject();														//�f�X�g���N�^
	virtual void Initialize(void) = 0;										//������
	virtual void Update(void) = 0;											//�X�V
	virtual void Render(const Vector2& screenPos) = 0;						//�`��
	virtual void Release(void) = 0;											//���
	void SetPos(const float& x, const float& y) { SetPos(Vector2(x,y)); }	//���W�ݒ�
	void SetPos(const Vector2& pos) { m_Pos = pos; }						//���W�ݒ�
	virtual void SetTexture(const CTexturePtr& pt) { m_pTexture = pt; }		//�摜�ݒ�
	void SetShow(const bool& b) { m_bShow = b; }							//�\���t���O�ύX
	bool IsShow(void) const { return m_bShow; }								//�\���t���O�擾
	Vector2 GetPos(void) const { return m_Pos; }							//���W�擾
};

