#include "Empty.h"



CEmpty::CEmpty()
{
	m_pRect = nullptr;
}


CEmpty::~CEmpty()
{
	if (m_pRect)
	{
		delete[] m_pRect;
		m_pRect = nullptr;
	}
}

void CEmpty::RectLoad(const char * pName)
{
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return;
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


	pstr = strtok(pBuffer, ",");
	m_RectCount = atoi(pstr);
	m_pRect = new CRectangle[m_RectCount];
	for (int i = 0; i < m_RectCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pRect[i].Left = m_Rect.Left + atoi(pstr);
		pstr = strtok(NULL, ",");
		m_pRect[i].Top = m_Rect.Top + atoi(pstr);
		pstr = strtok(NULL, ",");
		m_pRect[i].Right = m_Rect.Left + atoi(pstr);
		pstr = strtok(NULL, ",");
		m_pRect[i].Bottom = m_Rect.Top + atoi(pstr);
	}
	free(pBuffer);
	fclose(fp);
}
