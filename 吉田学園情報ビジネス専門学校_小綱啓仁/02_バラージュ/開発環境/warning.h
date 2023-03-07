//=============================================================================
//
// warning.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _WARNING_H_			//���̃}�N����`������Ȃ�������
#define _WARNING_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class C2DPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWarning
{
private:
	static const int MAX_WARNING = 4;
	static const D3DXVECTOR3 WARNING_POS[MAX_WARNING];
	static const D3DXVECTOR3 WARNING_ROT[MAX_WARNING];
	static const D3DXVECTOR2 WARNING_SISE[MAX_WARNING];

public:
	CWarning();
	~CWarning();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetWarning() { return m_bWarning; }
	void SetWarning() { m_bWarning = true; }
	bool OutWarning();

private:
	C2DPolygon *m_pWarning[MAX_WARNING];
	C2DPolygon *m_pRedFade;
	bool m_bWarning;
};

#endif