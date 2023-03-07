//=============================================================================
//
// pause.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PAUSE_H_			//���̃}�N����`������Ȃ�������
#define _PAUSE_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class C2DPolygon;
class CUI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPause : public CObject
{
private:
	static const int MAX_PAUSE = 4;
	static const float SIZE_PAUSE_UI; 
	static const float SIZE_PAUSE_UI_HALF;

public:
	CPause();
	~CPause() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetPause(bool bUse) { m_bPause = bUse; }
	bool GetPause() { return m_bPause; }
	
private:
	bool m_bPause;
	int m_nMood;

	C2DPolygon *m_pUi;
	CUI *m_pBg;
};

#endif