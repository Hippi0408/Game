//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "result.h"
#include "2dpolygon.h"
#include "texture.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "counter.h"
#include "ranking.h"
#include "read.h"
#include "rankinginput.h"
#include "camera.h"
#include "result3dbg.h"
#include "light.h"
#include "sound.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CResult::CResult()
{
	m_pResultPolygon = nullptr;
	m_pRanking = nullptr;
	m_pRead = nullptr;
	m_pRankingInput = nullptr;
	m_pBGObj = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CResult::Init()
{
	m_bEnd = false;

	m_pResultPolygon = nullptr;

	m_pResultPolygon = new CUI;

	if (FAILED(m_pResultPolygon->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pResultPolygon->CreateUi(1);

	int nIndex = CTexture::LoadTexture("data/TEXTURE/�X�R�A.png");
	pPolygon->SetTextIndex(nIndex);
	pPolygon->SetPos(D3DXVECTOR3(310.0f, 250.0f, 0.0f));
	pPolygon->SetDiagonalLine(300.0f, 300.0f);
	pPolygon->SetPolygon();

	//�X�R�A
	CManager *pManager = GetManager();
	int nScore = pManager->GetScore();

	D3DXVECTOR3 Pos = D3DXVECTOR3(550.0f, 450.0f, 0.0f);
	int nDigit = 8;
	int nNumerical = nScore;
	float fSize = 120.0f;
	CCounter *Counter = CCounter::Create();
	if (FAILED(Counter->Init(Pos, nDigit, fSize, nNumerical)))
	{
		return -1;
	}

	Pos = D3DXVECTOR3(1400.0f, -1400.0f, 0.0f);
	m_pRanking = new CRanking;
	m_pRanking->Init(Pos);

	m_pRead = new CRead;
	m_pRead->ReadRanking(pManager->GetStage(), m_pRanking);

	m_pRankingInput = nullptr;

	m_pRankingInput = new CRankingInput;
	Pos = D3DXVECTOR3(200.0f, 700.0f, 0.0f);

	if (FAILED(m_pRankingInput->Init(Pos)))
	{
		return -1;
	}

	//�J����
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 0.0f, -300.0f));

	//���C�g
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pBGObj = new CResult3DBG;
	if (FAILED(m_pBGObj->Init()))
	{
		return -1;
	}

	//�T�E���h��~
	StopSound();
	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM_RESULT);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CResult::Uninit()
{
	CCounter::AllUninit();
	if (m_pResultPolygon != nullptr)
	{
		// �I������
		m_pResultPolygon->Uninit();
		delete m_pResultPolygon;
		m_pResultPolygon = nullptr;
	}

	if (m_pRanking != nullptr)
	{
		// �I������
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = nullptr;
	}

	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

	if (m_pRankingInput != nullptr)
	{
		m_pRankingInput->Uninit();
		delete m_pRankingInput;
		m_pRankingInput = nullptr;
	}

	//�J����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//3DBG
	if (m_pBGObj != nullptr)
	{
		m_pBGObj->Uninit();
		delete m_pBGObj;
		m_pBGObj = nullptr;
	}

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
void CResult::Update()
{
	m_pResultPolygon->Update();

	m_pRanking->Update();

	//3DBG
	if (m_pBGObj != nullptr)
	{
		m_pBGObj->Update();
	}

	if (m_bEnd)
	{
		return;
	}

	m_bEnd = m_pRankingInput->Update();

	if (m_bEnd)
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_TITLE);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CResult::Draw()
{
	//�J����
	m_pCamera->SetCamera();
	//�w�i
	m_pBGObj->Draw();

	m_pResultPolygon->Draw();

	m_pRanking->Draw();

	m_pRankingInput->Draw();

	CCounter::AllDraw();
}