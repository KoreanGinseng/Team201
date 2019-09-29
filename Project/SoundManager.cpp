#include		"SoundManager.h"

CSoundManager* CSoundManager::m_pInstance = nullptr;

bool CSoundManager::Load() {

	//�T�E���h�̓ǂݍ���
	char* name[] = {

		"TestJump.mp3",
		"TestStageBGM.mp3",
	};

	for (int i = 0; i < SUD_TYPECOUNT; i++)
	{
		if (!m_Sound[i].Load(name[i]))
		{
			return false;
		}
	}
	return true;
}

void CSoundManager::Initialize() {

	//�T�E���h�̊�b�ݒ�
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

	//�T�E���h�̍X�V
	for (int j = 0; j < SUD_TYPECOUNT; j++)
	{
		for (int i = 0; i < SOUNDCOUNT; i++)
		{
			m_CSound[i][j].Update();
		}
	}
}


CSound* CSoundManager::Start(int type,int loop) {

	//�T�E���h�̏���n��
	for (int i = 0; i < SOUNDCOUNT; i++) {

		if (m_CSound[i][type].IsPlay()) {

			continue;
		}

		//BGM�Ȃ烋�[�v���Z�b�g����
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

	//�w�肵����ނ�BGM���w�肵���^�C�v�Œ�~������
	for (int i = 0; i < SOUNDCOUNT; i++) {

		m_CSound[i][type].Stop(stopType);

	}
}


void CSoundManager::Release() {

	//�T�E���h�̉��
	for (int j = 0; j < SUD_TYPECOUNT; j++)
	{

		m_Sound[j].Release();

	}
}
