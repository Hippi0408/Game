//=============================================================================
//
// name.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _NAME_H_			//���̃}�N����`������Ȃ�������
#define _NAME_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBeeline;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CName
{
public:
	static const float NAME_SIZE_ADJUSTMENT;
	static const int MAX_NAME_LENGTH = 5;
	static const int MAX_NAME_INDEX = 32;
	static const int MAX_NAME_X = 8;
	static const int MAX_NAME_Y = 4;

	CName();
	~CName();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetName(const int nNameIndex);
	void ChangeName(const int *pNameIndex);
	void SetAllName(const int *pNameIndex);
	void BreakBeeline();
	void SetPos(D3DXVECTOR3 pos);
	void AddPos(D3DXVECTOR3 Add);
	void SetSize(float fSize) { m_fSize = fSize; }
	int GetTextureIndex() { return m_nTextureIndex; }
	D3DXVECTOR3 GetPos() { return m_Pos; }
	void SetFlashing() { m_bFlashing = true; }

private:
	CBeeline *m_pName[MAX_NAME_LENGTH];
	int m_aNameIndex[MAX_NAME_LENGTH];
	int m_nSetNameNum;
	float m_fSize;
	int m_nTextureIndex;
	D3DXVECTOR3 m_Pos;
	bool m_bFlashing;
};

#endif