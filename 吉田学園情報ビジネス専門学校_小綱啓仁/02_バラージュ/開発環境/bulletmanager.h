//=============================================================================
//
// bulletmanager .h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET_MANAGER_H_			//このマクロ定義がされなかったら
#define _BULLET_MANAGER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "bulletbase.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBulletBase;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBulletManager
{
private:
	// ポリゴンの幅
	static const float SIZE_BULLET;
	// バレットの最大数
	static const int BULLET_MAX = 1024;
	// 一回の射撃の最大角度
	static const float BULLET_ANGLE;


public:
	CBulletManager();
	~CBulletManager();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	

	static CBulletBase* CreateBullet(Bullet Bullet, BulletMoveType type);//弾のセット処理
	static void SetBullet(const Bullet bullet, const BulletMoveType type);//弾の発射
	static void ShotBullet(const Bullet bullet, const BulletMoveType type,int nbullet = 1, float fangle = 0.0f,float fradius = 0.0f);//弾の発射
	static int BreakBullet(BulletType type);
	static bool CollisionBullet(D3DXVECTOR3 pos, float radius, BulletType type);

private:
	static CBulletBase *m_pBullet[BULLET_MAX];//ポインタの配列
};

#endif