#pragma once
#include	"Mof.h"
#include	"AnimationData.h"
#include	<unordered_map>

//�A�j���[�V�����Ǘ��N���X
class CAnimationManager
{
private:
	std::unordered_map<std::string, CAnimationData*> m_Resource;	//! �f�[�^
	CAnimationManager(void);
	~CAnimationManager(void);
public:
	static CAnimationManager* GetAnimation(void);					//! �}�l�[�W���[�Ăяo��
	static CAnimationData* GetAnimation(const std::string& str);	//! �A�j���[�V�����f�[�^�擾
	static bool Load(const std::string& str);						//! �t�@�C��������f�[�^�ǂݍ���
	static void Release(void);										//! ���
};

