//=============================================================================
//
// 3dobject.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _3DOBJECT_H_			//���̃}�N����`������Ȃ�������
#define _3DOBJECT_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class C3DObject : public CObject
{
public:
	static const int MODEL_MAX_TEXTURE = 20;
	static const int MODEL_PATTERN_MAX = 20;

	//���f���p�^�[���\����
	typedef struct
	{
		LPD3DXMESH pMeshModel;		//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
		DWORD nNumMatModel;				//�}�e���A�����̐�
		LPDIRECT3DTEXTURE9 pTexture[MODEL_MAX_TEXTURE];		// �e�N�X�`���ւ̃|�C���^
		bool bUse;
	}ModelPattern;

	//���f���\����
	typedef struct
	{
		D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
		D3DXVECTOR3 posChildren;			//�q�̈ʒu
		D3DXVECTOR3 pos;					//�ʒu�e
		D3DXVECTOR3 move;					//�ړ�
		D3DXVECTOR3 vtxMin, vtxMax;			//���f���̃T�C�Y
		D3DXVECTOR3 rot;					//����
		int nPattn;							//���f���̃p�^�[��
	}Model;

public:
	C3DObject();
	~C3DObject() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set3DObject(int nPattn, D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos() { return m_Model.pos; }
	void SetPos(D3DXVECTOR3 pos) { m_Model.pos = pos; }
	void AddPos(D3DXVECTOR3 add) { m_Model.pos += add; }
	void SetRot(D3DXVECTOR3 rot) { m_Model.rot = rot; }
	void AddRot(D3DXVECTOR3 add) { m_Model.rot += add; }
	void SetSize(float fSize) { m_fSize = fSize; }

	D3DXVECTOR3 GetSize();

	static void SetModel(ModelPattern *pModel);
	static void UninitAllModel();

private:
	static ModelPattern m_ModelPattern[MODEL_PATTERN_MAX];
	Model m_Model;
	float m_fSize;						//�T�C�Y
};

#endif