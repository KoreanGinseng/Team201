/*****************************************************************
 *	@file			Stage.cpp
 *	@brief			ステージクラス
 *	@author			井上颯騎
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
	//チップデータの読み込み
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

//コンストラクタ
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

//読み込み
bool CStage::Load(const char* pName) {
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
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
	m_pMapObjData = (char*)malloc(m_XCount*m_YCount);
	m_pBackChipData = (char*)malloc(m_XCount*m_YCount);
	m_pEnemyData = (char*)malloc(m_XCount*m_YCount);
	m_pItemData = (char*)malloc(m_XCount*m_YCount);
	m_pObjectData = (char*)malloc(m_XCount*m_YCount);
	m_pObjEndData = (char*)malloc(m_XCount*m_YCount);

	//チップデータの読み込み
	ChipDataLoad(pstr, m_pChipData);

	//マップオブジェクトテクスチャの読み込み
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
	
	//チップデータの読み込み
	m_MapObjCount = ChipDataLoad(pstr, m_pMapObjData);
	
	//背景パーツテクスチャの読み込み
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
	
	//チップデータの読み込み
	m_BackChipCount = ChipDataLoad(pstr, m_pBackChipData);

	//敵テクスチャの読み込み
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
	//配列データの読み込み
	m_EnemyCount = ChipDataLoad(pstr, m_pEnemyData);

	//アイテムテクスチャの読み込み
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
	//配列データの読み込み
	m_ItemCount = ChipDataLoad(pstr, m_pItemData);

	//オブジェクトテクスチャの読み込み
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
	//配列データの読み込み
	m_ObjectCount = ChipDataLoad(pstr, m_pObjectData);
	ChipDataLoad(pstr, m_pObjEndData);

	free(pBuffer);
	pBuffer = nullptr;

	//ファイルを閉じる
	fclose(fp);
	return TRUE;
}

//初期化
void CStage::Initialize(CDynamicArray<CEnemy*>* pEnemyArray, CDynamicArray<CItem*>* pItemArray, CDynamicArray<CTargetObj*>* pTargetObjArray)
{
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
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
			//配置番号
			//番号０は配置しない
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
			//配置番号
			//番号０は配置しない
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


//更新
void CStage::Update() {

}

//描画
void CStage::Render(Vector2 scroll) {
	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_pBackTexture->GetWidth();
	int hn = m_pBackTexture->GetHeight();
	for (float y = ((int)-scroll.y / 4 % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-scroll.x / 4 % wn) - wn; x < scw; x += wn) {
			m_pBackTexture->Render(x, y);
		}
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_pChipTexture->GetWidth() / m_ChipSize;
	//マップチップの描画
	for (int y = 0; y < m_YCount; y++) 
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//描画するチップ番号
			//チップ番号０は描画しない
			char cn = m_pChipData[y*m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize*(cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			m_pChipTexture->Render(-scroll.x + x * m_ChipSize, -scroll.y + y * m_ChipSize, cr);
		}
	}
}

//デバッグ描画
void CStage::RenderDebug(Vector2 scroll) {

}

//解放
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

//当たり判定
bool CStage::OverValue(CRectangle r, Vector2& o) {
	bool re = false;

	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//ステージの範囲外にはならないようにする
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

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定を行う
	//それ以外の番号は当たることはないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号０は当たり判定しない
			char cn = m_pChipData[y*m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(x*m_ChipSize, y*m_ChipSize, x*m_ChipSize + m_ChipSize, y*m_ChipSize + m_ChipSize);
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成する。
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;//
			brec.Expansion(-6, 0);//
			//下と当たり判定
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
					//斜面の上の位置を求める
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
					//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まり値
					o.y += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}
			if (cn != RIGHTSLOPE || cn != RIGHTSLOPE2)
			{

			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = r;
			lrec.Right = lrec.Left - 1;//
			lrec.Expansion(0, -6);//
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;//
			rrec.Expansion(0, -6);//
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//左の埋まりなのでチップ右端から矩形の左端の値を引いた値が埋まりの値
				o.x += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//右と当たり判定
			if (cr.CollisionRect(rrec))
			{
				re = true;
				//右の埋まりなのでチップの左端から
				o.x += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//当たり判定用のキャラクタ矩形
			//上で範囲を限定した専用の矩形を作成する。
			CRectangle trec = r;
			trec.Bottom = trec.Top - 1;//
			trec.Expansion(-6, 0);//
			//上と当たり判定
			if (cr.CollisionRect(trec))
			{
				re = true;
				//上の埋まりなのでチップした端から矩形の上端を
				o.y += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
			}
		}
	}

	return re;
}