//=============================================================================
//
// game.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME_H_			//���̃}�N����`������Ȃ�������
#define _GAME_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUI;
class CPlayer;
class CEnemyManager;
class CBulletManager;
class CRead;
class CCamera;
class CLight;
class CGame3DBG;
class CPause;
class CWarning;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame : public CObject
{
private:
	static const int WARNING_CNT_MAX = 300;

public:
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CEnemyManager *GetEnemy() { return m_pEnemyManager; }

	void SetWarning();
	void BossDied() { m_bBossDied = true; }

private:
	static CPlayer *m_pPlayer;
	CPause *m_pPause;
	CUI *m_pUi;
	static CEnemyManager *m_pEnemyManager;
	static CBulletManager *m_pBulletManager;
	CRead *m_pRead;
	CCamera *m_pCamera;
	CGame3DBG *m_pBGObj;
	CLight *m_pLight;
	CWarning *m_pWarning;
	int m_nWarningCnt;
	bool m_bBossDied;
};

#endif