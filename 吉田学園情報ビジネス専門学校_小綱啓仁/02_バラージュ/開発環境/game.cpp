//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "player.h"
#include "main.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "2dpolygon.h"
#include "texture.h"
#include "enemymanager .h"
#include "bulletmanager.h"
#include "anim.h"
#include "explosion.h"
#include "counter.h"
#include "time.h"
#include "read.h"
#include "gauge.h"
#include "counter.h"
#include "camera.h"
#include "3dobject.h"
#include "light.h"
#include "game3dbg.h"
#include "effect.h"
#include "pause.h"
#include "warning.h"
#include "sound.h"

CPlayer *CGame::m_pPlayer = nullptr;
CEnemyManager *CGame::m_pEnemyManager = nullptr;
CBulletManager *CGame::m_pBulletManager = nullptr;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pEnemyManager = nullptr;
	m_pBulletManager = nullptr;
	m_pRead = nullptr;
	m_pCamera = nullptr;
	m_pBGObj = nullptr;
	m_pLight = nullptr;
	m_pPause = nullptr;
	m_nWarningCnt = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CGame::Init()
{
	m_bBossDied = false;
	
	CEffect::ALLInit();

	m_pUi = nullptr;

	m_pUi = new CUI;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pUi->CreateUi(5);

	int nIndex = CTexture::LoadTexture("data/TEXTURE/gameui01.png");
	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[0].SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/gameui02.png");
	pPolygon[1].SetTextIndex(nIndex);
	pPolygon[1].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[1].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[1].SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/gameui03.png");
	pPolygon[2].SetTextIndex(nIndex);
	pPolygon[2].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[2].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[2].SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	pPolygon[2].SetPolygon();

	pPolygon[3].SetTextIndex(0);
	pPolygon[3].SetPos(D3DXVECTOR3(225.0f, 170.0f, 0.0f));
	pPolygon[3].SetDiagonalLine(350.0f, 25.0f);
	pPolygon[3].SetColor(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	pPolygon[3].SetPolygon();

	pPolygon[4].SetTextIndex(0);
	pPolygon[4].SetPos(D3DXVECTOR3(225.0f, 195.0f, 0.0f));
	pPolygon[4].SetDiagonalLine(350.0f, 15.0f);
	pPolygon[4].SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	pPolygon[4].SetPolygon();

	m_pPlayer = nullptr;

	m_pPlayer = new CPlayer;

	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}

	m_pEnemyManager = new CEnemyManager;

	if (FAILED(m_pEnemyManager->Init()))
	{
		return -1;
	}

	m_pBulletManager = new CBulletManager;

	if (FAILED(m_pBulletManager->Init()))
	{
		return -1;
	}

	m_pRead = new CRead;

	m_pRead->ReadAnchorPoint();

	CManager * pManager = GetManager();
	StageNum Stage = pManager->GetStage();
	m_pRead->ReadEnemy(Stage);
	ModelTxt modeltxt = ModelTxtMax;

	switch (Stage)
	{
	case StageNum_01:
		modeltxt = GameStage01;
		break;
	case StageNum_02:
		modeltxt = GameStage02;
		break;
	case StageNum_03:
		modeltxt = GameStage03;
		break;
	case StageNum_04:
		modeltxt = GameStage04;
		break;
	case StageNum_05:
		modeltxt = GameStage05;
		break;
	case StageNum_06:
		modeltxt = GameStage06;
		break;
	default:
		break;
	}
	m_pRead->ReadModel(modeltxt);

	//�T�E���h��~
	StopSound();
	//�T�E���h�Đ�
	PlaySound((SOUND_LABEL)Stage);

	CAnim::ALLInit();

	CExplosion::Init();

	D3DXVECTOR3 Pos = D3DXVECTOR3(240.0f, 600.0f, 0.0f);
	int nDigit = 3;
	int nNumerical = 120;
	int nTime = 120;
	float fSize = 160.0f;
	if (FAILED(CTime::Init(Pos, nDigit, nNumerical, nTime, fSize)))
	{
		return -1;
	}

	//�X�R�A
	Pos = D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 400.0f, 0.0f);
	nDigit = 8;
	nNumerical = 0;
	fSize = 100.0f;
	CCounter *Counter = CCounter::Create(); 
	if (FAILED(Counter->Init(Pos, nDigit,fSize, nNumerical)))
	{
		return -1;
	}

	//�J����
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 70.0f, -100.0f));

	//���C�g
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pBGObj = new CGame3DBG;
	if (FAILED(m_pBGObj->Init()))
	{
		return -1;
	}

	//�|�[�Y
	m_pPause = new CPause;
	if (FAILED(m_pPause->Init()))
	{
		return -1;
	}

	m_pWarning = new CWarning;
	if (FAILED(m_pWarning->Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CGame::Uninit()
{
	CManager *pManager = GetManager();
	int nScore = CCounter::GetCounter();
	pManager->SetScore(nScore);

	CCounter::AllUninit();
	CTime::Uninit();
	CEffect::ALLUninit();
	CExplosion::Uninit();
	CAnim::ALLUninit();
	CGauge::AllUninit();

	//UI
	if (m_pUi != nullptr)
	{
		// �I������
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}

	if (m_pWarning != nullptr)
	{
		// �I������
		m_pWarning->Uninit();
		delete m_pWarning;
		m_pWarning = nullptr;
	}

	//�|�[�Y���
	if (m_pPause != nullptr)
	{
		// �I������
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	//�v���C���[
	if (m_pPlayer != nullptr)
	{
		// �I������
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	//�G�l�~�[�}�l�[�W���[
	if (m_pEnemyManager != nullptr)
	{
		// �I������
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	//�o���b�g�}�l�[�W���[
	if (m_pBulletManager != nullptr)
	{
		// �I������
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = nullptr;
	}

	//�J����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//�O���t�@�C��
	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

	//3DBG
	if (m_pBGObj != nullptr)
	{
		m_pBGObj->Uninit();
		delete m_pBGObj;
		m_pBGObj = nullptr;
	}
	C3DObject::UninitAllModel();

	//���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CGame::Update()
{

	CManager * pManager = GetManager();

	CInput *pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_PAUSE) && !pManager->IsChangingMode())
	{//�|�[�Y��ʂւ̐؂�ւ�
		if (m_pPause->GetPause())
		{
			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_BACK);
			m_pPause->SetPause(false);
		}
		else
		{
			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_DETERMINATION);
			m_pPause->SetPause(true);
		}
	}

	if (m_pPause->GetPause())
	{
		m_pPause->Update();
		return;
	}

	m_pBGObj->Update();
	
	if (!m_pWarning->GetWarning())
	{
		m_pEnemyManager->Update();
	}
	else
	{
		m_nWarningCnt++;
		m_pWarning->Update();
	}

	if (m_nWarningCnt > WARNING_CNT_MAX)
	{
		if (m_pWarning->OutWarning())
		{
			m_nWarningCnt = 0;
		}
	}

	m_pUi->Update();

	m_pPlayer->Update();

	CTime::Update(TYPE_RESULT);

	m_pBulletManager->Update();

	CEffect::ALLUpdate();

	CAnim::ALLUpdate();

	if (m_bBossDied)
	{
		CExplosion::BossDiedExplosion();
	}

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CGame::Draw()
{
	//�J����
	m_pCamera->SetCamera();
	//�w�i
	m_pBGObj->Draw();
	//�G�t�F�N�g
	CEffect::ALLDraw();
	//�G�l�~�[�}�l�[�W���[
	m_pEnemyManager->Draw();
	//�v���C���[
	m_pPlayer->Draw();
	//�o���b�g
	m_pBulletManager->Draw();
	//�A�j���[�V����
	CAnim::ALLDraw();
	//���[�j���O�\��
	m_pWarning->Draw();
	//�t�h
	m_pUi->Draw();
	//�J�E���^�[
	CCounter::AllDraw();
	//�^�C��
	CTime::Draw();
	//�Q�[�W
	CGauge::AllDraw();

	//�|�[�Y�̕`��
	if (m_pPause->GetPause())
	{
		m_pPause->Draw();
	}
}

//*****************************************************************************
// ���[�j���O�\��
//*****************************************************************************
void CGame::SetWarning()
{
	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_SE_WARNING);
	m_pWarning->SetWarning();
	CBulletManager::BreakBullet(BULLET_ENEMY);
}
