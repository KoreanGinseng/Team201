#pragma once
#include	"Mof.h"

template<typename T>
class CResourceManager
{
private:
	std::map<std::string, std::shared_ptr<T>> m_Resource;	//�f�[�^�ۗL�����o
	CResourceManager(void) = default;
	~CResourceManager(void) = default;

public:

	//Get

	//�t�@�C���l�[������f�[�^���擾
	std::shared_ptr<T> GetResource(const char* pName) { 
		if (m_Resource.find(pName) == m_Resource.end())
		{
			m_Resource[pName] = std::make_shared<T>();
			if (!m_Resource[pName]->Load(pName))
			{
				return nullptr;
			}
		}
		return m_Resource[pName];
	}

	//�C���X�^���X�擾�p
	static CResourceManager<T>* GetInstance(void) {
		static CResourceManager<T> *obj = nullptr;
		if (obj == nullptr)	obj = new CResourceManager<T>();
		return obj;
	}

	//�f�[�^�ۗL���Ă�����̂��ׂĂ����
	void Release(void) {
		for (auto itr = m_Resource.begin(); itr != m_Resource.end(); ++itr)
		{
			itr->second->Release();
		}
	}
};