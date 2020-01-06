#pragma once
#include	"Mof.h"
#include	<unordered_map>
#include	"Effect.h"

constexpr	int		DefEffectPool = 10;		//! �G�t�F�N�g�v�[����

//�G�t�F�N�g�Ǘ��N���X
class CEffectManager
{
private:
	std::unordered_map<std::string, CDynamicArray<CEffect*>>	m_Resource;			//! �f�[�^
	CEffectManager(void);
	~CEffectManager(void);
public:
	static CEffectManager* GetEffect(void);											//! �}�l�[�W���[�Ăяo��
	static CEffect* GetEffect(const std::string& str);								//! �Đ��\�ȃG�t�F�N�g�擾
	static void Start(const std::string& str, const Vector2& pos);					//! �G�t�F�N�g�̍Đ�
	static void Start(const std::string& str, const float& x, const float& y);		//! �G�t�F�N�g�̍Đ�
	static bool Load(const std::string& str);										//! �Ǎ�
	static void Update(void);														//! �G�t�F�N�g�̐���
	static void Render(void);														//! �G�t�F�N�g�̕`��
	static void Release(void);														//! ���
};

