//=============================================================================
//
// explosion.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _EXPLOSION_H_			//���̃}�N����`������Ȃ�������
#define _EXPLOSION_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "anim.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExplosion
{
private:
	// �|���S���̕�
	static const float SIZE_EXPLOSION;

	static const int MAX_BOSS_EXPLOSION_CNT = 5;
	static const int MAX_BOSS_EXPLOSION = 30;
	static const D3DXVECTOR3 BOSS_EXPLOSION_POS[MAX_BOSS_EXPLOSION];

public:
	CExplosion();
	~CExplosion();

	static void Init();
	static void Uninit();

	static void CreateExplosion(D3DXVECTOR3 pos);
	static void BossDiedExplosion();

private:
	static CExplosion *m_pExplosion;
	static int m_nExplosionTextIndex;
	static int m_nExplosionCnt;
	static int m_nExplosionNextCnt;
	
};

#endif