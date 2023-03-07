//=============================================================================
//
// enemybase.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemybase.h"
#include "texture.h"
#include "enemymanager .h"
#include "game.h"
#include "player.h"
#include "enemydata.h"
#include <assert.h>
#include "counter.h"
#include "bulletmanager.h"
#include "effect.h"
#include "sound.h"

const float CEnemyBase::ENEMY_BASE_SIZE = 30.0f;
const float CEnemyBase::ENEMY_BASE_MOVE = 5.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemyBase::CEnemyBase()
{
	ZeroMemory(&m_AnchorData, sizeof(m_AnchorData));
	m_nBulletCoolTime = 0;
	m_nLife = 0;
	m_nBulletTextIndex = 0;
	m_AddPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0;
	m_bDied = false;
	m_EnemyType = ENEMY_BASE;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemyBase::~CEnemyBase()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemyBase::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	m_bDied = false;
	m_fMove = ENEMY_BASE_MOVE;
	SetDiagonalLine(ENEMY_BASE_SIZE, ENEMY_BASE_SIZE);//�\������|���S���̏c�����ݒ�
	SetPolygon();
	
	
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemyBase::Uninit()
{
	C2DPolygon::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemyBase::Update()
{
	//�U������
	EnemyAttack();
	//�ړ�����
	EnemyMove();
	//ROT�̕ύX
	EnemyRot();
	
	C2DPolygon::Update();

	if (m_nLife > 0)
	{//�G�t�F�N�g
		EnemyEffect();
	}

	if (C2DPolygon::Collision(m_AnchorData.pAnchorPos[m_AnchorData.nUseNumPos] + m_AddPos, 0.0f))
	{
		if (CalculatingUpToNextMovePoint())
		{
			CEnemyManager::UninitEnemyId(m_nId);
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemyBase::Draw()
{
	C2DPolygon::Draw();
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemyBase::IsUnused()
{
	if (m_nLife <= 0)
	{
		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		return true;
	}
	return false;
}

//*****************************************************************************
// �G�̈ړ�
//*****************************************************************************
void CEnemyBase::EnemyMove()
{
}

//*****************************************************************************
// �G�̌����̕ω�
//*****************************************************************************
void CEnemyBase::EnemyRot()
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot;
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = atan2f(move.x, move.y);

	SetRot(rot);
}

//*****************************************************************************
// �G�̃G�t�F�N�g
//*****************************************************************************
void CEnemyBase::EnemyEffect()
{
	CEffect::Effect effect;
	effect.fAttenuation = -0.2f;
	effect.fSizeX = 25.0f;
	effect.fSizeY = 30.0f;
	effect.nLife = 7;
	effect.fScaleDown = -3.0f;
	effect.nTextIndex = 0;
	effect.pos = GetPos();
	effect.Color = D3DXCOLOR(0.6f, 0.3f, 0.3f, 1.0f);

	effect.move = GetMove();
	D3DXVec3Normalize(&effect.move, &effect.move);
	effect.move *= -5.0f;

	effect.bAddColor = true;

	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
}

//*****************************************************************************
// �G�̍U������
//*****************************************************************************
void CEnemyBase::EnemyAttack()
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
		bullet.fMove = 5.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = m_nBulletTextIndex;
		bullet.pos = Epos;
		bullet.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = vec;
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_00);
	}
}
//-----------------------------------------------------------------------------
//���̂̈ړ��_�܂ł̌v�Z
//-----------------------------------------------------------------------------
bool CEnemyBase::CalculatingUpToNextMovePoint(void)
{
	m_AnchorData.nUseNumPos++;

	if (m_AnchorData.nUseNumPos >= m_AnchorData.nPosNumMax)
	{
		switch (m_EnemyType)
		{
		case ENEMY_BASE:
		case ENEMY_01:
		case ENEMY_02:
		case ENEMY_03:
		case ENEMY_04:
		case ENEMY_05:
		case ENEMY_06:
			return true;
			break;
		case BOSS_01:
		case BOSS_02:
		case BOSS_03:
		case BOSS_04:
		case BOSS_05:
		case BOSS_06:
			m_AnchorData.nUseNumPos = 0;
			break;
		case MAX_TYPE:
		default:
			assert(false);
			break;
		}
	}

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 vec;
	D3DXVECTOR3 move;
	vec = (m_AnchorData.pAnchorPos[m_AnchorData.nUseNumPos] + m_AddPos) - pos;

	D3DXVec3Normalize(&move, &vec);

	move *= m_fMove;

	SetMove(move);

	return false;
}

//*****************************************************************************
// �G�l�~�[�̃^�C�v�Z�b�g
//*****************************************************************************
void CEnemyBase::SetEnemyType(EnemyType Type)
{
	m_EnemyType = Type;
	switch (Type)
	{
	case ENEMY_BASE:
	case ENEMY_01:
	case ENEMY_02:
	case ENEMY_03:
	case ENEMY_04:
	case ENEMY_05:
	case ENEMY_06:
		m_nLife = 5;
		break;
	case BOSS_01:
		m_nLife = 600;
		break;
	case BOSS_02:
	case BOSS_03:
	case BOSS_04:
		m_nLife = 300;
		break;
	case BOSS_05:
		m_nLife = 200;
		break;
	case BOSS_06:
		m_nLife = 150;
		break;
	case MAX_TYPE:
	default:
		assert(false);
		break;
	}

}

//*****************************************************************************
// �����蔻��
//*****************************************************************************
bool CEnemyBase::Collision(D3DXVECTOR3 pos, float radius)
{
	if (C2DPolygon::Collision(pos, radius))
	{
		m_nLife -= 1;
		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
		if (m_nLife <= 0)
		{
			m_bDied = true;
			CCounter::AddCounter(100);
		}
		return true;
	}
	return false;
}