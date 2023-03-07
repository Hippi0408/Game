//=============================================================================
//
// beeline.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BEELINE_H_			//���̃}�N����`������Ȃ�������
#define _BEELINE_H_			//2�d�C���N���[�h�h�~�̃}�N����`

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
class CBeeline
{
public:
	static const int MAX_NAME_LENGTH = 4;
	static const int MAX_NAME_INDEX = 32;
	static const int MAX_NAME_X = 8;
	static const int MAX_NAME_Y = 4;

	CBeeline();
	~CBeeline();

	HRESULT Init();
	void Uninit(); 
	void Update();
	void Draw();

	void SetBeeline(const int nNameIndex);
	void ChangeBeeline(const int nNameIndex);
	void SetPos(D3DXVECTOR3 pos);
	void SetTextureIndex(int nIndex) { m_nTextureIndex = nIndex; }
	void AddPos(D3DXVECTOR3 Add);
	void SetSize(float fSize) { m_fSize = fSize; }
	D3DXVECTOR3 GetPos() { return m_Pos; }
	int GetBeeline() { return m_nBeelineIndex; }
	void SetFlashing() { m_bFlashing = true; }

private:
	C2DPolygon *m_pBeeline;
	int m_nBeelineIndex;
	float m_fSize;
	int m_nTextureIndex;
	D3DXVECTOR3 m_Pos;
	bool m_bFlashing;
};

#endif