//=============================================================================
//
// Bullet.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET_H_			//このマクロ定義がされなかったら
#define _BULLET_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "2dpolygon.h"

//*****************************************************************************
// 列挙型定義
//*****************************************************************************
enum BulletType
{
	BULLET_PLAYER = 0,//プレイヤーの弾
	BULLET_ENEMY,//エネミーの弾
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
// 構造体定義
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
// クラス定義
//*****************************************************************************
class CBulletBase : public C2DPolygon
{
private:
	// ポリゴンの幅
	static const float SIZE_BULLET;
public:

	CBulletBase();//コンストラクタ
	~CBulletBase() override;//デストラクタ

	virtual HRESULT Init() override;//初期化
	virtual void Uninit() override;//終了処理
	virtual void Update() override;//更新処理
	virtual void Draw() override;//描画処理
	virtual void SetType(BulletType Type) { m_Type = Type; }//弾のタイプセット
	virtual BulletType GetType() { return m_Type; }
	virtual bool IsUnused() override;//終了条件
	virtual void SetBullet(const Bullet bullet);
	virtual void BulletMove();//弾の動き
	virtual void BulletRot();//弾の向き
	float GetBulletMove() { return m_fMove; }
	void SetBulletMove(float fmove) { m_fMove = fmove; }

private:
	BulletType m_Type;//弾の種類
	float m_fMove;//移動量
};

#endif