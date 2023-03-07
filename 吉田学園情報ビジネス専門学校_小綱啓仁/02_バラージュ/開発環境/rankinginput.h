//=============================================================================
//
// rankinginput.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RANKINGINPUT_H_			//���̃}�N����`������Ȃ�������
#define _RANKINGINPUT_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "name.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBeeline;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRankingInput
{
public:
	static const float SIZE_SET_MAME;
	static const float SIZE_SET_SELECT_MAME;
	static const int SELECT_PL_MAME = 5; //�I��p�̐�
	static const int SELECT_PL_MAME_HALF = 2; //�I��p�̐�
	static const int SET_PL_MAME = 32; //�I��p�̐�
	static const int SET_PL_MAME_HALF = SET_PL_MAME / 2; //�I��p�̐�
	static const int CHANGE_CNT = 10; //�I��p�̐�

	CRankingInput();
	~CRankingInput();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	bool Update();
	void Draw();
	
private:
	CName *m_pPLName;
	CBeeline *m_pSetName[SET_PL_MAME];
	D3DXVECTOR3 m_Pos;
	int m_nCurrentValue;//�I�𒆂̐��l
	int m_nFpsCnt;
	int m_nSetNameNum;
	bool m_bChange;
	bool m_bUp;
	bool m_bSetEnd;
	int m_aPLNameIndex[CName::MAX_NAME_LENGTH];
};

#endif