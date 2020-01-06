#pragma once
#include	"Mof.h"

//�T�E���h�G�t�F�N�g�p�N���X
class CSound
{
private:
	CSoundBuffer*	m_pSound;						//! �T�E���h
	bool			m_bPlay;						//! �Đ��t���O
public:
	CSound(void);									//! �R���X�g���N�^
	~CSound(void);									//! �f�X�g���N�^
	CSoundBuffer*	GetSoundBuffer(void);			//! �T�E���h�擾
	bool			IsPlay(void) const;				//! �Đ��t���O�擾
	void			Play(void);						//! �Đ�
	bool			Load(const std::string& str);	//! �Ǎ�
	void			Update(void);					//! �X�V
	void			Release(void);					//! ���
};

