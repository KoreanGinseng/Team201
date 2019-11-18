/*****************************************************************
 *	@file			Stage.cpp
 *	@brief			�X�e�[�W�N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/

//INCLUDE
#include	"Stage.h"

std::string CStage::IsExt(const char * pName)
{
	std::string fs = pName;
	int len = fs.find_last_of(".");
	std::string ext = fs.substr(len);
	if (ext == ".png" || ext == ".bmp" || ext == ".dds")
	{
		return picture;
	}
	else if (ext == ".bin")
	{
		return anim;
	}
	return "";
}

CTexturePtr CStage::TextureLoad(char * pName)
{
	if (IsExt(pName) == picture)
	{
		return g_pTextureManager->GetResource(pName);

	}
	else if (IsExt(pName) == anim)
	{
		return g_pAnimManager->GetResource(pName)->GetTexture();
	}
	return nullptr;
}

int CStage::ChipDataLoad(char * str, char * pData)
{
	//�`�b�v�f�[�^�̓ǂݍ���
	int count = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			str = strtok(NULL, ",");
			pData[y*m_XCount + x] = atoi(str);
			if (pData[y*m_XCount + x] > 0)
			{
				count++;
			}
		}
	}
	return count;
}

//�R���X�g���N�^
CStage::CStage() :
	m_pBackTexture(nullptr),
	m_pChipTexture(nullptr),
	m_ChipSize(0),
	m_XCount(0),
	m_YCount(0),
	m_pChipData(nullptr),
	m_pMapObjData(nullptr),
	m_pBackChipData(nullptr),
	m_pEnemyData(nullptr),
	m_pItemData(nullptr),
	m_pObjectData(nullptr),
	m_pObjEndData(nullptr),
	m_MapObjTextureCount(0),
	m_BackChipTextureCount(0),
	m_EnemyTextureCount(0),
	m_ItemTextureCount(0),
	m_ObjectTextureCount(0),
	m_EnemyCount(0),
	m_ItemCount(0),
	m_ObjectCount(0)
{
}

//�ǂݍ���
bool CStage::Load(const char* pName) {
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
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
	//if (!m_BackTexture.Load(pstr)) {
	m_pBackTexture = g_pTextureManager->GetResource(pstr);
	if (m_pBackTexture == nullptr) 
	{
		free(pBuffer);
		pBuffer = nullptr;
		return FALSE;
	}
	pstr = strtok(NULL, ",");
	m_pChipTexture = g_pTextureManager->GetResource(pstr);
	if (m_pChipTexture == nullptr)
	{
		free(pBuffer);
		pBuffer = nullptr;
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
	m_pMapObjData = (char*)malloc(m_XCount*m_YCount);
	m_pBackChipData = (char*)malloc(m_XCount*m_YCount);
	m_pEnemyData = (char*)malloc(m_XCount*m_YCount);
	m_pItemData = (char*)malloc(m_XCount*m_YCount);
	m_pObjectData = (char*)malloc(m_XCount*m_YCount);
	m_pObjEndData = (char*)malloc(m_XCount*m_YCount);

	//�`�b�v�f�[�^�̓ǂݍ���
	ChipDataLoad(pstr, m_pChipData);

	//�}�b�v�I�u�W�F�N�g�e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	int m_MapObjTextureCount = atoi(pstr);
	for (int i = 0; i < m_MapObjTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pMapObjTexture.push_back(TextureLoad(pstr));
		if (m_pMapObjTexture[i] == nullptr)
		{
			free(pBuffer);
			pBuffer = nullptr;
			return FALSE;
		}
	}
	
	//�`�b�v�f�[�^�̓ǂݍ���
	m_MapObjCount = ChipDataLoad(pstr, m_pMapObjData);
	
	//�w�i�p�[�c�e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	int m_BackChipTextureCount = atoi(pstr);
	for (int i = 0; i < m_BackChipTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pBackChipTexture.push_back(TextureLoad(pstr));
		if (m_pBackChipTexture[i] == nullptr)
		{
			free(pBuffer);
			pBuffer = nullptr;
			return FALSE;
		}
	}
	
	//�`�b�v�f�[�^�̓ǂݍ���
	m_BackChipCount = ChipDataLoad(pstr, m_pBackChipData);

	//�G�e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);

	for (int i = 0; i < m_EnemyTextureCount; i++) 
	{
		pstr = strtok(NULL, ",");
		m_pEnemyTexture.push_back(TextureLoad(pstr));
		if (m_pEnemyTexture[i] == nullptr)
		{
			free(pBuffer);
			pBuffer = nullptr;
			return FALSE;
		}
	}
	//�z��f�[�^�̓ǂݍ���
	m_EnemyCount = ChipDataLoad(pstr, m_pEnemyData);

	//�A�C�e���e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pItemTexture.push_back(TextureLoad(pstr));
		if (m_pItemTexture[i] == nullptr)
		{
			free(pBuffer);
			pBuffer = nullptr;
			return FALSE;
		}
	}
	//�z��f�[�^�̓ǂݍ���
	m_ItemCount = ChipDataLoad(pstr, m_pItemData);

	//�I�u�W�F�N�g�e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_ObjectTextureCount = atoi(pstr);
	for (int i = 0; i < m_ObjectTextureCount; i++) 
	{
		pstr = strtok(NULL, ",");
		m_pObjectTexture.push_back(TextureLoad(pstr));
		if (m_pObjectTexture[i] == nullptr)
		{
			free(pBuffer);
			pBuffer = nullptr;
			return FALSE;
		}
	}
	//�z��f�[�^�̓ǂݍ���
	m_ObjectCount = ChipDataLoad(pstr, m_pObjectData);
	ChipDataLoad(pstr, m_pObjEndData);

	free(pBuffer);
	pBuffer = nullptr;

	//�t�@�C�������
	fclose(fp);
	return TRUE;
}

//������
void CStage::Initialize(CDynamicArray<CEnemy*>* pEnemyArray, CDynamicArray<CItem*>* pItemArray, CDynamicArray<CTargetObj*>* pTargetObjArray)
{
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			(*pEnemyArray)[n]->SetTexture(m_pEnemyTexture[on]);
			(*pEnemyArray)[n]->CreateMove(on);
			(*pEnemyArray)[n]->CreateAnim(FileName[ANIMATION_ENEMY_1 + on]);
			(*pEnemyArray)[n]->SetPos(x * m_ChipSize, y * m_ChipSize);
			(*pEnemyArray)[n++]->Initialize();
		}
	}
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			(*pItemArray)[n]->SetTexture(m_pItemTexture[on]);
			(*pItemArray)[n]->CreateAnim(FileName[ANIMATION_ITEM_1 + on]);
			(*pItemArray)[n]->SetPos(x * m_ChipSize, y * m_ChipSize);
			(*pItemArray)[n++]->Initialize();
		}
	}
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pObjectData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			(*pTargetObjArray)[n]->SetTexture(m_pObjectTexture[on]);
			(*pTargetObjArray)[n]->SetPos(x * m_ChipSize, y * m_ChipSize);
			(*pTargetObjArray)[n]->CreateAnim(FileName[ANIMATION_OBJ_1 + on]);
			(*pTargetObjArray)[n]->SetMotionEnd(m_pObjEndData[y * m_XCount + x]);
			(*pTargetObjArray)[n]->Initialize();
			(*pTargetObjArray)[n++]->SetObject(on);
		}
	}
}


//�X�V
void CStage::Update() {

}

//�`��
void CStage::Render(Vector2 scroll) {
	//���i�̕`��
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_pBackTexture->GetWidth();
	int hn = m_pBackTexture->GetHeight();
	for (float y = ((int)-scroll.y / 4 % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-scroll.x / 4 % wn) - wn; x < scw; x += wn) {
			m_pBackTexture->Render(x, y);
		}
	}

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_pChipTexture->GetWidth() / m_ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_YCount; y++) 
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͕`�悵�Ȃ�
			char cn = m_pChipData[y*m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize*(cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			m_pChipTexture->Render(-scroll.x + x * m_ChipSize, -scroll.y + y * m_ChipSize, cr);
		}
	}
}

//�f�o�b�O�`��
void CStage::RenderDebug(Vector2 scroll) {

}

//���
void CStage::Release() {
	if (m_pChipData != nullptr) {
		free(m_pChipData);
		m_pChipData = nullptr;
	}
	if (m_pMapObjData != nullptr) {
		free(m_pMapObjData);
		m_pMapObjData = nullptr;
	}
	if (m_pBackChipData != nullptr) {
		free(m_pBackChipData);
		m_pBackChipData = nullptr;
	}
	if (m_pEnemyData != nullptr) {
		free(m_pEnemyData);
		m_pEnemyData = nullptr;
	}
	if (m_pItemData != nullptr) {
		free(m_pItemData);
		m_pItemData = nullptr;
	}
	if (m_pObjectData != nullptr) {
		free(m_pObjectData);
		m_pObjectData = nullptr;
	}
	if (m_pObjEndData != nullptr) {
		free(m_pObjEndData);
		m_pObjEndData = nullptr;
	}
	m_pEnemyTexture.clear();
	m_pItemTexture.clear();
	m_pObjectTexture.clear();
}

//�����蔻��
bool CStage::OverValue(CRectangle r, Vector2& o) {
	bool re = false;

	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XCount)
	{
		rc = m_XCount - 1;
	}
	if (bc >= m_YCount)
	{
		bc = m_YCount - 1;
	}

	//�����蔻��������`�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y*m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(x*m_ChipSize, y*m_ChipSize, x*m_ChipSize + m_ChipSize, y*m_ChipSize + m_ChipSize);
			//�����蔻��p�̃L�����N�^��`
			//���Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;//
			brec.Expansion(-6, 0);//
			//���Ɠ����蔻��
			if (cr.CollisionRect(brec))
			{
				re = true;
				if (cn == RIGHTSLOPE || cn == RIGHTSLOPE2)
				{
					float sp = (cr.Right - brec.Left) / cr.GetWidth();
					if (sp < 0.0f)
					{
						sp = 0.0f;
					}
					else if (sp > 1.0f)
					{
						sp = 1.0f;
					}
					//�Ζʂ̏�̈ʒu�����߂�
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					if (brec.Bottom < cTop)
					{
						continue;
					}
					o.y += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else
				{
					//���̖��܂�Ȃ̂Ń`�b�v�̏�[�����`�̉��[�̒l���������l�����܂�l
					o.y += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}
			if (cn != RIGHTSLOPE || cn != RIGHTSLOPE2)
			{

			//�����蔻��p�̃L�����N�^��`
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle lrec = r;
			lrec.Right = lrec.Left - 1;//
			lrec.Expansion(0, -6);//
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;//
			rrec.Expansion(0, -6);//
			//���Ɠ����蔻��
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//���̖��܂�Ȃ̂Ń`�b�v�E�[�����`�̍��[�̒l���������l�����܂�̒l
				o.x += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//�E�Ɠ����蔻��
			if (cr.CollisionRect(rrec))
			{
				re = true;
				//�E�̖��܂�Ȃ̂Ń`�b�v�̍��[����
				o.x += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//�����蔻��p�̃L�����N�^��`
			//��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle trec = r;
			trec.Bottom = trec.Top - 1;//
			trec.Expansion(-6, 0);//
			//��Ɠ����蔻��
			if (cr.CollisionRect(trec))
			{
				re = true;
				//��̖��܂�Ȃ̂Ń`�b�v�����[�����`�̏�[��
				o.y += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
			}
		}
	}

	return re;
}