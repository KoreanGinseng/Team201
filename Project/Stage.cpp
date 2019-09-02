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
	m_pObjEndData = (char*)malloc(m_XCount*m_YCount);

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
	for (int y = 0; y < m_YCount; y++) {
		for (int x = 0; x < m_XCount; x++) {
			pstr = strtok(NULL, ",");
			m_pObjEndData[y*m_XCount + x] = atoi(pstr);
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
	//for (float y = ((int)-scroll.y % hn) - hn; y < sch; y += hn) {
	for (float y = ((int)-scroll.y / 4 % hn) - hn; y < sch; y += hn) {
		//for (float x = ((int)-scroll.x % wn) - wn; x < scw; x += wn) {
		for (float x = ((int)-scroll.x / 4 % wn) - wn; x < scw; x += wn) {
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
			//m_ChipTexture.Render(-scroll.x + x * m_ChipSize, -scroll.y + y * m_ChipSize, cr);
			m_ChipTexture.Render(-scroll.x + x * m_ChipSize, -scroll.y + y * m_ChipSize, cr);
		}
	}
}

void CStage::RenderDebug(Vector2 scroll) {

}

void CStage::Release() {
	m_BackTexture.Release();
	m_ChipTexture.Release();

	for (int i = 0; i < m_EnemyTextureCount; i++) {
		m_pEnemyTexture[i].Release();
	}
	for (int i = 0; i < m_ItemTextureCount; i++) {
		m_pItemTexture[i].Release();
	}
	for (int i = 0; i < m_ObjectTextureCount; i++) {
		m_pObjectTexture[i].Release();
	}

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
	if (m_pObjEndData) {
		free(m_pObjEndData);
		m_pObjEndData = NULL;
	}
}

bool CStage::Collision(CRectangle r, Vector2& o) {
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
				//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まり値
				o.y += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
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

	return re;
}