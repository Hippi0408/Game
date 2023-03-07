//=============================================================================
//
// subunit03.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _SUBUUNIT03_H_			//���̃}�N����`������Ȃ�������
#define _SUBUUNIT03_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "subunit.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class C2DPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSubunit03 : public CSubunit
{
private:
	static const float SUB_UNIT_SUBTRAHEND_Y;
	static const float SUB_UNIT_SUBTRAHEND_X;
	static const float X_SUB_UNIT_WIDTH;
public:
	CSubunit03();
	~CSubunit03() override;
	void Update(const D3DXVECTOR3 pos) override;
	void SetInitPos(const D3DXVECTOR3 pos) override;
	void SetBullet(int nTextIndex, D3DXVECTOR3 pos) override;

protected:

private:

};

#endif