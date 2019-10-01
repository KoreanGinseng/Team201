#include		"SoundManager.h"

//CSoundManager::CSoundManager() {
//
//
//}
//
//CSoundManager::~CSoundManager() {
//
//
//}

CSoundManager* CSoundManager::m_pInstance = NULL;

bool CSoundManager::Load() {

	//サウンドの読み込み
	char* name[] = {

		"TestJump.mp3",
		"TestStageBGM.mp3",
	};

	for (int i = 0; i < SUD_TYPECOUNT; i++) {

		if (!m_Sound[i].Load(name[i])) {

			return false;

		}
	}

	return true;
}

void CSoundManager::AllSetVolume(float volume) {

	//全てのサウンドのボリュームをセットする
	for (int j = 0; j < SUD_TYPECOUNT; j++)
	{
		for (int i = 0; i < SOUNDCOUNT; i++)
		{
			m_CSound[i][j].SetVolume(volume);
		}
	}

}

void CSoundManager::SetVolume(int type, float volume) {

	//指定した種類のサウンドだけボリュームをセットする
	for (int i = 0; i < SOUNDCOUNT; i++) {

		m_CSound[i][type].SetVolume(volume);

	}

}

void CSoundManager::Initialize() {

	//サウンドの基礎設定
	for (int j = 0; j < SUD_TYPECOUNT; j++)
	{
		for (int i = 0; i < SOUNDCOUNT; i++)
		{
			m_CSound[i][j].SetSound(&m_Sound[j]);
			m_CSound[i][j].Initialize();
		}
	}

}

void CSoundManager::Update() {

	//サウンドの更新
	for (int j = 0; j < SUD_TYPECOUNT; j++)
	{
		for (int i = 0; i < SOUNDCOUNT; i++)
		{
			m_CSound[i][j].Update();
		}
	}

}


CSound* CSoundManager::Start(int type,int loop) {

	//サウンドの情報を渡す
	for (int i = 0; i < SOUNDCOUNT; i++) {

		if (m_CSound[i][type].IsPlay()) {

			continue;
		}

		//BGMならループをセットする
		if (loop) {

			m_CSound[i][type].Start(true);

		}
		else {

			m_CSound[i][type].Start(false);

		}
		
		return &m_CSound[i][type];

	}

	return NULL;

}

void CSoundManager::Stop(int type,int stopType) {

	//指定した種類のBGMを指定したタイプで停止させる
	for (int i = 0; i < SOUNDCOUNT; i++) {

		m_CSound[i][type].Stop(stopType);

	}
}

float CSoundManager::RenderDebug(int type) {

	for (int i = 0; i < SOUNDCOUNT; i++) {

		return m_CSound[i][type].RenderDebug();

	}
}


void CSoundManager::Release() {

	//サウンドの解放
	for (int j = 0; j < SUD_TYPECOUNT; j++)
	{

		m_Sound[j].Release();

	}
}
