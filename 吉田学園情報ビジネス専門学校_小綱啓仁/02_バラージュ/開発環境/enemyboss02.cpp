//=============================================================================
//
// enemyboss02.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemyboss02.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"
#include "counter.h"
#include "manager.h"
#include "explosion.h"
#include <assert.h>
#include "sound.h"

const float CEnemyBoss02::ENEMY_BOSS02_SIZE = 50.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemyBoss02::CEnemyBoss02()
{
	m_nFixedValueBodyMax = BOSS_BODY_NUMBER;
	m_fBodySize = ENEMY_BOSS02_SIZE;
	m_nBossBodyMax = m_nFixedValueBodyMax - 1;
	m_nBulletCoolTime = 0;
	m_nCarrent = 0;
	m_nBossAttack = 0;
	ZeroMemory(&m_BossPosOld, sizeof(m_BossPosOld));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemyBoss02::~CEnemyBoss02()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemyBoss02::Init()
{
	for (int nCnt = 0; nCnt < m_nFixedValueBodyMax; nCnt++)
	{
		m_pBossBody[nCnt] = nullptr;
		m_bBody[nCnt] = true;
		m_nBodyLife[nCnt] = 20;
		m_fBodyRot[nCnt] = 0.0f;
	}

	if (FAILED(C2DPolygon::Init()))
	{
		assert(false);
	}
	m_nBossAttack = 0;
	SetEnemyMove(1.0f);
	SetDiagonalLine(m_fBodySize, m_fBodySize);//表示するポリゴンの縦横幅設定
	SetPolygon();

	for (int nCnt = 0; nCnt < m_nFixedValueBodyMax; nCnt++)
	{
		m_pBossBody[nCnt] = new C2DPolygon;

		if (FAILED(m_pBossBody[nCnt]->Init()))
		{
			assert(false);
		}
		m_pBossBody[nCnt]->SetDiagonalLine(m_fBodySize, m_fBodySize);
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemyBoss02::Uninit()
{
	for (int nCnt = 0; nCnt < m_nFixedValueBodyMax; nCnt++)
	{
		if (m_pBossBody[nCnt] != nullptr)
		{
			m_pBossBody[nCnt]->Uninit();
			delete m_pBossBody[nCnt];
			m_pBossBody[nCnt] = nullptr;
		}
	}

	C2DPolygon::Uninit();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemyBoss02::Draw()
{
	C2DPolygon::Draw();
	int nTex = this->GetTextIndex();

	for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
	{
		if (m_pBossBody[nCnt] == nullptr)
		{
			assert(false);
		}
		m_pBossBody[nCnt]->SetTextIndex(nTex);
		m_pBossBody[nCnt]->Draw();
	}
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemyBoss02::IsUnused()
{
	if (m_nLife <= 0)
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT, 180);

		for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
		{
			CExplosion::CreateExplosion(m_pBossBody[nCnt]->GetPos());
		}

		return true;
	}
	return false;
}

//*****************************************************************************
// 当たり判定
//*****************************************************************************
bool CEnemyBoss02::Collision(D3DXVECTOR3 pos, float radius)
{
	if (EnemyBossHeadCollision(pos,radius))
	{//頭だけの判定
		return true;
	}

	for (int nCnt = 0;nCnt <= m_nBossBodyMax;nCnt++)
	{
		if(m_pBossBody[nCnt]->Collision(pos,radius))
		{
			m_nBodyLife[m_nBossBodyMax] -= 1;
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
			if (m_nBodyLife[m_nBossBodyMax] <= 0)
			{
				CCounter::AddCounter(20);
				m_nBossBodyMax--;
			}

			return true;
		}
	}

	
	return false;
}

//*****************************************************************************
// 敵の移動
//*****************************************************************************
void CEnemyBoss02::EnemyMove()
{
	float fMove = GetEnemyMove();
	D3DXVECTOR3 move = GetMove();
	if (fMove < 6.0f)
	{
		fMove *= 1.01f;
	}
	D3DXVec3Normalize(&move, &move);
	move *= fMove;
	SetEnemyMove(fMove);
	SetMove(move);

	m_BossPosOld[m_nCarrent] = this->GetPos();
	m_fBodyRot[m_nCarrent] = this->GetRot().z;
	m_nCarrent++;
	if (m_nCarrent >= MAX_BOSS_POS_OLD)
	{
		m_nCarrent = 0;
	}

	for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
	{
		int nCarrent = m_nCarrent - (BODY_FRAME_DISTANCE + BODY_FRAME_DISTANCE * nCnt);
		if (nCarrent < 0)
		{
			nCarrent = MAX_BOSS_POS_OLD + nCarrent;
		}

		m_pBossBody[nCnt]->SetPos(m_BossPosOld[nCarrent]);
		m_pBossBody[nCnt]->SetPolygon();
	}



}

//*****************************************************************************
// 敵の向きの変化
//*****************************************************************************
void CEnemyBoss02::EnemyRot()
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot;
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = atan2f(move.x, move.y);
	this->SetRot(rot);


	for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
	{
		int nCarrent = m_nCarrent - (BODY_FRAME_DISTANCE + BODY_FRAME_DISTANCE * nCnt);
		if (nCarrent < 0)
		{
			nCarrent = MAX_BOSS_POS_OLD + nCarrent;
		}

		rot.z = m_fBodyRot[nCarrent];
		m_pBossBody[nCnt]->SetRot(rot);
		m_pBossBody[nCnt]->SetPolygon();
	}

}

//*****************************************************************************
// 敵のエフェクト
//*****************************************************************************
void CEnemyBoss02::EnemyEffect()
{
}

//*****************************************************************************
// 頭単体の判定
//*****************************************************************************
bool CEnemyBoss02::EnemyBossHeadCollision(D3DXVECTOR3 pos, float radius)
{
	if (C2DPolygon::Collision(pos, radius))
	{
		m_nLife -= 4;
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
		if (m_nLife <= 0)
		{
			DiedEnemy();
			CCounter::AddCounter(3000);
			CCounter::AddCounter(m_nBossBodyMax * 100);
			CBulletManager::BreakBullet(BULLET_ENEMY);
		}
		return true;
	}
	return false;
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemyBoss02::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime < ENEMY_ATTACK_CNT)
	{
		return;
	}
	m_nBulletCoolTime = 0;

	Bullet bullet;
	bullet.fMove = 2.0f;
	bullet.fSize = 20.0f;
	bullet.nTextIndex = GetBulletText();
	bullet.Type = BULLET_ENEMY;
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PLpos = pPlayer->GetPos();
	D3DXVECTOR3 Epos;
	D3DXVECTOR3 vec;

	for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
	{
		if ((nCnt % 2) == m_nBossAttack)
		{
			continue;
		}

		Epos = m_pBossBody[nCnt]->GetPos();
		vec = PLpos - Epos;
		D3DXVec3Normalize(&vec, &vec);

		bullet.Vector = vec;
		bullet.pos = Epos;

		switch (m_nBossAttack)
		{
		case 0:
			CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 4, 30.0f);
			break;
		case 1:
			CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 12, 330.0f);
			break;
		default:
			break;
		}
		
	}


	m_nBossAttack = (1 - m_nBossAttack);


}
