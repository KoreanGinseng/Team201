#pragma once
#include	"Mof.h"
#include	"AnimationManager.h"

class CEffect
{
private:
	//CTexture* m_pTexture;					//! �G�t�F�N�g�摜
	std::shared_ptr<CTexture> m_pTexture;	//! �G�t�F�N�g�摜
	CSpriteMotionController m_Motion;		//! �G�t�F�N�g���[�V����
	bool m_bShow;							//! �\���t���O
	Vector2 m_Pos;							//! �\�����W
public:
	CEffect(void);							//! �R���X�g���N�^
	~CEffect(void);							//! �f�X�g���N�^
	bool IsShow(void) const;				//! �\���t���O�擾
	void Start(const Vector2& pos);			//! �G�t�F�N�g�̔���
	bool Load(const std::string& str);		//! �t�@�C������f�[�^�ǂݍ���
	void Update(void);						//! �G�t�F�N�g����
	void Render(void);						//! �G�t�F�N�g�\��
	void Release(void);						//! ���
};

