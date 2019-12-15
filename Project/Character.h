#pragma once
#include "Object.h"

class CCharacter :
	public CObject
{
protected:
	Vector2						m_Move;				//�ړ���
	CSpriteMotionController*	m_pMotion;			//�A�j���[�V����
	RectArray					m_SrcRectArray;		//�����蔻��p��`
	bool						m_bDead;			//���S�t���O
	bool						m_bReverse;			//���]�t���O
	int							m_DamageWait;		//�_���[�W�҂��t���[��
	bool						m_bCollision;		//�����蔻������邩�ǂ����̃t���O
public:
	CCharacter(void);//�R���X�g���N�^
	virtual ~CCharacter(void);//�f�X�g���N�^
	void Initialize(void) override = 0;				//������
	void Update(void) override = 0;					//�X�V
	void Render(const Vector2& screenPos) override;	//�`��
	void Release(void) override;					//���
	void LoadRect(const char* pName);				//�����蔻��p��`�ǂݍ���
	bool IsDead(void) const { return m_bDead; }		//���S�t���O�擾
	CRectangle GetSrcRect(void) const;				//�A�j���[�V������`�擾
	virtual CRectangle GetRect(void) const;			//�����蔻��p��`�擾
	RectArray GetSrcRectArray(void) const			//�����蔻��p��`�̔z��擾
	{ return m_SrcRectArray; }
	RectArray* GetSrcRectArrayPointer(void)			//�����蔻��p��`�̔z����|�C���^�Ŏ擾
	{ return &m_SrcRectArray; }
	RectArray GetRectArray(void) const;				//�����蔻��p��`�̔z��擾
	CRectangle GetRectArray(const int& n) const {	//�����蔻��p��`�̔z���ԍ��w��Ŏ擾
		return CRectangle(
			m_Pos.x + m_SrcRectArray[n].Left, m_Pos.y + m_SrcRectArray[n].Top,
			m_Pos.x + m_SrcRectArray[n].Right, m_Pos.y + m_SrcRectArray[n].Bottom);
	}
	int GetDamageWait(void) const					//�_���[�W�҂��t���[���擾
	{ return m_DamageWait; }
	virtual bool OverValue(CRectangle rec, Vector2& out);	//���g�Ƃ̖��܂�l���v�Z���ĕԂ�
	virtual void CollisionStage(const Vector2& over);		//���܂������̏���
	void SetCollisionFlag(const bool& b)					//�����蔻������邩�ǂ����̃t���O�ݒ�
	{ m_bCollision = b; }
	bool IsCollisionFlag(void) const						//�����蔻������邩�ǂ����̃t���O�擾
	{ return m_bCollision; }
	bool IsStageOver(void) const {							//�X�e�[�W�͈̔͊O�ɏo�Ă��邩�ǂ����𒲂ׂ�
		return (GetRect().Right < CCordinate::GetStageRect().Left || m_Pos.x > CCordinate::GetStageRect().Right ||
			GetRect().Bottom < CCordinate::GetStageRect().Top || m_Pos.y > CCordinate::GetStageRect().Bottom);
	}
};

