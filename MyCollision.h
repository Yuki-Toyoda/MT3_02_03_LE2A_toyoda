#pragma once
#include "MyConst.h"
#include "MyStruct.h"
#include "MyMath.h"

/// <summary>
/// 当たり判定を行う関数を保持するクラス
/// </summary>
class MyCollision
{
public:

	/// <summary>
	/// 球の当たり判定をとる関数
	/// </summary>
	/// <param name="s1">球1</param>
	/// <param name="s2">球2</param>
	/// <returns>衝突しているか</returns>
	static bool IsCollisionSphere(const Sphere& s1, const Sphere& s2);

	/// <summary>
	/// 球と平面の当たり判定をとる関数
	/// </summary>
	/// <param name="s">球</param>
	/// <param name="p">平面</param>
	/// <returns>衝突しているか</returns>
	static bool IsCollisionPlane(const Sphere& s, const Plane& p);

	/// <summary>
	/// 直線と平面の当たり判定をとる関数
	/// </summary>
	/// <param name="l">直線</param>
	/// <param name="p">平面</param>
	/// <returns>衝突しているか</returns>
	static bool IsCollisionLine(const Line& l, const Plane& p);

	/// <summary>
	/// 半直線と平面の当たり判定をとる関数
	/// </summary>
	/// <param name="r">半直線</param>
	/// <param name="p">平面</param>
	/// <returns>衝突しているか</returns>
	static bool IsCollisionLine(const Ray& r, const Plane& p);

	/// <summary>
	/// 線分と平面の当たり判定をとる関数
	/// </summary>
	/// <param name="s">線分</param>
	/// <param name="p">平面</param>
	/// <returns>衝突しているか</returns>
	static bool IsCollisionLine(const Segment& s, const Plane& p);

};

