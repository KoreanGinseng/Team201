/*****************************************************************
 *	@file			Player.h
 *	@brief			�v���C���[�N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"
#include	"Camera2D.h"
#include	"GameDefine.h"
#include	"Character.h"
#include	"Enemy.h"
#include	"TargetObj.h"
#include	"Item.h"
#include	"Score.h"

//DEFINE
#define		PLAYER_RECTDIS		90		//�v���C���[�̓����蔻���`���E�̏k�߂�l

class CPlayer : public CCharacter
{
private:
	//�v���C���[�̃A�j���[�V����
	enum tag_Animation {
		ANIM_WAIT,
		ANIM_MOVE,
		ANIM_JUMPUP,
		ANIM_JUMPDOWN,
		ANIM_SKILLSTANCE,
		ANIM_SKILLPLAY,

		ANIM_COUNT,
	};
	struct KeyConfig {
		bool	moveLeft;
		bool	moveRight;
		bool	jump;
		bool	clime;
		bool	fall;
		bool	selectNext;
		bool	selectBack;
		bool	skillStance;
		bool	skillStancePull;
		bool	skillBack;
		bool	skillStop;
		bool	skillSkip;
		bool	attack;
	};

	KeyConfig					m_KeyConfig;		//�L�[�R���t�B�O
	bool						m_bKey;				//�L�[�{�[�h���p�b�h���̃t���O
	bool						m_bJump;			//�W�����v�t���O
	std::vector<CSubstance*>	m_SkillTarget;		//�X�L���őI���ł��郊�X�g
	bool						m_bTrigger;			//�X�L�����g�����t���O
	bool						m_bClime;			//���o��悤�̃t���O
	int							m_Target;			//�^�[�Q�b�g���Ă���ԍ�
	float						m_Skillrang;		//�X�L���͈̔�
	CCircle						m_SkillCircle;		//�X�L���̉~
	bool						m_bCntrl;			//����\�t���O

	bool						m_bSkillObjNomal;
	bool						m_bSkillObjBack;
	bool						m_bSkillObjTrip;
	bool						m_bSkillEne;

	CSpriteMotionController		m_SordMotion;

	bool						m_bAttack;

public:
	CPlayer(void);			//�R���X�g���N�^
	~CPlayer(void);			//�f�X�g���N�^
	void Initialize(void) override;					//������
	void Update(void) override;						//�X�V
	void Render(const Vector2& screenPos) override;	//�`��
	void RenderCircle(const Vector2& screenPos) override;	//Circle�`��
	void Release(void) override;					//���

	void Move(void);								//����,�ړ��ʌv�Z
	void Animation(void);							//�A�j���[�V��������
	void Skill(void);								//�X�L������
	//�^�[�Q�b�g�I��
	void TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray);

	void CollisionStage(const Vector2& over) override; //���܂�l�̏���

	//Get
	bool	IsTrigger(void) { return m_bTrigger; }	//�X�L�����g�������̃t���O�擾
	bool	IsClime(void) { return m_bClime; }		//�o���Ԃ��̃t���O
	CRectangle GetRect(void) override;				//�����蔻��p��`�̎擾
	//Set
	void   SetClime(const bool& b)					//�t���O�̃Z�b�g
	{ m_bClime = b; }
	bool   Dmg(CEnemy& ene);						//�_���[�W�̏���
	bool   Dmg(const int& dmg);						//�_���[�W�̏���
	void SetCntrl(const bool& b) { m_bCntrl = b; }	//����t���O�̃Z�b�g
	void Heal(const int& h) { m_HP += h; }

	bool IsJump(void) const { return m_bJump; }
	bool IsObjNomal(void) const { return m_bSkillObjNomal; }
	bool IsObjBack(void) const { return m_bSkillObjBack; }
	bool IsObjTrip(void) const { return m_bSkillObjTrip; }
	bool IsEne(void) const { return m_bSkillEne; }
};

