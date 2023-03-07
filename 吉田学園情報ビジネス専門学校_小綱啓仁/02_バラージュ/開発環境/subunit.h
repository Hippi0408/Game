//=============================================================================
//
// subunit.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _SUBUUNIT_H_			//���̃}�N����`������Ȃ�������
#define _SUBUUNIT_H_			//2�d�C���N���[�h�h�~�̃}�N����`

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
class CSubunit
{
protected:
	static const int MAX_SUBUNIT = 2;
	static const float MAX_RANGE_WITH_PLAYER[MAX_SUBUNIT];
	static const float SIZE_SUBUNIT;
public:
	CSubunit();
	virtual ~CSubunit();

	HRESULT Init(const D3DXVECTOR3 pos);
	void Uninit();
	void Draw();
	void EffeCt(const D3DXVECTOR3 pos);
	void BreakSubunit() { m_bUes = false; }

	virtual void Update(const D3DXVECTOR3 pos) = 0;
	virtual void SetInitPos(const D3DXVECTOR3 pos) = 0;
	virtual void SetBullet(int nTextIndex, D3DXVECTOR3 pos) = 0;

protected:
	C2DPolygon *m_pSubunit[MAX_SUBUNIT];
	int m_nSubunitCnt;
	int m_nSubunitTexIndex;
	D3DXCOLOR m_Color;
private:
	bool m_bUes;
};

#endif