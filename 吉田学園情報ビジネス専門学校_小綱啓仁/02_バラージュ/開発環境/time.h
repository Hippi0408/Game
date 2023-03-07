//=============================================================================
//
// time.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TIME_H_			//���̃}�N����`������Ȃ�������
#define _TIME_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;
enum MODE_TYPE;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTime
{
private:

public:

	CTime();
	~CTime();

	static HRESULT Init(D3DXVECTOR3 pos, int nDigit, int nNumerical, int nTime, float fSize);
	static void Uninit();
	static void Update(MODE_TYPE type);
	static void Draw();

	static int GetTime() { return m_nTime; }
	static void SetTimer(int nTime) { m_nTime = nTime; }

private:
	static CTime *m_pCTime;
	static CNumber *m_pTime;
	static int m_nTime;
	static int m_nFPS;
};

#endif