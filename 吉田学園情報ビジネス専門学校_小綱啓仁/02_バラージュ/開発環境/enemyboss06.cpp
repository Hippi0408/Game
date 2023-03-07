//=============================================================================
//
// enemyboss06.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemyboss06.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"
#include "counter.h"
#include "manager.h"
#include <assert.h>
#include "sound.h"
#include "texture.h"
#include <time.h>
#include "effect.h"

const float CEnemyBoss06::ENEMY_BOSS06_SIZE = 100.0f;
int CEnemyBoss06::m_nBossNum = 0;
int CEnemyBoss06::m_nBossDiedCnt = 0;
int CEnemyBoss06::m_nAttackChange = 0;
int CEnemyBoss06::m_nBossIdMax = 0;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemyBoss06::CEnemyBoss06()
{
	m_nBossNum = 2;
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemyBoss06::~CEnemyBoss06()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemyBoss06::Init()
{
	srand((unsigned)time(NULL)); // 現在時刻の情報で初期化
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	m_nBossAttack = 0;
	SetEnemyMove(1.0f);
	SetDiagonalLine(ENEMY_BOSS06_SIZE, ENEMY_BOSS06_SIZE);//表示するポリゴンの縦横幅設定
	SetPolygon();
	m_nID = m_nBossIdMax;
	m_nBossIdMax++;
	m_nSpecialBulletTex = CTexture::LoadTexture("data/TEXTURE/bulletspecial01.png");

	return S_OK;
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemyBoss06::IsUnused()
{
	if (m_nBossNum <= 1)
	{
		m_nBossDiedCnt++;
	}

	if (m_nLife <= 0)
	{
		m_nBossNum--;
		if (m_nBossNum <= 0)
		{
			if (BOSS_DIEDCNT > m_nBossDiedCnt)
			{
				CCounter::AddCounter(3000);
			}
			CManager * pManager = GetManager();
			pManager->NextMode(TYPE_RESULT, 180);
			CBulletManager::BreakBullet(BULLET_ENEMY);
		}
		return true;
	}
	return false;
	return false;
}

//*****************************************************************************
// ボスの死亡のエフェクト
//*****************************************************************************
bool CEnemyBoss06::EnemyBossEffect()
{
	if (m_nBossNum <= 0)
	{
		return true;
	}
	return false;
}

//*****************************************************************************
// 当たり判定
//*****************************************************************************
bool CEnemyBoss06::Collision(D3DXVECTOR3 pos, float radius)
{
	if (C2DPolygon::Collision(pos, radius))
	{
		m_nLife -= 1;
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
		if (m_nLife <= 0)
		{
			DiedEnemy();
			CCounter::AddCounter(3000);
		}
		return true;
	}
	return false;
}

//*****************************************************************************
// 敵の移動
//*****************************************************************************
void CEnemyBoss06::EnemyMove()
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
}

//*****************************************************************************
// 敵のエフェクト
//*****************************************************************************
void CEnemyBoss06::EnemyEffect()
{
	CEffect::Effect effect;
	D3DXVECTOR3 move = GetMove();
	D3DXVec3Normalize(&move, &move);
	move *= -5.0f;
	float fSize = ENEMY_BOSS06_SIZE / 2.0f;
	effect.fAttenuation = -0.05f;
	effect.fSizeX = fSize;
	effect.fSizeY = fSize;
	effect.nLife = 20;
	effect.fScaleDown = -2.0f;
	effect.nTextIndex = 0;
	effect.pos = GetPos();
	switch (m_nID)
	{
	case 0:
		effect.pos.y -= 20.0f;
		break;
	case 1:
		effect.pos.y += 20.0f;
		break;
	default:
		break;
	}
	
	effect.Color = D3DXCOLOR(0.6f, 0.3f, 0.3f, 1.0f);
	effect.move = move;
	effect.bAddColor = true;

	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemyBoss06::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime % 20 == 0)
	{

		D3DXVECTOR3 pos;
		Bullet bullet;
		pos.x = (SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f) + rand() % SCREEN_GAME_WIDTH;
		switch (m_nAttackChange)
		{
		case 0:
			pos.y = SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f;
			bullet.Vector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			break;
		case 1:
			pos.y = SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f;
			bullet.Vector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			break;
		default:
			break;
		}
		
		pos.z = 0.0f;
		bullet.fMove = 2.0f;
		bullet.fSize = 50.0f;
		bullet.nTextIndex = m_nSpecialBulletTex;
		bullet.pos = pos;
		bullet.Type = BULLET_ENEMY;

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_SPECIAL_02, 1);

		m_nAttackChange = 1 - m_nAttackChange;
	}

	if (m_nBulletCoolTime < ENEMY_ATTACK_CNT)
	{
		return;
	}

	m_nBulletCoolTime = 0;

	D3DXVECTOR3 pos = GetPos();
	if (pos.y < SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f)
	{
		return;
	}
	if (pos.y > SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f)
	{
		return;
	}

	if (pos.x < SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f)
	{
		return;
	}
	if (pos.x > SCREEN_WIDTH * 0.5f + SCREEN_GAME_WIDTH * 0.5f)
	{
		return;
	}

	D3DXVECTOR3 Epos = GetPos();
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 PLpos = pPlayer->GetPos();

	D3DXVECTOR3 vec = PLpos - Epos;

	D3DXVec3Normalize(&vec, &vec);

	Bullet bullet;
	bullet.fMove = 2.0f;
	bullet.fSize = 20.0f;
	bullet.nTextIndex = GetBulletText();
	bullet.pos = GetPos();
	bullet.Type = BULLET_ENEMY;
	bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	bullet.Vector = vec;

	CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 12, 330.0f);
}
