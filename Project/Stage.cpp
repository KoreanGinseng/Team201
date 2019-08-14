#include	"Stage.h"

CStage::CStage() :
m_BackTexture(),
m_ChipTexture(),
m_pEnemyTexture(nullptr),
m_pItemTexture(nullptr),
m_pObjectTexture(nullptr),
m_ChipSize(0),
m_XCount(0),
m_YCount(0),
m_pChipData(nullptr),
m_pEnemyData(nullptr),
m_pItemData(nullptr),
m_pObjectData(nullptr),
m_EnemyTextureCount(0),
m_ItemTextureCount(0),
m_ObjectTextureCount(0),
m_EnemyCount(0),
m_ItemCount(0),
m_ObjectCount(0)
{
}

bool CStage::Load(char* pName) {
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL) {
		return FALSE;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C���T�C�Y�����ׂăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr)) {
		return FALSE;
	}
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr)) {
		return FALSE;
	}
	
	//�`�b�v�T�C�Y
	pstr = strtok(NULL, ",");
	m_ChipSize = atof(pstr);

	//�}�b�v�̃`�b�v��
	pstr = strtok(NULL, ",");
	m_XCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YCount = atoi(pstr);

	//�}�b�v�`�b�v�p�̃������m��
	m_pChipData = (char*)malloc(m_XCount*m_YCount);
	m_pEnemyData = (char*)malloc(m_XCount*m_YCount);
	m_pItemData = (char*)malloc(m_XCount*m_YCount);
	m_pObjectData = (char*)malloc(m_XCount*m_YCount);

	//�`�b�v�f�[�^�̓ǂݍ���
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			pstr = strtok(NULL, ",");
			m_pChipData[y*m_XCount + x] = atoi(pstr);
		}
	}

	//�G�e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr)) {
			return FALSE;
		}
	}
	//�z��f�[�^�̓ǂݍ���
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			pstr = strtok(NULL, ",");
			m_pEnemyData[y*m_XCount + x] = atoi(pstr);
			if (m_pEnemyData[y*m_XCount + x] > 0) {
				m_EnemyCount++;
			}
		}
	}

	//�A�C�e���e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr)) {
			return FALSE;
		}
	}
	//�z��f�[�^�̓ǂݍ���
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			pstr = strtok(NULL, ",");
			m_pItemData[y*m_XCount + x] = atoi(pstr);
			if (m_pItemData[y*m_XCount + x] > 0) {
				m_ItemCount++;
			}
		}
	}

	//�I�u�W�F�N�g�e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_ObjectTextureCount = atoi(pstr);
	m_pObjectTexture = new CTexture[m_ObjectTextureCount];
	for (int i = 0; i < m_ObjectTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pObjectTexture[i].Load(pstr)) {
			return FALSE;
		}
	}
	//�z��f�[�^�̓ǂݍ���
	m_ObjectCount = 0;
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			pstr = strtok(NULL, ",");
			m_pObjectData[y*m_XCount + x] = atoi(pstr);
			if (m_pObjectData[y*m_XCount + x] > 0) {
				m_ObjectCount++;
			}
		}
	}

	//�t�@�C�������
	fclose(fp);
	free(pBuffer);
	return TRUE;
}

void CStage::Initialize() {

}

void CStage::Update() {

}

void CStage::Render(Vector2 scroll) {
	//���i�̕`��
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-scroll.y % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-scroll.x % wn) - wn; x < scw; x += wn) {
			m_BackTexture.Render(x, y);
		}
	}

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͕`�悵�Ȃ�
			char cn = m_pChipData[y*m_XCount + x] - 1;
			if (cn < 0) {
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize*(cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			m_ChipTexture.Render(-scroll.x + x * m_ChipSize, -scroll.y + y * m_ChipSize);
		}
	}
}

void CStage::RenderDebug(Vector2 scroll) {

}

void CStage::Release() {
	m_BackTexture.Release();
	m_ChipTexture.Release();
	if (m_pChipData) {
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData) {
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pItemData) {
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pObjectData) {
		free(m_pObjectData);
		m_pObjectData = NULL;
	}
}