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

CSound * CSoundManager::GetSoundSE(const std::string & str)
{
	if (CSoundManager::GetSound()->m_ResourceSE[str].GetArrayCount() <= 0)
	{
		CSoundManager::LoadSE(str);
	}
	CSound* re;
	int c = CSoundManager::GetSound()->m_ResourceSE[str].GetArrayCount();
	bool bFind = false;
	//再生可能のサウンドを探す
	for (int i = 0; i < c; i++)
	{
		re = CSoundManager::GetSound()->m_ResourceSE[str].GetData(i);
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
		float vol = CSoundManager::GetSound()->m_ResourceSE[str].GetData(0)->GetSoundBuffer()->GetVolume();
		//追加
		CSoundManager::GetSound()->m_ResourceSE[str].Add(NEW CSound());
		CSoundManager::GetSound()->m_ResourceSE[str].GetData(c)->Load(str.c_str());
		//サウンドの大きさを合わせる
		CSoundManager::GetSound()->m_ResourceSE[str].GetData(c)->GetSoundBuffer()->SetVolume(vol);
		re = CSoundManager::GetSound()->m_ResourceSE[str].GetData(c);
	}
	return re;
}

CSoundBuffer * CSoundManager::GetSoundBGM(const std::string & str)
{
	if (CSoundManager::GetSound()->m_ResourceBGM[str] == nullptr)
	{
		CSoundManager::LoadBGM(str);
	}
	return CSoundManager::GetSound()->m_ResourceBGM[str];
}

CSoundBuffer * CSoundManager::GetSoundBuffer(const std::string & str)
{
	CSoundBuffer* re = CSoundManager::GetSoundSE(str)->GetSoundBuffer();
	if (re == nullptr)
	{
		re = CSoundManager::GetSoundBGM(str);
	}
	return re;
}

void CSoundManager::PlaySE(const std::string & str)
{
	CSoundManager::GetSoundSE(str)->Play();
}

void CSoundManager::PlayBGM(const std::string & str)
{
	CSoundManager::GetSoundBGM(str)->Play();
}

void CSoundManager::SetVolumeSE(const std::string & str, const float & vol)
{
	int c = CSoundManager::GetSound()->m_ResourceSE[str].GetArrayCount();
	for (int i = 0; i < c; i++)
	{
		CSoundManager::GetSound()->m_ResourceSE[str].GetData(i)->GetSoundBuffer()->SetVolume(vol);
	}
}

void CSoundManager::SetVolumeBGM(const std::string & str, const float & vol)
{
	CSoundManager::GetSoundBGM(str)->SetVolume(vol);
}

bool CSoundManager::LoadSE(const std::string& str)
{
	for (int i = 0; i < DefSoundPool; i++)
	{
		CSoundManager::GetSound()->m_ResourceSE[str].Add(NEW CSound());
		if (!CSoundManager::GetSound()->m_ResourceSE[str].GetData(i)->Load(str))
		{
			return false;
		}
	}
	return true;
}

bool CSoundManager::LoadBGM(const std::string & str)
{
	if (CSoundManager::GetSound()->m_ResourceBGM[str] != nullptr)
	{
		return true;
	}
	CSoundManager::GetSound()->m_ResourceBGM[str] = new CSoundBuffer();
	if (!CSoundManager::GetSound()->m_ResourceBGM[str]->Load(str.c_str()))
	{
		return false;
	}
	CSoundManager::GetSound()->m_ResourceBGM[str]->SetLoop(TRUE);
	return true;
}

void CSoundManager::Update(void)
{
	for (auto& itr : CSoundManager::GetSound()->m_ResourceSE)
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
	for (auto& itr : CSoundManager::GetSound()->m_ResourceSE)
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
	for (auto& itr : CSoundManager::GetSound()->m_ResourceBGM)
	{
			itr.second->Release();
			delete itr.second;
			itr.second = nullptr;
	}
	CSoundManager::GetSound()->m_ResourceBGM.clear();
}
