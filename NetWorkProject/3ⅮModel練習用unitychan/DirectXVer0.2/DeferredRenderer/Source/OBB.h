//---------------------------------------------
// OBB vs OBB 衝突判定
// 2020-11-16 Monday
//---------------------------------------------
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

//struct OBB {
//	XMVECTOR m_Pos;              // 位置
//	XMVECTOR m_NormaDirect[3];   // 方向ベクトル
//	FLOAT m_fLength[3];          // 各軸方向の長さ
//};

class OBB
{
public:
	XMFLOAT3 maxpos;// = XMFLOAT3(0, 0, 0);
	XMFLOAT3 minpos;// = XMFLOAT3(0, 0, 0);
	XMMATRIX WorldMatrix;
//protected:
	XMVECTOR m_Pos;              // 位置
	XMVECTOR m_NormaDirect[3];   // 方向ベクトル
	FLOAT	 m_fLength[3];       // 各軸方向の長さ

public:
	
	// 指定軸番号の方向ベクトルを取得

	XMVECTOR GetDirect(int elem) {

		return WorldMatrix.r[elem];
	}
	
	// 指定軸方向の長さを取得
	FLOAT	GetLen_W(int elem) {
		FLOAT localmaxpos=0.0f;// = maxpos[elem];
		FLOAT localminpos=0.0f;// = minpos[elem];

		if (elem == 0) {
			localmaxpos = maxpos.x;
			localminpos = minpos.x;
		}
		if (elem == 1) {
			localmaxpos = maxpos.y;
			localminpos = minpos.y;
		}

		if (elem == 2) {
			localmaxpos = maxpos.z;
			localminpos = minpos.z;
		}

		return (float)fabs(localmaxpos - localminpos) * 0.5f;

	}    
	
	// 位置を取得
	XMVECTOR GetPos_W() {
		XMVECTOR localpos;

		localpos = WorldMatrix.r[3];
		
		return localpos;
	}; 
};

bool CollisionOBB(OBB &obb1, OBB &obb2);