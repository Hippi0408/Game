//=============================================================================
//
// Bullet.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
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


// �|���S���̕�
const float CBulletManager::SIZE_BULLET = 16.0f;
// ���̎ˌ��̍ő�p�x
const float CBulletManager::BULLET_ANGLE= 20.0f;
// �o���b�g�̏��
CBulletBase *CBulletManager::m_pBullet[BULLET_MAX] = {};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBulletManager::CBulletManager()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBulletManager::~CBulletManager()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CBulletManager::Init()
{
	ZeroMemory(m_pBullet, sizeof(m_pBullet));
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBulletManager::Uninit()
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] != nullptr)
		{
			// �I������
			m_pBullet[nCnt]->Uninit();
			delete m_pBullet[nCnt];
			m_pBullet[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBulletManager::Update()
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] == nullptr)
		{
			continue;
		}
		// �X�V����
		m_pBullet[nCnt]->Update();
		if (m_pBullet[nCnt]->IsUnused())
		{
			// �I������
			m_pBullet[nCnt]->Uninit();
			delete m_pBullet[nCnt];
			m_pBullet[nCnt] = nullptr;
		}

	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBulletManager::Draw()
{
	for (int nCnt = 0; nCnt < BULLET_MAX; nCnt++)
	{
		if (m_pBullet[nCnt] != nullptr)
		{
			// �`�揈��
			m_pBullet[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// �e�̔��ˏ���
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
// �e�̔��ˏ���(�܂Ƃ߂�)
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
// �e�̔j���i�^�C�v�w��j
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

		// �I������
		m_pBullet[nCnt]->Uninit();
		delete m_pBullet[nCnt];
		m_pBullet[nCnt] = nullptr;
		nBulletCnt++;
	}

	return nBulletCnt;
}

//*****************************************************************************
// �e�̓����蔻��i�^�C�v�w��j
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
			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
			// �I������
			m_pBullet[nCnt]->Uninit();
			delete m_pBullet[nCnt];
			m_pBullet[nCnt] = nullptr;
			return true;
		}
	}
	return false;
}

//*****************************************************************************
// �e�̃N���G�C�g����
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