//=============================================================================
//
// name.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "name.h"
#include "beeline.h"
#include "texture.h"

const float CName::NAME_SIZE_ADJUSTMENT = 0.7f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CName::CName()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		m_aNameIndex[nCnt] = MAX_NAME_INDEX;
		m_pName[nCnt] = nullptr;
	}
	m_fSize = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSetNameNum = 0;
	m_nTextureIndex = 0;
	m_bFlashing = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CName::~CName()
{

}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CName::Init()
{
	m_nTextureIndex = CTexture::LoadTexture("data/TEXTURE/�A���t�@�x�b�g.png");
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CName::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Uninit();

			delete m_pName[nCnt];
			m_pName[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CName::Update()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{
			continue;
		}

		if (m_bFlashing)
		{
			m_pName[nCnt]->SetFlashing();
		}

		m_pName[nCnt]->Update();
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CName::Draw()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{
			continue;
		}

		m_pName[nCnt]->Draw();
	}
}

//*****************************************************************************
// �l�[���̈ꕶ���ݒ�
//*****************************************************************************
void CName::SetName(const int nNameIndex)
{
	if (m_nSetNameNum >= MAX_NAME_LENGTH)
	{//�ݒ肳�ꂽ�������𒴂��ĂȂ���
		return;
	}

	if (m_pName[m_nSetNameNum] != nullptr)
	{//�|�C���^��NULL���ǂ���
		return;
	}

	m_pName[m_nSetNameNum] = new CBeeline;

	if (FAILED(m_pName[m_nSetNameNum]->Init()))
	{//�Q���|���S���̂h�m�h�s
		return;
	}

	//�ʒu�̐ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x + (m_fSize * NAME_SIZE_ADJUSTMENT) * (m_nSetNameNum), m_Pos.y, 0.0f);

	//�ꕶ���̃Z�b�g
	m_pName[m_nSetNameNum]->SetPos(pos);
	m_pName[m_nSetNameNum]->SetSize(m_fSize);
	m_pName[m_nSetNameNum]->SetTextureIndex(m_nTextureIndex);
	m_pName[m_nSetNameNum]->SetBeeline(nNameIndex);
	m_nSetNameNum++;
}

//*****************************************************************************
// �l�[���̈ꕶ���̔j��
//*****************************************************************************
void CName::BreakBeeline()
{
	m_nSetNameNum--;
	if (m_nSetNameNum < 0)
	{
		m_nSetNameNum = 0;
	}

	if (m_pName[m_nSetNameNum] == nullptr)
	{
		return;
	}

	m_pName[m_nSetNameNum]->Uninit();

	delete m_pName[m_nSetNameNum];
	m_pName[m_nSetNameNum] = nullptr;
}

//*****************************************************************************
// �l�[���̂܂Ƃ߂Đݒ�
//*****************************************************************************
void CName::SetAllName(const int *pNameIndex)
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH - 1; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{//�|�C���^��NULL���ǂ���

			return;
		}

		if (pNameIndex[nCnt] < 0 || MAX_NAME_INDEX <= pNameIndex[nCnt])
		{
			continue;
		}

		m_pName[nCnt] = new CBeeline;

		if (FAILED(m_pName[nCnt]->Init()))
		{//�Q���|���S���̂h�m�h�s
			return;
		}

		//�ʒu�̐ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x + (m_fSize * 0.7f) * (nCnt + 1), m_Pos.y, 0.0f);

		//�ꕶ���̃Z�b�g
		m_pName[nCnt]->SetPos(pos);
		m_pName[nCnt]->SetSize(m_fSize);
		m_pName[nCnt]->SetTextureIndex(m_nTextureIndex);
		m_pName[nCnt]->SetBeeline(pNameIndex[nCnt]);
	}
}

//*****************************************************************************
// �l�[���̂܂Ƃ߂ĕύX
//*****************************************************************************
void CName::ChangeName(const int *pNameIndex)
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{//�|�C���^��NULL���ǂ���
			return;
		}
		m_pName[nCnt]->ChangeBeeline(pNameIndex[nCnt]);
	}
}

//*****************************************************************************
// �ʒu�̈ړ�
//*****************************************************************************
void CName::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{//�|�C���^��NULL���ǂ���
			continue;
		}
		//�ʒu�̐ݒ�
		D3DXVECTOR3 Namepos = D3DXVECTOR3(m_Pos.x + (m_fSize * 0.7f) * (nCnt + 1), m_Pos.y, 0.0f);

		//2D�|���S���̃Z�b�g
		m_pName[nCnt]->SetPos(Namepos);
	}
}

//*****************************************************************************
// �ʒu�̈ړ�
//*****************************************************************************
void CName::AddPos(D3DXVECTOR3 Add)
{
	m_Pos += Add;

	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{//�|�C���^��NULL���ǂ���
			continue;
		}

		m_pName[nCnt]->AddPos(Add);
	}
}