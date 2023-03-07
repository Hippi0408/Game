//=============================================================================
//
// ranking.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RANKING_H_			//���̃}�N����`������Ȃ�������
#define _RANKING_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "name.h"

//�O���錾
class CNumber;
class C2DPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRanking
{
private:
	static const int MAX_RANKING_DIGIT = 8;
	static const float RANKING_SIZE;
	static const int MAX_AIRFRAME = 3;

	static const int MAX_STAGE = 6;
	static const float SIZE_UI;
	static const float SIZE_UI_HALF;

public:
	struct NameData
	{
		int nNameNumIndex[CName::MAX_NAME_LENGTH];
	};


	static const int MAX_RANKING = 10;
	CRanking();
	~CRanking();

	void Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void Create(const NameData *pName,const int *pScore, const int *pAirframe);
	void SetPLNewData(int *pNameIndex);
	void SaveRanking();

	D3DXVECTOR3 GetPos() { return m_Pos; }
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	void AddPos(D3DXVECTOR3 add) { m_Pos += add; }
	bool PLNewRanking();

private:
	int m_nScore[MAX_RANKING];
	int m_nAirframe[MAX_AIRFRAME];
	int m_nAirframeTex[MAX_RANKING];
	bool m_bNewScore;
	NameData m_NameData[MAX_RANKING];
	D3DXVECTOR3 m_Pos;
	CNumber *m_pCounter[MAX_RANKING];//���l��`�悷��N���X
	C2DPolygon *m_pAirframe[MAX_RANKING];
	C2DPolygon *m_pStageName;
	CName *m_pName[MAX_RANKING];//���l��`�悷��N���X
};

#endif