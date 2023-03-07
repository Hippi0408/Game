//=============================================================================
//
// anim.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ANIM_H_			//���̃}�N����`������Ȃ�������
#define _ANIM_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "2dpolygon.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CAnim : public C2DPolygon
{
private:
	// �|���S���̕�
	static const float SIZE_ANIM;
	//�A�j���[�V�����|���S���̓����ɏo������E��
	static const int ANIM_MAX = 128;

public:
	CAnim();//�R���X�g���N�^
	~CAnim();//�f�X�g���N�^

	static void ALLInit();//���ׂĂ̏�����
	static void ALLUninit();//���ׂĂ̏I������
	static void ALLUpdate();//���ׂĂ̍X�V����
	static void ALLDraw();//���ׂĂ̕`�揈��

	HRESULT Init() override;//������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��

	bool IsUnused() override;//�I����������

	static void CreateAnim(D3DXVECTOR3 pos,int nAnimCnt, int nAnimXNumber, int nAnimYNumber, int nTextIndex);//�A�j���[�V�����|���S���̍쐬
	void SetAnim(int nAnimCnt, int nAnimXNumber, int nAnimYNumber) //�Z�b�g�A�b�v
	{ m_nAnimCnt = nAnimCnt; m_nAnimXNumber = nAnimXNumber; m_nAnimYNumber = nAnimYNumber; }

private:
	static CAnim *m_pAnim[ANIM_MAX];//�N���X�̃|�C���^�z��
	D3DXVECTOR2 m_moveUV;//UV�̈ړ���
	int m_nAnimCnt;//�A�j���[�V�����̃J�E���^
	int m_nAnimNumX;//���̃A�j���[�V��������
	int m_nAnimNumY;//�c�̃A�j���[�V��������
	int m_nAnimTime;//���̃A�j���[�V�����܂ł̃t���[����
	int m_nAnimXNumber;//���݂̉�����
	int m_nAnimYNumber;//���݂̏c����
	

};

#endif