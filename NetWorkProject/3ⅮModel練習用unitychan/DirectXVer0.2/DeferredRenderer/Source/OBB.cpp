//---------------------------------------------
// OBB vs OBB 衝突判定プログラム
// 2020-11-16 Monday
//---------------------------------------------
#include "OBB.h"


// 分離軸に投影された軸成分から投影線分長を算出
FLOAT LenSegOnSeparateAxis(XMVECTOR Sep, XMVECTOR e1, 
	XMVECTOR e2,XMVECTOR e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	FLOAT r1 = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Sep, e1)));
	FLOAT r2 = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Sep, e2)));

	XMFLOAT3 fe3;
	XMStoreFloat3(&fe3, e3);
	
	FLOAT r3 = (fe3.x==0 && fe3.y==0 && fe3.z==0) ? (XMVectorGetX(XMVector3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}

// OBB v.s. OBB
bool CollisionOBB(OBB &obb1, OBB &obb2)
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	XMVECTOR NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen_W(0);
	XMVECTOR NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen_W(1);
	XMVECTOR NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen_W(2);
	XMVECTOR NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen_W(0);
	XMVECTOR NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen_W(1);
	XMVECTOR NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen_W(2);
	XMVECTOR Interval = obb1.GetPos_W() - obb2.GetPos_W();

	// 分離軸 : Ae1
	FLOAT rA = XMVectorGetX(XMVector3Length(Ae1));
	FLOAT rB = LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
	FLOAT L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, NAe1)));
	if (L > rA + rB)
		return false; // 衝突していない

	 // 分離軸 : Ae2
	rA = XMVectorGetX(XMVector3Length(Ae2));
	rB = LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, NAe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	//rA = D3DXVec3Length(&Ae3);
	//rB = LenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
	//L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	
	rA = XMVectorGetX(XMVector3Length(Ae3));
	rB = LenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, NAe3)));

	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	//rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	//rB = D3DXVec3Length(&Be1);
	//L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	
	rA = LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
	rB = XMVectorGetX(XMVector3Length(Be1));
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, NBe1)));

	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	/*rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	*/
	rA = LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
	rB = XMVectorGetX(XMVector3Length(Be2));
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, NBe2)));

	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	//rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	//rB = D3DXVec3Length(&Be3);
	//L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	rA = LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
	rB = XMVectorGetX(XMVector3Length(Be3));
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, NBe3)));
		
	if (L > rA + rB)
		return false;

	// 分離軸 : C11
	/*D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	XMVECTOR Cross;
	Cross=XMVector3Cross(NAe1, NBe1);

	XMFLOAT3 fzero=XMFLOAT3(0,0,0);
	XMVECTOR ezero;
	ezero=XMLoadFloat3(&fzero);

	rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be2, Be3, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));

	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	/*D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	
	Cross=XMVector3Cross(NAe1, NBe2);
	rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be3, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));

	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	//D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	//rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	//rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	//L = fabs(D3DXVec3Dot(&Interval, &Cross));
	
	Cross = XMVector3Cross(NAe1, NBe3);
	rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be2, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));

	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	/*D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	Cross = XMVector3Cross(NAe2, NBe1);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be2, Be3, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
	   	
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	/*D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	Cross = XMVector3Cross(NAe2, NBe2);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be3, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));

	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	/*D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	Cross = XMVector3Cross(NAe2, NBe3);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be2, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
	   	
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	/*D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	Cross = XMVector3Cross(NAe3, NBe1);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be2, Be3, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
	   	
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	/*D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	Cross = XMVector3Cross(NAe3, NBe2);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be3, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
	   	
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	/*D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	*/
	Cross = XMVector3Cross(NAe3, NBe3);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2, ezero);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be2, ezero);
	L = (FLOAT)fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
	   	
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	
	return true;
}

