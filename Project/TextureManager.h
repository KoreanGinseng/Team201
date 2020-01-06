#pragma once
#include	"Mof.h"
#include	<unordered_map>

class CTextureManager
{
private:
	//std::unordered_map<std::string, CTexture*> m_Resource;		//! �f�[�^
	std::unordered_map<std::string, std::shared_ptr<CTexture>> m_Resource;		//! �f�[�^
	CTextureManager(void);
	~CTextureManager(void);
public:
	static CTextureManager* GetTexture(void);					//! �}�l�[�W���[�Ăяo��
	//static CTexture* GetTexture(const std::string& str);		//! �摜�擾
	static std::shared_ptr<CTexture> GetTexture(const std::string& str);		//! �摜�擾
	static bool Load(const std::string& str);					//! �Ǎ�
	static void Release(void);									//! ���
};

