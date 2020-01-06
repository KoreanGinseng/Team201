#pragma once
#include	"Mof.h"
#include	<unordered_map>
#include	"Sound.h"

constexpr	int		DefSoundPool = 10;			//! �Đ��v�[����

//�T�E���h�G�t�F�N�g�Ǘ��N���X
class CSoundManager
{
private:
	std::unordered_map<std::string, CDynamicArray<CSound*>> m_ResourceSE;	//! �f�[�^
	std::unordered_map<std::string, CSoundBuffer*> m_ResourceBGM;			//! �f�[�^
	CSoundManager(void);
	~CSoundManager(void);
public:
	static CSoundManager* GetSound(void);									//! �}�l�[�W���[�Ăяo�� 
	static CSound* GetSoundSE(const std::string& str);						//! �Đ��\�ȃT�E���h�擾
	static CSoundBuffer* GetSoundBGM(const std::string& str);				//! �Đ��\�ȃT�E���h�擾
	static CSoundBuffer* GetSoundBuffer(const std::string& str);			//! �Đ��\�ȃT�E���h�擾
	static void PlaySE(const std::string& str);								//! �Đ�
	static void PlayBGM(const std::string& str);							//! �Đ�
	static void SetVolumeSE(const std::string& str, const float& vol);		//! ���ʂ̒��� vol(0.0f ~ 1.0f)
	static void SetVolumeBGM(const std::string& str, const float& vol);		//! ���ʂ̒��� vol(0.0f ~ 1.0f)
	static bool LoadSE(const std::string& str);								//! �Ǎ�
	static bool LoadBGM(const std::string& str);							//! �Ǎ�
	static void Update(void);												//! �T�E���h����
	static void Release(void);												//! ���
};

