#pragma once
#include	"Mof.h"
#include	"TextureManager.h"

//�A�j���[�V�����f�[�^�N���X
class CAnimationData
{
private:
	std::string				m_TextureName;		//! �A�j���[�V�����f�[�^�̉摜��
	SpriteAnimationCreate*	m_pAnim;			//! �A�j���[�V�����f�[�^
	int						m_AnimCount;		//! �A�j���[�V������
public:
	CAnimationData(void);						//! �R���X�g���N�^
	~CAnimationData(void);						//! �f�X�g���N�^
	bool Load(const std::string& str);			//! �Ǎ�
	SpriteAnimationCreate* GetAnim(void);		//! �A�j���[�V�����f�[�^�擾
	int GetAnimCount(void) const;				//! �A�j���[�V�������擾
	std::string GetTextureName(void) const;		//! �摜���擾
	void Release(void);							//! ���
};

