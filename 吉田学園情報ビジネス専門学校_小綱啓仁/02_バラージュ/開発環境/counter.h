//=============================================================================
//
// counter.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _COUNTER_H_			//���̃}�N����`������Ȃ�������
#define _COUNTER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCounter
{
private:

public:

	CCounter();//�R���X�g���N�^
	~CCounter();//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, int nDigit, float fSize, int nNumerical);//������
	void Uninit();//�I������
	void Draw();//�`�揈��
	void Add(int nAdd);
	int GetCount() { return m_nCounter; }

	static void AllUninit();
	static void AllDraw();

	static CCounter *Create();
	static void AddCounter(int nAdd);//�J�E���g��i�߂�
	static int GetCounter() { return m_pCCounter->GetCount(); }

private:
	static CCounter *m_pCCounter;//�����̃|�C���^
	CNumber *m_pCounter;//���l��`�悷��N���X
	int m_nCounter;//���݂̐��l
};

#endif