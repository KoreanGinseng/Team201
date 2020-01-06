#include "SoundManager.h"



CSoundManager::CSoundManager(void)
{
}

CSoundManager::~CSoundManager(void)
{
}

CSoundManager * CSoundManager::GetSound(void)
{
	static CSoundManager obj;
	return &obj;
}

CSound * CSoundManager::GetSound(const std::string & str)
{
	CSound* re;
	int c = CSoundManager::GetSound()->m_Resource[str].GetArrayCount();
	bool bFind = false;
	//再生可能のサウンドを探す
	for (int i = 0; i < c; i++)
	{
		re = CSoundManager::GetSound()->m_Resource[str].GetData(i);
		//再生中なら次
		if (re->IsPlay())
		{
			continue;
		}
		//見つけたらぬける
		bFind = true;
		break;
	}
	//見つからなかった場合追加する
	if (!bFind)
	{
		//サウンドの大きさを取得
		float vol = CSoundManager::GetSound()->m_Resource[str].GetData(0)->GetSoundBuffer()->GetVolume();
		//追加
		CSoundManager::GetSound()->m_Resource[str].Add(NEW CSound());
		CSoundManager::GetSound()->m_Resource[str].GetData(c)->Load(str.c_str());
		//サウンドの大きさを合わせる
		CSoundManager::GetSound()->m_Resource[str].GetData(c)->GetSoundBuffer()->SetVolume(vol);
		re = CSoundManager::GetSound()->m_Resource[str].GetData(c);
	}
	return re;
}

CSoundBuffer * CSoundManager::GetSoundBuffer(const std::string & str)
{
	return CSoundManager::GetSound(str)->GetSoundBuffer();
}

void CSoundManager::Play(const std::string & str)
{
	CSoundManager::GetSound(str)->Play();
}

void CSoundManager::SetVolume(const std::string & str, const float & vol)
{
	int c = CSoundManager::GetSound()->m_Resource[str].GetArrayCount();
	for (int i = 0; i < c; i++)
	{
		CSoundManager::GetSound()->m_Resource[str].GetData(i)->GetSoundBuffer()->SetVolume(vol);
	}
}

bool CSoundManager::Load(const std::string& str)
{
	for (int i = 0; i < DefSoundPool; i++)
	{
		CSoundManager::GetSound()->m_Resource[str].Add(NEW CSound());
		if (!CSoundManager::GetSound()->m_Resource[str].GetData(i)->Load(str))
		{
			return false;
		}
	}
	return true;
}

void CSoundManager::Update(void)
{
	for (auto& itr : CSoundManager::GetSound()->m_Resource)
	{
		int c = itr.second.GetArrayCount();
		for (int i = 0; i < c; i++)
		{
			itr.second.GetData(i)->Update();
		}
	}
}

void CSoundManager::Release(void)
{
	for (auto& itr : CSoundManager::GetSound()->m_Resource)
	{
		int c = itr.second.GetArrayCount();
		for (int i = 0; i < c; i++)
		{
			itr.second.GetData(i)->Release();
			delete itr.second.GetData(i);
			itr.second.SetData(nullptr, i);
		}
		itr.second.Release();
	}
	CSoundManager::GetSound()->m_Resource.clear();
}
