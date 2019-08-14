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
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL) {
		return FALSE;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルサイズをすべてバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr)) {
		return FALSE;
	}
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr)) {
		return FALSE;
	}
	
	//チップサイズ
	pstr = strtok(NULL, ",");
	m_ChipSize = atof(pstr);

	//マップのチップ数
	pstr = strtok(NULL, ",");
	m_XCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YCount = atoi(pstr);

	//マップチップ用のメモリ確保
	m_pChipData = (char*)malloc(m_XCount*m_YCount);
	m_pEnemyData = (char*)malloc(m_XCount*m_YCount);
	m_pItemData = (char*)malloc(m_XCount*m_YCount);
	m_pObjectData = (char*)malloc(m_XCount*m_YCount);

	//チップデータの読み込み
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			pstr = strtok(NULL, ",");
			m_pChipData[y*m_XCount + x] = atoi(pstr);
		}
	}

	//敵テクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr)) {
			return FALSE;
		}
	}
	//配列データの読み込み
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

	//アイテムテクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr)) {
			return FALSE;
		}
	}
	//配列データの読み込み
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

	//オブジェクトテクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_ObjectTextureCount = atoi(pstr);
	m_pObjectTexture = new CTexture[m_ObjectTextureCount];
	for (int i = 0; i < m_ObjectTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pObjectTexture[i].Load(pstr)) {
			return FALSE;
		}
	}
	//配列データの読み込み
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

	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);
	return TRUE;
}

void CStage::Initialize() {

}

void CStage::Update() {

}

void CStage::Render(Vector2 scroll) {
	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-scroll.y % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-scroll.x % wn) - wn; x < scw; x += wn) {
			m_BackTexture.Render(x, y);
		}
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//マップチップの描画
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			//描画するチップ番号
			//チップ番号０は描画しない
			char cn = m_pChipData[y*m_XCount + x] - 1;
			if (cn < 0) {
				continue;
			}
			//マップチップの矩形
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize*(cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
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