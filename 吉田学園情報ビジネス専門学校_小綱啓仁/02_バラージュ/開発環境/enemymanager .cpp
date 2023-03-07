//=============================================================================
//
// enemy.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "enemymanager .h"
#include <assert.h>
#include "enemybase.h"
#include "enemy01.h"
#include "enemy02.h"
#include "enemy03.h"
#include "enemy04.h"
#include "enemy05.h"
#include "enemy06.h"
#include "enemyboss01.h"
#include "enemyboss02.h"
#include "enemyboss03.h"
#include "enemyboss04.h"
#include "enemyboss05.h"
#include "enemyboss06.h"

int CEnemyManager::m_nBulletTextIndex = -1;
CEnemyBase *CEnemyManager::m_pEnemy[ENEMY_MAX] = {};
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemyManager::CEnemyManager()
{
	//�G�l�~�[�̃e�N�X�`��
	ZeroMemory(&m_nEnemyTextIndex,sizeof(m_nEnemyTextIndex));

	//�G�l�~�[�O���[�v���
	m_nGroupNum = 0;				//���ݐ������̓G�O���[�v�̐�
	m_nGroupMax = 0;					//�o�^�G�O���[�v�̐�
	ZeroMemory(&m_GroupData, sizeof(m_GroupData));	//�O���[�v�̑S�f�[�^

	m_nEnemyMoveTypeMax = 0;		   //�G�l�~�[�̓o�^���������̐�
	//�G�l�~�[�̓����̌�
	ZeroMemory(&m_EnemyMoveType, sizeof(m_EnemyMoveType));

	//�Q�[����Ő����Ă���G�l�~�[�̐�
	m_nAliveEnemyCnt = 0;

	//�C���^�[�o��
	m_nInterval = 0;

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemyManager::~CEnemyManager()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemyManager::Init()
{
	CManager *pManager = GetManager();

	StageNum Stage = pManager->GetStage();

	//�Q�[���J�n���A�ŏ��̃O���[�v���o��܂ł̊�
	m_nInterval = FIRST_INTERVAL;

	m_nBulletTextIndex = CTexture::LoadTexture("data/TEXTURE/EnemyBullet.png");

	m_nEnemyTextIndex[0] = CTexture::LoadTexture("data/TEXTURE/enemy01.png");
	m_nEnemyTextIndex[1] = CTexture::LoadTexture("data/TEXTURE/enemy01.png");
	m_nEnemyTextIndex[2] = CTexture::LoadTexture("data/TEXTURE/enemy02.png");
	m_nEnemyTextIndex[3] = CTexture::LoadTexture("data/TEXTURE/enemy03.png");
	m_nEnemyTextIndex[4] = CTexture::LoadTexture("data/TEXTURE/enemy04.png");
	m_nEnemyTextIndex[5] = CTexture::LoadTexture("data/TEXTURE/enemy05.png");
	m_nEnemyTextIndex[6] = CTexture::LoadTexture("data/TEXTURE/enemy06.png");

	switch (Stage)
	{
	case StageNum_01:
		m_nEnemyTextIndex[7] = CTexture::LoadTexture("data/TEXTURE/boss01.png");
		break;
	case StageNum_02:
		m_nEnemyTextIndex[8] = CTexture::LoadTexture("data/TEXTURE/boss02.png");
		break;
	case StageNum_03:
		m_nEnemyTextIndex[9] = CTexture::LoadTexture("data/TEXTURE/boss03.png");
		break;
	case StageNum_04:
		m_nEnemyTextIndex[10] = CTexture::LoadTexture("data/TEXTURE/boss01.png");
		break;
	case StageNum_05:
		m_nEnemyTextIndex[11] = CTexture::LoadTexture("data/TEXTURE/boss02.png");
		break;
	case StageNum_06:
		m_nEnemyTextIndex[12] = CTexture::LoadTexture("data/TEXTURE/boss03.png");
		break;
	case StageNum_MAX:
	default:
		assert(false);
		break;
	}
	
	
	

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemyManager::Uninit()
{
	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{
		if (m_pEnemy[nCnt] != nullptr)
		{
			m_pEnemy[nCnt]->Uninit();
			delete m_pEnemy[nCnt];
			m_pEnemy[nCnt] = nullptr;
		}
	}

	//�O���[�v�̔j��
	for (int nCnt = 0; nCnt < ENEMY_GROUP_MAX; nCnt++)
	{
		if (m_GroupData[nCnt].pEnemyMoveType != nullptr)
		{
			delete[] m_GroupData[nCnt].pEnemyMoveType;
			m_GroupData[nCnt].pEnemyMoveType = nullptr;
		}

		if (m_GroupData[nCnt].pEnemyType != nullptr)
		{
			delete[] m_GroupData[nCnt].pEnemyType;
			m_GroupData[nCnt].pEnemyType = nullptr;
		}

		if (m_GroupData[nCnt].pAddPos != nullptr)
		{
			delete[] m_GroupData[nCnt].pAddPos;
			m_GroupData[nCnt].pAddPos = nullptr;
		}
	}

	//�G�l�~�[�̓����̔j��
	for (int nCnt = 0; nCnt < ENEMY_MOVE_SOURCE_MAX; nCnt++)
	{
		if (m_EnemyMoveType[nCnt].pAnchorPos != nullptr)
		{
			delete[] m_EnemyMoveType[nCnt].pAnchorPos;
			m_EnemyMoveType[nCnt].pAnchorPos = nullptr;
		}
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemyManager::Update()
{
	//�Q�[����Ő����Ă���G�l�~�[�̐��J�E���g��������
	m_nAliveEnemyCnt = 0;

	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{//�G�l�~�[�̍X�V
		if (m_pEnemy[nCnt] == nullptr)
		{
			continue;
		}
		m_pEnemy[nCnt]->Update();

		if (m_pEnemy[nCnt] == nullptr)
		{
			continue;
		}

		if (m_pEnemy[nCnt]->IsUnused())
		{//�I����������
			if (m_pEnemy[nCnt]->GetEnemyType() >= BOSS_01 
				&& m_pEnemy[nCnt]->EnemyBossEffect())
			{
				CManager *pManager = GetManager();
				CGame * pGame = (CGame*)pManager->GetGameObject();
				pGame->BossDied();
			}

			if (m_pEnemy[nCnt] != nullptr)
			{
				m_pEnemy[nCnt]->Uninit();
				delete m_pEnemy[nCnt];
				m_pEnemy[nCnt] = nullptr;
			}
			continue;
		}

		//�Q�[����Ő����Ă���G�l�~�[�̐��J�E���g
		m_nAliveEnemyCnt++;
	}

	if (m_nInterval > 0)
	{//�C���^�[�o�������鎞�A����IF��艺�̏������X�L�b�v
		m_nInterval--;
		return;
	}

	if (m_nAliveEnemyCnt > 0)
	{//�����Ă���G�l�~�[�����鎞�A����IF��艺�̏������X�L�b�v
		return;
	}

	if (m_nGroupNum > m_nGroupMax)
	{
		return;
	}


	//�G�l�~�[�̐���
	for (int nCnt = 0; nCnt < m_GroupData[m_nGroupNum].nEnemyMax; nCnt++)
	{
		if (m_pEnemy[nCnt] != nullptr)
		{
			assert(false);
		}

		//�C���X�^���̐���
		CreateEnemy(nCnt, m_GroupData[m_nGroupNum].pEnemyMoveType[nCnt], m_GroupData[m_nGroupNum].pEnemyType[nCnt], m_GroupData[m_nGroupNum].pAddPos[nCnt]);
	}

	//���݂̃O���[�v�ɃC���N�������g
	m_nGroupNum++;
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemyManager::Draw()
{
	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{
		if (m_pEnemy[nCnt] != nullptr)
		{
			m_pEnemy[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// �G�l�~�[�̐���
//*****************************************************************************
void CEnemyManager::CreateEnemy(int nNum, int nMoveType, EnemyType type, D3DXVECTOR3 addpos)
{
	if (m_pEnemy[nNum] != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	CManager *pManager = GetManager();
	CGame *pGame = (CGame*)pManager->GetGameObject();

	//�C���X�^���̐���
	switch (type)
	{
	case ENEMY_BASE:
		m_pEnemy[nNum] = new CEnemyBase;
		break;
	case ENEMY_01:
		m_pEnemy[nNum] = new CEnemy01;
		break;
	case ENEMY_02:
		m_pEnemy[nNum] = new CEnemy02;
		break;
	case ENEMY_03:
		m_pEnemy[nNum] = new CEnemy03;
		break;
	case ENEMY_04:
		m_pEnemy[nNum] = new CEnemy04;
		break;
	case ENEMY_05:
		m_pEnemy[nNum] = new CEnemy05;
		break;
	case ENEMY_06:
		m_pEnemy[nNum] = new CEnemy06;
		break;
	case BOSS_01:
		m_pEnemy[nNum] = new CEnemyBoss01;
		pGame->SetWarning();
		break;
	case BOSS_02:
		m_pEnemy[nNum] = new CEnemyBoss02;
		pGame->SetWarning();
		break;
	case BOSS_03:
		m_pEnemy[nNum] = new CEnemyBoss03;
		pGame->SetWarning();
		break;
	case BOSS_04:
		m_pEnemy[nNum] = new CEnemyBoss04;
		pGame->SetWarning();
		break;
	case BOSS_05:
		m_pEnemy[nNum] = new CEnemyBoss05;
		pGame->SetWarning();
		break;
	case BOSS_06:
		m_pEnemy[nNum] = new CEnemyBoss06;
		pGame->SetWarning();
		break;
	case MAX_TYPE:
	default:
		assert(false);
		break;
	}

	//������
	if (FAILED(m_pEnemy[nNum]->Init()))
	{
		assert(false);
	}


	//�e�N�X�`���ԍ��ݒ�
	m_pEnemy[nNum]->SetTextIndex(m_nEnemyTextIndex[type]);
	//�A���J�[�|�C���g���̐ݒ�
	m_pEnemy[nNum]->SetEnemyData(m_EnemyMoveType[nMoveType]);
	//�G�l�~�[�̃^�C�v�̐ݒ�
	m_pEnemy[nNum]->SetEnemyType(type);
	//�G�l�~�[�̃o���b�g�̐ݒ�
	m_pEnemy[nNum]->SetBulletText(m_nBulletTextIndex);

	//����POS�Z�b�g
	m_pEnemy[nNum]->SetEnemyAddPos(addpos);
	m_pEnemy[nNum]->SetPos(m_EnemyMoveType[nMoveType].pAnchorPos[0] + addpos);
	m_pEnemy[nNum]->SetPolygon();
	m_pEnemy[nNum]->CalculatingUpToNextMovePoint();

	//ID�o�^
	m_pEnemy[nNum]->SetID(nNum);
}

//*****************************************************************************
// �����蔻��
//*****************************************************************************
bool CEnemyManager::Collision(D3DXVECTOR3 pos, float radius)
{
	for (int nCnt = 0;nCnt < ENEMY_MAX;nCnt++)
	{
		if (m_pEnemy[nCnt] == nullptr)
		{
			continue;
		}

		if (m_pEnemy[nCnt]->GetDied())
		{
			continue;
		}

		if (m_pEnemy[nCnt]->Collision(pos, radius))
		{
			return true;
		}
	}

	return false;
}

//*****************************************************************************
// �G�l�~�[�̓����̌��{�o�^
//*****************************************************************************
void CEnemyManager::SetEnemyMoveType(int nPosNumMax, D3DXVECTOR3 * pAnchorPos)
{
	if (m_nEnemyMoveTypeMax > ENEMY_MOVE_SOURCE_MAX)
	{
		assert(false);
	}

	if (m_EnemyMoveType[m_nEnemyMoveTypeMax].pAnchorPos != nullptr)
	{
		assert(false);
	}

	//pos�|�C���^�̊m��
	m_EnemyMoveType[m_nEnemyMoveTypeMax].pAnchorPos = new D3DXVECTOR3[nPosNumMax];
	//���ꂩ��o�^����POS�̐�
	m_EnemyMoveType[m_nEnemyMoveTypeMax].nPosNumMax = nPosNumMax;

	for (int nCnt = 0; nCnt < nPosNumMax; nCnt++)
	{
		m_EnemyMoveType[m_nEnemyMoveTypeMax].pAnchorPos[nCnt] = pAnchorPos[nCnt];
	}

	m_nEnemyMoveTypeMax++;
}

//*****************************************************************************
// �G�l�~�[�O���[�v�̓o�^
//*****************************************************************************
void CEnemyManager::SetGroupData(int nEnemyMax, int * pEnemyMove ,int * pEnemyType , D3DXVECTOR3 *pInitPos)
{
	if (m_nGroupMax > ENEMY_GROUP_MAX)
	{
		assert(false);
	}

	if (m_GroupData[m_nGroupMax].pEnemyMoveType != nullptr)
	{
		assert(false);
	}

	//int�|�C���^�̊m��
	m_GroupData[m_nGroupMax].pEnemyMoveType = new int[nEnemyMax];
	m_GroupData[m_nGroupMax].pEnemyType = new EnemyType[nEnemyMax];
	m_GroupData[m_nGroupMax].pAddPos = new D3DXVECTOR3[nEnemyMax];

	//���ꂩ��o�^����G�l�~�[�̐�
	m_GroupData[m_nGroupMax].nEnemyMax = nEnemyMax;

	for (int nCnt = 0; nCnt < nEnemyMax; nCnt++)
	{
		m_GroupData[m_nGroupMax].pEnemyMoveType[nCnt] = pEnemyMove[nCnt];
		m_GroupData[m_nGroupMax].pEnemyType[nCnt] = (EnemyType)pEnemyType[nCnt];
		m_GroupData[m_nGroupMax].pAddPos[nCnt] = pInitPos[nCnt] - m_EnemyMoveType[pEnemyMove[nCnt]].pAnchorPos[0];
	}

	m_nGroupMax++;
}

//*****************************************************************************
// �G�l�~�[��ID�w��ł̔j��
//*****************************************************************************
void CEnemyManager::UninitEnemyId(const int nId)
{
	if (m_pEnemy[nId] != nullptr)
	{
		m_pEnemy[nId]->Uninit();
		delete m_pEnemy[nId];
		m_pEnemy[nId] = nullptr;
	}
}
