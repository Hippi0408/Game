//=============================================================================
//
// player.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PLAYER_H_			//���̃}�N����`������Ȃ�������
#define _PLAYER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "2dpolygon.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;
class CStatGauge;
class CSubunit;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public C2DPolygon
{
private:
	// �|���S���̕�
	static const float SIZE_PLAYER;
	static const float PLAYER_MOVE;
	static const float PLAYER_BOOST_MOVE;
	static const int PLAYER_TYPE = 3;
	static const int BOOST_CNT = 30;
	static const int INVINCIBLE_TIME = 4 * 60; //���G���ԁ@�i�b���t���[���j
	static const D3DXCOLOR PLAYER_CENTER_COLOR[PLAYER_TYPE];
	static const float PLAYER_CENTER_SIZE;


public:
	CPlayer();
	~CPlayer() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void ShootBullet(D3DXVECTOR3 Vector, float fMove);

	void SetUp(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move) override;
	bool IsUnused() override;
	bool HetPlayer(D3DXVECTOR3 pos, float radius);
	bool Collision(D3DXVECTOR3 pos, float radius) override;//�����蔻��

private:
	CStatGauge *m_pLife;
	CStatGauge *m_pStamina;
	bool m_bBoost;
	int m_nBoostCnt;
	int m_nInvincibleTime;
	D3DXVECTOR3 m_BoostVector;
	int m_nBulletCoolTime;
	int m_nBulletTextIndex;
	int m_nEffectTextIndex;
	int m_nAirframe;
	C2DPolygon *m_pCenter;
	CSubunit *m_pSubunit;
	D3DXCOLOR m_BulletCol;
};

#endif