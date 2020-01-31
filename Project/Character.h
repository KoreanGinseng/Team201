#pragma once
#include "Object.h"
#include "Camera2D.h"

class CCharacter :
	public CObject
{
protected:

	int							m_HP;				//�̗�
	Vector2						m_Move;				//�ړ���
	Vector2						m_Spd;				//�ړ����x
	CSpriteMotionController		m_Motion;			//�A�j���[�V����
	RectArray					m_SrcRectArray;		//�����蔻��p��`
	bool						m_bMove;			//�ړ��t���O
	bool						m_bDead;			//���S�t���O
	bool						m_bReverse;			//���]�t���O
	int							m_DamageWait;		//�_���[�W�҂��t���[��
	bool						m_bCollision;		//�����蔻������邩�ǂ����̃t���O
public:
	CCharacter(void);//�R���X�g���N�^
	virtual ~CCharacter(void);//�f�X�g���N�^
	virtual void Initialize(void) override = 0;				//������
	virtual void Update(void) override = 0;					//�X�V
	virtual void Render(const Vector2& screenPos) override;	//�`��
	virtual void RenderCircle(const Vector2& screenPos);	//Circle�`��
	virtual void Release(void) override;					//���
	virtual void CreateMotion(const char* pName);			//���[�V�����̍쐬
	void LoadRect(const char* pName);						//�����蔻��p��`�ǂݍ���
	bool IsDead(void) const { return m_bDead; }				//���S�t���O�擾
	int	 GetHp(void) { return m_HP; }						//HP�̎擾
	CRectangle GetSrcRect(void);							//�A�j���[�V������`�擾
	virtual CRectangle GetRect(void);						//�����蔻��p��`�擾
	RectArray GetSrcRectArray(void) const;					//�����蔻��p��`�̔z��擾
	RectArray* GetSrcRectArrayPointer(void);				//�����蔻��p��`�̔z����|�C���^�Ŏ擾
	RectArray GetRectArray(void);							//�����蔻��p��`�̔z��擾
	CRectangle GetRectArray(const int& n) const;			//�����蔻��p��`�̔z���ԍ��w��Ŏ擾
	int GetDamageWait(void) const;							//�_���[�W�҂��t���[���擾
	virtual bool OverValue(CRectangle rec, Vector2& out);	//���g�Ƃ̖��܂�l���v�Z���ĕԂ�
	virtual void CollisionStage(const Vector2& over);		//���܂������̏���
	void SetCollisionFlag(const bool& b);					//�����蔻������邩�ǂ����̃t���O�ݒ�
	bool IsCollisionFlag(void) const;						//�����蔻������邩�ǂ����̃t���O�擾
	bool IsStageOver(void);									//�X�e�[�W�͈̔͊O�ɏo�Ă��邩�ǂ����𒲂ׂ�
	virtual Vector2 GetMove(void) const;

	virtual void SetDead(const bool& b);
	virtual void SetReverse(const bool& b);
	virtual bool IsReverse(void) const;
	virtual void SetMove(const Vector2& move);
};

