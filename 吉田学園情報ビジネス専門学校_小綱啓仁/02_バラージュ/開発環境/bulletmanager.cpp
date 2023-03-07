//=============================================================================
//
// Bullet.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bulletmanager.h"
#include "explosion.h"
#include "sound.h"
#include <assert.h>
#include "bulletbase.h"
#include "bullet01.h"
#include "bullet02.h"
#include "bullet03.h"
#include "bullet04.h"
#include "bulletspecial01.h"
#include "bulletspecial02.h"


// ポリゴンの幅
const float CBulletManager::SIZE_BULLET = 16.0f;
// 一回の射撃の最大角度
const float CBulletManager::BULLET_ANGLE= 20.0f;
// バレットの情報
CBulletBase *CBulletManager::m_pBullet[BULLET_MAX] = {};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBulletManager::CBulletManager()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBulletManager::~CBulletManager()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CBulletManager::Init()
{
	ZeroMemory(m_pBullet, sizeof(m_pBullet));
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBulletManager::Uninit()
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] != nullptr)
		{
			// 終了処理
			m_pBullet[nCnt]->Uninit();
			delete m_pBullet[nCnt];
			m_pBullet[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBulletManager::Update()
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] == nullptr)
		{
			continue;
		}
		// 更新処理
		m_pBullet[nCnt]->Update();
		if (m_pBullet[nCnt]->IsUnused())
		{
			// 終了処理
			m_pBullet[nCnt]->Uninit();
			delete m_pBullet[nCnt];
			m_pBullet[nCnt] = nullptr;
		}

	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBulletManager::Draw()
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] != nullptr)
		{
			// 描画処理
			m_pBullet[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// 弾の発射処理
//*****************************************************************************
void CBulletManager::SetBullet(const Bullet bullet, const BulletMoveType type)
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] != nullptr)
		{
			continue;
		}

		m_pBullet[nCnt] = CreateBullet(bullet, type);

		break;
	}
}

//*****************************************************************************
// 弾の発射処理(まとめて)
//*****************************************************************************
void CBulletManager::ShotBullet(const Bullet bullet, const BulletMoveType type, int nbullet, float fangle,float fradius)
{
	D3DXMATRIX mtxRot;
	Bullet Bullet = bullet;
	D3DXVECTOR3 pos = bullet.pos;
	D3DXVECTOR3 vec = Bullet.Vector;
	float fAngle = -fangle / 2;
	float fNextAngle = fangle / (nbullet - 1);
	float fD3DXRadian;

	for (int nCnt = 0; nCnt < nbullet; nCnt++)
	{
		fD3DXRadian = D3DXToRadian(fAngle);

		D3DXMatrixRotationZ(&mtxRot, fD3DXRadian);
		D3DXVec3TransformCoord(&Bullet.Vector, &vec, &mtxRot);

		Bullet.pos.x = pos.x + Bullet.Vector.x * fradius;
		Bullet.pos.y = pos.y + Bullet.Vector.y * fradius;

		fAngle += fNextAngle;

		SetBullet(Bullet, type);
	}

}

//*****************************************************************************
// 弾の破棄（タイプ指定）
//*****************************************************************************
int CBulletManager::BreakBullet(BulletType type)
{
	int nBulletCnt = 0;
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] == nullptr)
		{
			continue;
		}

		if (m_pBullet[nCnt]->GetType() != type)
		{
			continue;
		}

		// 終了処理
		m_pBullet[nCnt]->Uninit();
		delete m_pBullet[nCnt];
		m_pBullet[nCnt] = nullptr;
		nBulletCnt++;
	}

	return nBulletCnt;
}

//*****************************************************************************
// 弾の当たり判定（タイプ指定）
//*****************************************************************************
bool CBulletManager::CollisionBullet(D3DXVECTOR3 pos, float radius,BulletType type)
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] == nullptr)
		{
			continue;
		}

		if (m_pBullet[nCnt]->GetType() != type)
		{
			continue;
		}

		if (m_pBullet[nCnt]->Collision(pos, radius))
		{
			CExplosion::CreateExplosion(m_pBullet[nCnt]->GetPos());
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
			// 終了処理
			m_pBullet[nCnt]->Uninit();
			delete m_pBullet[nCnt];
			m_pBullet[nCnt] = nullptr;
			return true;
		}
	}
	return false;
}

//*****************************************************************************
// 弾のクリエイト処理
//*****************************************************************************
CBulletBase * CBulletManager::CreateBullet(Bullet Bullet, BulletMoveType type)
{

	CBulletBase* pBullet = nullptr;

	switch (type)
	{
	case BULLET_MOVE_00:
		pBullet = new CBulletBase;
		break;
	case BULLET_MOVE_01:
		pBullet = new CBullet01;
		break;
	case BULLET_MOVE_02:
		pBullet = new CBullet02;
		break;
	case BULLET_MOVE_03:
		pBullet = new CBullet03;
		break;
	case BULLET_MOVE_04:
		pBullet = new CBullet04;
		break;
	case BULLET_MOVE_SPECIAL_01:
		pBullet = new CBulletSpecial01;
		break;
	case BULLET_MOVE_SPECIAL_02:
		pBullet = new CBulletSpecial02;
		break;
	case BULLET_MOVE_MAX:
	default:
		assert(false);
		break;
	}

	if (FAILED(pBullet->Init()))
	{
		assert(false);
	}

	pBullet->SetBullet(Bullet);

	return pBullet;
}