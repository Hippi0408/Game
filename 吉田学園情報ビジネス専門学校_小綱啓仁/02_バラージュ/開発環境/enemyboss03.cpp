//=============================================================================
//
// enemy03.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemyboss03.h"
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

const float CEnemyBoss03::ENEMY_BOSS03_SIZE = 100.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemyBoss03::CEnemyBoss03()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemyBoss03::~CEnemyBoss03()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemyBoss03::Init()
{
	srand((unsigned)time(NULL)); // ���ݎ����̏��ŏ�����
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	m_nBossAttack = 0;
	SetEnemyMove(1.0f);
	SetDiagonalLine(ENEMY_BOSS03_SIZE, ENEMY_BOSS03_SIZE);//�\������|���S���̏c�����ݒ�
	SetPolygon();

	m_nSpecialBulletTex = CTexture::LoadTexture("data/TEXTURE/bulletspecial01.png");

	return S_OK;
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemyBoss03::IsUnused()
{
	if (m_nLife <= 0)
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT, 180);
		return true;
	}
	return false;
}

//*****************************************************************************
// �����蔻��
//*****************************************************************************
bool CEnemyBoss03::Collision(D3DXVECTOR3 pos, float radius)
{
	if (C2DPolygon::Collision(pos, radius))
	{
		m_nLife -= 1;
		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
		if (m_nLife <= 0)
		{
			DiedEnemy();
			int nScore = CBulletManager::BreakBullet(BULLET_ENEMY) * 100;
			CCounter::AddCounter(3000 + nScore);
		}
		return true;
	}
	return false;
}

//*****************************************************************************
// �G�̈ړ�
//*****************************************************************************
void CEnemyBoss03::EnemyMove()
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
// �G�̃G�t�F�N�g
//*****************************************************************************
void CEnemyBoss03::EnemyEffect()
{
	CEffect::Effect effect;
	D3DXVECTOR3 move = GetMove();
	D3DXVec3Normalize(&move, &move);
	move *= -5.0f;
	float fSize = ENEMY_BOSS03_SIZE / 2.0f;
	effect.fAttenuation = -0.05f;
	effect.fSizeX = fSize;
	effect.fSizeY = fSize;
	effect.nLife = 20;
	effect.fScaleDown = -2.0f;
	effect.nTextIndex = 0;
	effect.pos = GetPos();
	effect.pos.y -= 20.0f;
	effect.Color = D3DXCOLOR(0.6f, 0.3f, 0.3f, 1.0f);
	effect.move = move;
	effect.bAddColor = true;

	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
}

//*****************************************************************************
// �G�̍U������
//*****************************************************************************
void CEnemyBoss03::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime % 20 == 0)
	{
	
		D3DXVECTOR3 pos;
		pos.x = (SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f) + rand() % SCREEN_GAME_WIDTH;
		pos.y = SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f;
		pos.z = 0.0f;
		Bullet bullet;
		bullet.fMove = 2.0f;
		bullet.fSize = 100.0f;
		bullet.nTextIndex = m_nSpecialBulletTex;
		bullet.pos = pos;
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = D3DXVECTOR3(0.0f,1.0f,0.0f);

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_SPECIAL_01, 1);
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

	Bullet bullet;
	bullet.fMove = 2.0f;
	bullet.fSize = 50.0f;
	bullet.nTextIndex = GetBulletText();
	bullet.pos = GetPos();
	bullet.Type = BULLET_ENEMY;
	bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	bullet.Vector = D3DXVECTOR3(0.0f,-1.0f,0.0f);

	CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 12, 330.0f);
}
