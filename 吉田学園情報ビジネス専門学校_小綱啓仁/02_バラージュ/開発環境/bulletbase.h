//=============================================================================
//
// Bullet.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET_H_			//���̃}�N����`������Ȃ�������
#define _BULLET_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "2dpolygon.h"

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************
enum BulletType
{
	BULLET_PLAYER = 0,//�v���C���[�̒e
	BULLET_ENEMY,//�G�l�~�[�̒e
	BULLET_TYPE_MAX
};

enum BulletMoveType
{
	BULLET_MOVE_00 = 0,
	BULLET_MOVE_01,
	BULLET_MOVE_02,
	BULLET_MOVE_03,
	BULLET_MOVE_04,
	BULLET_MOVE_SPECIAL_01,
	BULLET_MOVE_SPECIAL_02,
	BULLET_MOVE_MAX
};
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct Bullet
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Vector;
	D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	int nTextIndex;
	float fSize;
	float fMove;
	BulletType Type;
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBulletBase : public C2DPolygon
{
private:
	// �|���S���̕�
	static const float SIZE_BULLET;
public:

	CBulletBase();//�R���X�g���N�^
	~CBulletBase() override;//�f�X�g���N�^

	virtual HRESULT Init() override;//������
	virtual void Uninit() override;//�I������
	virtual void Update() override;//�X�V����
	virtual void Draw() override;//�`�揈��
	virtual void SetType(BulletType Type) { m_Type = Type; }//�e�̃^�C�v�Z�b�g
	virtual BulletType GetType() { return m_Type; }
	virtual bool IsUnused() override;//�I������
	virtual void SetBullet(const Bullet bullet);
	virtual void BulletMove();//�e�̓���
	virtual void BulletRot();//�e�̌���
	float GetBulletMove() { return m_fMove; }
	void SetBulletMove(float fmove) { m_fMove = fmove; }

private:
	BulletType m_Type;//�e�̎��
	float m_fMove;//�ړ���
};

#endif