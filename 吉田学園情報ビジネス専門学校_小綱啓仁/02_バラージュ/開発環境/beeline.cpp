//=============================================================================
//
// beeline.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "beeline.h"
#include "2dpolygon.h"
#include "texture.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBeeline::CBeeline()
{
	m_pBeeline = nullptr;
	m_nTextureIndex = 0;
	m_nBeelineIndex = 0;
	m_fSize = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBeeline::~CBeeline()
{

}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CBeeline::Init()
{
	m_pBeeline = new C2DPolygon;

	if (FAILED(m_pBeeline->Init()))
	{//�Q���|���S���̂h�m�h�s
		return -1;
	}

	m_nTextureIndex = 0;
	m_nBeelineIndex = 0;
	m_fSize = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBeeline::Uninit()
{

	if (m_pBeeline == nullptr)
	{
		return;
	}

	m_pBeeline->Uninit();

	delete m_pBeeline;
	m_pBeeline = nullptr;

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBeeline::Update()
{
	if (m_bFlashing)
	{
		m_pBeeline->SetFlashing(120);
	}
	m_pBeeline->Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBeeline::Draw()
{

	if (m_pBeeline == nullptr)
	{
		return;
	}

	m_pBeeline->Draw();

}

//*****************************************************************************
// �l�[���̈ꕶ���ݒ�
//*****************************************************************************
void CBeeline::SetBeeline(const int nNameIndex)
{
	if (m_pBeeline == nullptr)
	{//�|�C���^��NULL���ǂ���
		return;
	}

	
	//�w�x�̔ԍ��̌v�Z
	int nNumX = nNameIndex % MAX_NAME_X;
	int nNumY = nNameIndex / MAX_NAME_X;

	//�w�x�̃T�C�Y�̐ݒ�
	float fUVSizeX = 1.0f / MAX_NAME_X;
	float fUVSizeY = 1.0f / MAX_NAME_Y;

	//�t�u�̈ʒu�̐ݒ�
	D3DXVECTOR2 posUV;
	//�t�u�̃T�C�Y�̐ݒ�
	D3DXVECTOR2 sizeUV;
	if (nNameIndex >= MAX_NAME_INDEX || nNameIndex < 0)
	{
		posUV = D3DXVECTOR2(0.0f, 0.0f);
		sizeUV = D3DXVECTOR2(0.0f, 0.0f);
	}
	else
	{
		posUV = D3DXVECTOR2(fUVSizeX * nNumX + fUVSizeX * 0.5f, fUVSizeY * nNumY + fUVSizeY * 0.5f);
		sizeUV = D3DXVECTOR2(1.0f / MAX_NAME_X * 0.5f, 1.0f / MAX_NAME_Y * 0.5f);
	}

	//2D�|���S���̃Z�b�g
	m_pBeeline->SetPos(m_Pos);
	m_pBeeline->SetDiagonalLine(m_fSize, m_fSize);
	m_pBeeline->SetUV(posUV);
	m_pBeeline->SetUVSize(sizeUV);
	m_pBeeline->SetTextIndex(m_nTextureIndex);
	m_pBeeline->SetPolygon();
}

//*****************************************************************************
// �l�[���̈ꕶ���̕ύX
//*****************************************************************************
void CBeeline::ChangeBeeline(const int nNameIndex)
{
	if (m_pBeeline != nullptr)
	{//�|�C���^��NULL���ǂ���
		return;
	}

	//�w�x�̔ԍ��̌v�Z
	int nNumX = nNameIndex % MAX_NAME_X;
	int nNumY = nNameIndex / MAX_NAME_X;

	//�w�x�̃T�C�Y�̐ݒ�
	float fUVSizeX = 1.0f / MAX_NAME_X;
	float fUVSizeY = 1.0f / MAX_NAME_Y;

	//�t�u�̈ʒu�̐ݒ�
	D3DXVECTOR2 posUV;
	//�t�u�̃T�C�Y�̐ݒ�
	D3DXVECTOR2 sizeUV;
	if (nNameIndex >= MAX_NAME_INDEX || nNameIndex < 0)
	{
		posUV = D3DXVECTOR2(0.0f, 0.0f);
		sizeUV = D3DXVECTOR2(0.0f, 0.0f);
	}
	else
	{
		posUV = D3DXVECTOR2(fUVSizeX * nNumX + fUVSizeX * 0.5f, fUVSizeY * nNumY + fUVSizeY * 0.5f);
		sizeUV = D3DXVECTOR2(1.0f / MAX_NAME_X * 0.5f, 1.0f / MAX_NAME_Y * 0.5f);
	}

	//2D�|���S���̃Z�b�g
	m_pBeeline->SetUV(posUV);
	m_pBeeline->SetUVSize(sizeUV);
	m_pBeeline->SetPolygon();
}

//*****************************************************************************
// �ʒu�̈ړ�
//*****************************************************************************
void CBeeline::AddPos(D3DXVECTOR3 Add)
{
	if (m_pBeeline == nullptr)
	{//�|�C���^��NULL���ǂ���
		return;
	}

	m_Pos += Add;

	//2D�|���S���̃Z�b�g
	m_pBeeline->SetPos(m_Pos);
	m_pBeeline->SetDiagonalLine(m_fSize, m_fSize);
	m_pBeeline->SetPolygon();

}

void CBeeline::SetPos(D3DXVECTOR3 pos)
{
	if (m_pBeeline == nullptr)
	{//�|�C���^��NULL���ǂ���
		return;
	}

	m_Pos = pos;

	//2D�|���S���̃Z�b�g
	m_pBeeline->SetPos(m_Pos);
	m_pBeeline->SetDiagonalLine(m_fSize, m_fSize);
	m_pBeeline->SetPolygon();
}