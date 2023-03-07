//=============================================================================
//
// enemy01.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy01.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"

const float CEnemy01::ENEMY_01_SIZE = 50.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy01::CEnemy01()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy01::~CEnemy01()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemy01::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	SetEnemyMove(0.7f);
	SetDiagonalLine(ENEMY_01_SIZE, ENEMY_01_SIZE);//�\������|���S���̏c�����ݒ�
	SetPolygon();

	return S_OK;
}

//*****************************************************************************
// �G�̈ړ�
//*****************************************************************************
void CEnemy01::EnemyMove()
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
// �G�̍U������
//*****************************************************************************
void CEnemy01::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime >= ENEMY_ATTACK_CNT)
	{
		m_nBulletCoolTime = 0;

		CPlayer *pPlayer = CGame::GetPlayer();

		D3DXVECTOR3 PLpos = pPlayer->GetPos();

		D3DXVECTOR3 Epos = GetPos();

		D3DXVECTOR3 vec = PLpos - Epos;

		D3DXVec3Normalize(&vec, &vec);
		
		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = Epos;
		bullet.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = vec;
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01,3,5.0f);
	}
}
