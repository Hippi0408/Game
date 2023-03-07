//=============================================================================
//
// enemy05.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy05.h"
#include "bulletmanager.h"
#include "sound.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy05::CEnemy05()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy05::~CEnemy05()
{
}

//*****************************************************************************
// �G�̍U������
//*****************************************************************************
void CEnemy05::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime >= ENEMY_ATTACK_CNT)
	{
		m_nBulletCoolTime = 0;

		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = GetPos();
		bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = D3DXVECTOR3(0.0f,-1.0f,0.0f);

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 6, 300.0f);
	}
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemy05::IsUnused()
{
	if (m_nLife <= 0)
	{
		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = GetPos();
		bullet.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_02, 8, 315.0f, GetActualRadius() * 2.0f);
		return true;
	}
	return false;
}