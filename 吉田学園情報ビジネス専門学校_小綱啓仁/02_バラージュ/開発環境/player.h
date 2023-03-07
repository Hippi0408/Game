//=============================================================================
//
// player.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PLAYER_H_			//このマクロ定義がされなかったら
#define _PLAYER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "2dpolygon.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;
class CStatGauge;
class CSubunit;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public C2DPolygon
{
private:
	// ポリゴンの幅
	static const float SIZE_PLAYER;
	static const float PLAYER_MOVE;
	static const float PLAYER_BOOST_MOVE;
	static const int PLAYER_TYPE = 3;
	static const int BOOST_CNT = 30;
	static const int INVINCIBLE_TIME = 4 * 60; //無敵時間　（秒＊フレーム）
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
	bool Collision(D3DXVECTOR3 pos, float radius) override;//当たり判定

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