//=============================================================================
//
// bulletmanager .h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET_MANAGER_H_			//���̃}�N����`������Ȃ�������
#define _BULLET_MANAGER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "bulletbase.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBulletBase;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBulletManager
{
private:
	// �|���S���̕�
	static const float SIZE_BULLET;
	// �o���b�g�̍ő吔
	static const int BULLET_MAX = 1024;
	// ���̎ˌ��̍ő�p�x
	static const float BULLET_ANGLE;


public:
	CBulletManager();
	~CBulletManager();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	

	static CBulletBase* CreateBullet(Bullet Bullet, BulletMoveType type);//�e�̃Z�b�g����
	static void SetBullet(const Bullet bullet, const BulletMoveType type);//�e�̔���
	static void ShotBullet(const Bullet bullet, const BulletMoveType type,int nbullet = 1, float fangle = 0.0f,float fradius = 0.0f);//�e�̔���
	static int BreakBullet(BulletType type);
	static bool CollisionBullet(D3DXVECTOR3 pos, float radius, BulletType type);

private:
	static CBulletBase *m_pBullet[BULLET_MAX];//�|�C���^�̔z��
};

#endif