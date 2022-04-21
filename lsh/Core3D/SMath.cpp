#include "SMath.h"
//https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
namespace S
{
		const SVector2 SVector2::Zero = { 0.f, 0.f };
		const SVector2 SVector2::One = { 1.f, 1.f };
		const SVector2 SVector2::UnitX = { 1.f, 0.f };
		const SVector2 SVector2::UnitY = { 0.f, 1.f };

		const SVector3 SVector3::Zero = { 0.f, 0.f, 0.f };
		const SVector3 SVector3::One = { 1.f, 1.f, 1.f };
		const SVector3 SVector3::UnitX = { 1.f, 0.f, 0.f };
		const SVector3 SVector3::UnitY = { 0.f, 1.f, 0.f };
		const SVector3 SVector3::UnitZ = { 0.f, 0.f, 1.f };
		const SVector3 SVector3::Up = { 0.f, 1.f, 0.f };
		const SVector3 SVector3::Down = { 0.f, -1.f, 0.f };
		const SVector3 SVector3::Right = { 1.f, 0.f, 0.f };
		const SVector3 SVector3::Left = { -1.f, 0.f, 0.f };
		const SVector3 SVector3::Forward = { 0.f, 0.f, -1.f };
		const SVector3 SVector3::Backward = { 0.f, 0.f, 1.f };

		const SVector4 SVector4::Zero = { 0.f, 0.f, 0.f, 0.f };
		const SVector4 SVector4::One = { 1.f, 1.f, 1.f, 1.f };
		const SVector4 SVector4::UnitX = { 1.f, 0.f, 0.f, 0.f };
		const SVector4 SVector4::UnitY = { 0.f, 1.f, 0.f, 0.f };
		const SVector4 SVector4::UnitZ = { 0.f, 0.f, 1.f, 0.f };
		const SVector4 SVector4::UnitW = { 0.f, 0.f, 0.f, 1.f };

		const SMatrix SMatrix::Identity = { 1.f, 0.f, 0.f, 0.f,
										  0.f, 1.f, 0.f, 0.f,
										  0.f, 0.f, 1.f, 0.f,
										  0.f, 0.f, 0.f, 1.f };

		const SQuaternion SQuaternion::Identity = { 0.f, 0.f, 0.f, 1.f };
	

	SVector2 SRectangle::Location() const
	{
		return SVector2(float(x), float(y));
	}

	SVector2 SRectangle::Center() const
	{
		return SVector2(float(x) + float(width / 2.f), float(y) + float(height / 2.f));
	}

	bool SRectangle::Contains(const SVector2& point) const
	{
		return (float(x) <= point.x) && (point.x < float(x + width)) && (float(y) <= point.y) && (point.y < float(y + height));
	}

	void SRectangle::Inflate(long horizAmount, long vertAmount)
	{
		x -= horizAmount;
		y -= vertAmount;
		width += horizAmount;
		height += vertAmount;
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	SRectangle SRectangle::Intersect(const SRectangle& ra, const SRectangle& rb)
	{
		long righta = ra.x + ra.width;
		long rightb = rb.x + rb.width;

		long bottoma = ra.y + ra.height;
		long bottomb = rb.y + rb.height;

		long maxX = ra.x > rb.x ? ra.x : rb.x;
		long maxY = ra.y > rb.y ? ra.y : rb.y;

		long minRight = righta < rightb ? righta : rightb;
		long minBottom = bottoma < bottomb ? bottoma : bottomb;

		SRectangle result;

		if ((minRight > maxX) && (minBottom > maxY))
		{
			result.x = maxX;
			result.y = maxY;
			result.width = minRight - maxX;
			result.height = minBottom - maxY;
		}
		else
		{
			result.x = 0;
			result.y = 0;
			result.width = 0;
			result.height = 0;
		}

		return result;
	}

	RECT SRectangle::Intersect(const RECT& rcta, const RECT& rctb)
	{
		long maxX = rcta.left > rctb.left ? rcta.left : rctb.left;
		long maxY = rcta.top > rctb.top ? rcta.top : rctb.top;

		long minRight = rcta.right < rctb.right ? rcta.right : rctb.right;
		long minBottom = rcta.bottom < rctb.bottom ? rcta.bottom : rctb.bottom;

		RECT result;

		if ((minRight > maxX) && (minBottom > maxY))
		{
			result.left = maxX;
			result.top = maxY;
			result.right = minRight;
			result.bottom = minBottom;
		}
		else
		{
			result.left = 0;
			result.top = 0;
			result.right = 0;
			result.bottom = 0;
		}

		return result;
	}

	SRectangle SRectangle::Union(const SRectangle& ra, const SRectangle& rb)
	{
		long righta = ra.x + ra.width;
		long rightb = rb.x + rb.width;

		long bottoma = ra.y + ra.height;
		long bottomb = rb.y + rb.height;

		int minX = ra.x < rb.x ? ra.x : rb.x;
		int minY = ra.y < rb.y ? ra.y : rb.y;

		int maxRight = righta > rightb ? righta : rightb;
		int maxBottom = bottoma > bottomb ? bottoma : bottomb;

		SRectangle result;
		result.x = minX;
		result.y = minY;
		result.width = maxRight - minX;
		result.height = maxBottom - minY;
		return result;
	}

	RECT SRectangle::Union(const RECT& rcta, const RECT& rctb)
	{
		RECT result;
		result.left = rcta.left < rctb.left ? rcta.left : rctb.left;
		result.top = rcta.top < rctb.top ? rcta.top : rctb.top;
		result.right = rcta.right > rctb.right ? rcta.right : rctb.right;
		result.bottom = rcta.bottom > rctb.bottom ? rcta.bottom : rctb.bottom;
		return result;
	}


	/****************************************************************************
	*
	* SVector2
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool SVector2::operator == (const SVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		return XMVector2Equal(v1, v2);
	}

	bool SVector2::operator != (const SVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		return XMVector2NotEqual(v1, v2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SVector2& SVector2::operator+= (const SVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorAdd(v1, v2);
		XMStoreFloat2(this, X);
		return *this;
	}

	SVector2& SVector2::operator-= (const SVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		XMStoreFloat2(this, X);
		return *this;
	}

	SVector2& SVector2::operator*= (const SVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		XMStoreFloat2(this, X);
		return *this;
	}

	SVector2& SVector2::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVectorScale(v1, S);
		XMStoreFloat2(this, X);
		return *this;
	}

	SVector2& SVector2::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.0f);
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVectorScale(v1, 1.f / S);
		XMStoreFloat2(this, X);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	SVector2 operator+ (const SVector2& V1, const SVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorAdd(v1, v2);
		SVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	SVector2 operator- (const SVector2& V1, const SVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		SVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	SVector2 operator* (const SVector2& V1, const SVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		SVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	SVector2 operator* (const SVector2& V, float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		SVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	SVector2 operator/ (const SVector2& V1, const SVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorDivide(v1, v2);
		SVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	SVector2 operator* (float S, const SVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		SVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Vector operations
	//------------------------------------------------------------------------------

	bool SVector2::InBounds(const SVector2& Bounds) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&Bounds);
		return XMVector2InBounds(v1, v2);
	}

	float SVector2::Length() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2Length(v1);
		return XMVectorGetX(X);
	}

	float SVector2::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2LengthSq(v1);
		return XMVectorGetX(X);
	}

	float SVector2::Dot(const SVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVector2Dot(v1, v2);
		return XMVectorGetX(X);
	}

	void SVector2::Cross(const SVector2& V, SVector2& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR R = XMVector2Cross(v1, v2);
		XMStoreFloat2(&result, R);
	}

	SVector2 SVector2::Cross(const SVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR R = XMVector2Cross(v1, v2);

		SVector2 result;
		XMStoreFloat2(&result, R);
		return result;
	}

	void SVector2::Normalize()
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2Normalize(v1);
		XMStoreFloat2(this, X);
	}

	void SVector2::Normalize(SVector2& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2Normalize(v1);
		XMStoreFloat2(&result, X);
	}

	void SVector2::Clamp(const SVector2& vmin, const SVector2& vmax)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&vmin);
		XMVECTOR v3 = XMLoadFloat2(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat2(this, X);
	}

	void SVector2::Clamp(const SVector2& vmin, const SVector2& vmax, SVector2& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&vmin);
		XMVECTOR v3 = XMLoadFloat2(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat2(&result, X);
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	float SVector2::Distance(const SVector2& v1, const SVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector2Length(V);
		return XMVectorGetX(X);
	}

	float SVector2::DistanceSquared(const SVector2& v1, const SVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector2LengthSq(V);
		return XMVectorGetX(X);
	}

	void SVector2::Min(const SVector2& v1, const SVector2& v2, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Min(const SVector2& v1, const SVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Max(const SVector2& v1, const SVector2& v2, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Max(const SVector2& v1, const SVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Lerp(const SVector2& v1, const SVector2& v2, float t, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Lerp(const SVector2& v1, const SVector2& v2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::SmoothStep(const SVector2& v1, const SVector2& v2, float t, SVector2& result)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t*(3.f - 2.f*t);
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::SmoothStep(const SVector2& v1, const SVector2& v2, float t)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t*(3.f - 2.f*t);
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Barycentric(const SVector2& v1, const SVector2& v2, const SVector2& v3, float f, float g, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Barycentric(const SVector2& v1, const SVector2& v2, const SVector2& v3, float f, float g)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::CatmullRom(const SVector2& v1, const SVector2& v2, const SVector2& v3, const SVector2& v4, float t, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR x4 = XMLoadFloat2(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::CatmullRom(const SVector2& v1, const SVector2& v2, const SVector2& v3, const SVector2& v4, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR x4 = XMLoadFloat2(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Hermite(const SVector2& v1, const SVector2& t1, const SVector2& v2, const SVector2& t2, float t, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&t1);
		XMVECTOR x3 = XMLoadFloat2(&v2);
		XMVECTOR x4 = XMLoadFloat2(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Hermite(const SVector2& v1, const SVector2& t1, const SVector2& v2, const SVector2& t2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&t1);
		XMVECTOR x3 = XMLoadFloat2(&v2);
		XMVECTOR x4 = XMLoadFloat2(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Reflect(const SVector2& ivec, const SVector2& nvec, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Reflect(i, n);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Reflect(const SVector2& ivec, const SVector2& nvec)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Reflect(i, n);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Refract(const SVector2& ivec, const SVector2& nvec, float refractionIndex, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Refract(i, n, refractionIndex);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Refract(const SVector2& ivec, const SVector2& nvec, float refractionIndex)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Refract(i, n, refractionIndex);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Transform(const SVector2& v, const SQuaternion& quat, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4((DirectX::XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Transform(const SVector2& v, const SQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4((DirectX::XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void SVector2::Transform(const SVector2& v, const SMatrix& m, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)&m);
		XMVECTOR X = XMVector2TransformCoord(v1, M);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::Transform(const SVector2& v, const SMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)&m);
		XMVECTOR X = XMVector2TransformCoord(v1, M);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void SVector2::Transform(const SVector2* varray, size_t count, const SMatrix& m, SVector2* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)&m);
		XMVector2TransformCoordStream(resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M);
	}

	void SVector2::Transform(const SVector2& v, const SMatrix& m, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)&m);
		XMVECTOR X = XMVector2Transform(v1, M);
		XMStoreFloat4((DirectX::XMFLOAT4  *)&result, X);
	}

	_Use_decl_annotations_
		void SVector2::Transform(const SVector2* varray, size_t count, const SMatrix& m, SVector4* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4  *)&m);
		XMVector2TransformStream((DirectX::XMFLOAT4*)resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT2), count, M);
	}

	void SVector2::TransformNormal(const SVector2& v, const SMatrix& m, SVector2& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2TransformNormal(v1, M);
		XMStoreFloat2(&result, X);
	}

	SVector2 SVector2::TransformNormal(const SVector2& v, const SMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2TransformNormal(v1, M);

		SVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void SVector2::TransformNormal(const SVector2* varray, size_t count, const SMatrix& m, SVector2* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVector2TransformNormalStream(resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M);
	}


	/****************************************************************************
	*
	* SVector3
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------
	bool SVector3::operator == (const SVector3& V) const
	{
		DirectX::XMVECTOR v1 = XMLoadFloat3(this);
		DirectX::XMVECTOR v2 = XMLoadFloat3(&V);
		return DirectX::XMVector3Equal(v1, v2);
	}

	bool SVector3::operator != (const SVector3& V) const
	{
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		return XMVector3NotEqual(v1, v2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SVector3& SVector3::operator+= (const SVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorAdd(v1, v2);
		XMStoreFloat3(this, X);
		return *this;
	}

	SVector3& SVector3::operator-= (const SVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		XMStoreFloat3(this, X);
		return *this;
	}

	SVector3& SVector3::operator*= (const SVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		XMStoreFloat3(this, X);
		return *this;
	}

	SVector3& SVector3::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVectorScale(v1, S);
		XMStoreFloat3(this, X);
		return *this;
	}

	SVector3& SVector3::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.0f);
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVectorScale(v1, 1.f / S);
		XMStoreFloat3(this, X);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	SVector3 SVector3::operator- () const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVectorNegate(v1);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	SVector3 operator+ (const SVector3& V1, const SVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorAdd(v1, v2);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	SVector3 operator- (const SVector3& V1, const SVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	SVector3 operator* (const SVector3& V1, const SVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	SVector3 operator* (const SVector3& V, float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	SVector3 operator/ (const SVector3& V1, const SVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorDivide(v1, v2);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	SVector3 operator* (float S, const SVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		SVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Vector operations
	//------------------------------------------------------------------------------

	bool SVector3::InBounds(const SVector3& Bounds) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&Bounds);
		return XMVector3InBounds(v1, v2);
	}

	float SVector3::Length() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3Length(v1);
		return XMVectorGetX(X);
	}

	float SVector3::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3LengthSq(v1);
		return XMVectorGetX(X);
	}

	float SVector3::Dot(const SVector3& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVector3Dot(v1, v2);
		return XMVectorGetX(X);
	}

	void SVector3::Cross(const SVector3& V, SVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR R = XMVector3Cross(v1, v2);
		XMStoreFloat3(&result, R);
	}

	SVector3 SVector3::Cross(const SVector3& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR R = XMVector3Cross(v1, v2);

		SVector3 result;
		XMStoreFloat3(&result, R);
		return result;
	}

	void SVector3::Normalize()
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3Normalize(v1);
		XMStoreFloat3(this, X);
	}

	void SVector3::Normalize(SVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3Normalize(v1);
		XMStoreFloat3(&result, X);
	}

	void SVector3::Clamp(const SVector3& vmin, const SVector3& vmax)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&vmin);
		XMVECTOR v3 = XMLoadFloat3(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat3(this, X);
	}

	void SVector3::Clamp(const SVector3& vmin, const SVector3& vmax, SVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&vmin);
		XMVECTOR v3 = XMLoadFloat3(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat3(&result, X);
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------
	float SVector3::Distance(const SVector3& v1, const SVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector3Length(V);
		return XMVectorGetX(X);
	}

	float SVector3::DistanceSquared(const SVector3& v1, const SVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector3LengthSq(V);
		return XMVectorGetX(X);
	}

	void SVector3::Min(const SVector3& v1, const SVector3& v2, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Min(const SVector3& v1, const SVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Max(const SVector3& v1, const SVector3& v2, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Max(const SVector3& v1, const SVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Lerp(const SVector3& v1, const SVector3& v2, float t, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Lerp(const SVector3& v1, const SVector3& v2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::SmoothStep(const SVector3& v1, const SVector3& v2, float t, SVector3& result)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t*(3.f - 2.f*t);
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::SmoothStep(const SVector3& v1, const SVector3& v2, float t)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t*(3.f - 2.f*t);
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Barycentric(const SVector3& v1, const SVector3& v2, const SVector3& v3, float f, float g, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Barycentric(const SVector3& v1, const SVector3& v2, const SVector3& v3, float f, float g)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::CatmullRom(const SVector3& v1, const SVector3& v2, const SVector3& v3, const SVector3& v4, float t, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR x4 = XMLoadFloat3(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::CatmullRom(const SVector3& v1, const SVector3& v2, const SVector3& v3, const SVector3& v4, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR x4 = XMLoadFloat3(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Hermite(const SVector3& v1, const SVector3& t1, const SVector3& v2, const SVector3& t2, float t, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&t1);
		XMVECTOR x3 = XMLoadFloat3(&v2);
		XMVECTOR x4 = XMLoadFloat3(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Hermite(const SVector3& v1, const SVector3& t1, const SVector3& v2, const SVector3& t2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&t1);
		XMVECTOR x3 = XMLoadFloat3(&v2);
		XMVECTOR x4 = XMLoadFloat3(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Reflect(const SVector3& ivec, const SVector3& nvec, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Reflect(i, n);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Reflect(const SVector3& ivec, const SVector3& nvec)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Reflect(i, n);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Refract(const SVector3& ivec, const SVector3& nvec, float refractionIndex, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Refract(i, n, refractionIndex);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Refract(const SVector3& ivec, const SVector3& nvec, float refractionIndex)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Refract(i, n, refractionIndex);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Transform(const SVector3& v, const SQuaternion& quat, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4((XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Transform(const SVector3& v, const SQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4((XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void SVector3::Transform(const SVector3& v, const SMatrix& m, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformCoord(v1, M);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::Transform(const SVector3& v, const SMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformCoord(v1, M);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void SVector3::Transform(const SVector3* varray, size_t count, const SMatrix& m, SVector3* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector3TransformCoordStream(resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M);
	}

	void SVector3::Transform(const SVector3& v, const SMatrix& m, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3Transform(v1, M);
		XMStoreFloat4(&result, X);
	}

	_Use_decl_annotations_
		void SVector3::Transform(const SVector3* varray, size_t count, const SMatrix& m, SVector4* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector3TransformStream((XMFLOAT4*)resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT3), count, M);
	}

	void SVector3::TransformNormal(const SVector3& v, const SMatrix& m, SVector3& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformNormal(v1, M);
		XMStoreFloat3(&result, X);
	}

	SVector3 SVector3::TransformNormal(const SVector3& v, const SMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformNormal(v1, M);

		SVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void SVector3::TransformNormal(const SVector3* varray, size_t count, const SMatrix& m, SVector3* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector3TransformNormalStream(resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M);
	}


	///****************************************************************************
	//*
	//* SVector4
	//*
	//****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool SVector4::operator == (const SVector4& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		return XMVector4Equal(v1, v2);
	}

	bool SVector4::operator != (const SVector4& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		return XMVector4NotEqual(v1, v2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SVector4& SVector4::operator+= (const SVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorAdd(v1, v2);
		XMStoreFloat4(this, X);
		return *this;
	}

	SVector4& SVector4::operator-= (const SVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		XMStoreFloat4(this, X);
		return *this;
	}

	SVector4& SVector4::operator*= (const SVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		XMStoreFloat4(this, X);
		return *this;
	}

	SVector4& SVector4::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVectorScale(v1, S);
		XMStoreFloat4(this, X);
		return *this;
	}

	SVector4& SVector4::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.0f);
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVectorScale(v1, 1.f / S);
		XMStoreFloat4(this, X);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	SVector4 SVector4::operator- () const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVectorNegate(v1);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	SVector4 operator+ (const SVector4& V1, const SVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorAdd(v1, v2);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	SVector4 operator- (const SVector4& V1, const SVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	SVector4 operator* (const SVector4& V1, const SVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	SVector4 operator* (const SVector4& V, float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	SVector4 operator/ (const SVector4& V1, const SVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorDivide(v1, v2);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	SVector4 operator* (float S, const SVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		SVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Vector operations
	//------------------------------------------------------------------------------

	bool SVector4::InBounds(const SVector4& Bounds) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&Bounds);
		return XMVector4InBounds(v1, v2);
	}

	float SVector4::Length() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4Length(v1);
		return XMVectorGetX(X);
	}

	float SVector4::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4LengthSq(v1);
		return XMVectorGetX(X);
	}

	float SVector4::Dot(const SVector4& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVector4Dot(v1, v2);
		return XMVectorGetX(X);
	}

	void SVector4::Cross(const SVector4& v1, const SVector4& v2, SVector4& result) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(this);
		XMVECTOR x2 = XMLoadFloat4(&v1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR R = XMVector4Cross(x1, x2, x3);
		XMStoreFloat4(&result, R);
	}

	SVector4 SVector4::Cross(const SVector4& v1, const SVector4& v2) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(this);
		XMVECTOR x2 = XMLoadFloat4(&v1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR R = XMVector4Cross(x1, x2, x3);

		SVector4 result;
		XMStoreFloat4(&result, R);
		return result;
	}

	void SVector4::Normalize()
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4Normalize(v1);
		XMStoreFloat4(this, X);
	}

	void SVector4::Normalize(SVector4& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4Normalize(v1);
		XMStoreFloat4(&result, X);
	}

	void SVector4::Clamp(const SVector4& vmin, const SVector4& vmax)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&vmin);
		XMVECTOR v3 = XMLoadFloat4(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat4(this, X);
	}

	void SVector4::Clamp(const SVector4& vmin, const SVector4& vmax, SVector4& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&vmin);
		XMVECTOR v3 = XMLoadFloat4(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat4(&result, X);
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	float SVector4::Distance(const SVector4& v1, const SVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector4Length(V);
		return XMVectorGetX(X);
	}

	float SVector4::DistanceSquared(const SVector4& v1, const SVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector4LengthSq(V);
		return XMVectorGetX(X);
	}

	void SVector4::Min(const SVector4& v1, const SVector4& v2, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Min(const SVector4& v1, const SVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Max(const SVector4& v1, const SVector4& v2, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Max(const SVector4& v1, const SVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Lerp(const SVector4& v1, const SVector4& v2, float t, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Lerp(const SVector4& v1, const SVector4& v2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::SmoothStep(const SVector4& v1, const SVector4& v2, float t, SVector4& result)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t*(3.f - 2.f*t);
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::SmoothStep(const SVector4& v1, const SVector4& v2, float t)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t*(3.f - 2.f*t);
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Barycentric(const SVector4& v1, const SVector4& v2, const SVector4& v3, float f, float g, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Barycentric(const SVector4& v1, const SVector4& v2, const SVector4& v3, float f, float g)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::CatmullRom(const SVector4& v1, const SVector4& v2, const SVector4& v3, const SVector4& v4, float t, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR x4 = XMLoadFloat4(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::CatmullRom(const SVector4& v1, const SVector4& v2, const SVector4& v3, const SVector4& v4, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR x4 = XMLoadFloat4(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Hermite(const SVector4& v1, const SVector4& t1, const SVector4& v2, const SVector4& t2, float t, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&t1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR x4 = XMLoadFloat4(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Hermite(const SVector4& v1, const SVector4& t1, const SVector4& v2, const SVector4& t2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&t1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR x4 = XMLoadFloat4(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Reflect(const SVector4& ivec, const SVector4& nvec, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Reflect(i, n);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Reflect(const SVector4& ivec, const SVector4& nvec)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Reflect(i, n);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Refract(const SVector4& ivec, const SVector4& nvec, float refractionIndex, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Refract(i, n, refractionIndex);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Refract(const SVector4& ivec, const SVector4& nvec, float refractionIndex)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Refract(i, n, refractionIndex);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Transform(const SVector2& v, const SQuaternion& quat, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Transform(const SVector2& v, const SQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Transform(const SVector3& v, const SQuaternion& quat, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Transform(const SVector3& v, const SQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Transform(const SVector4& v, const SQuaternion& quat, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(v1, X, g_XMSelect1110); // result.w = v.w
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Transform(const SVector4& v, const SQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(v1, X, g_XMSelect1110); // result.w = v.w

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void SVector4::Transform(const SVector4& v, const SMatrix& m, SVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector4Transform(v1, M);
		XMStoreFloat4(&result, X);
	}

	SVector4 SVector4::Transform(const SVector4& v, const SMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector4Transform(v1, M);

		SVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void SVector4::Transform(const SVector4* varray, size_t count, const SMatrix& m, SVector4* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector4TransformStream(resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT4), count, M);
	}


	/****************************************************************************
	*
	* SMatrix
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool SMatrix::operator == (const SMatrix& M) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		return (XMVector4Equal(x1, y1)
			&& XMVector4Equal(x2, y2)
			&& XMVector4Equal(x3, y3)
			&& XMVector4Equal(x4, y4)) != 0;
	}

	bool SMatrix::operator != (const SMatrix& M) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		return (XMVector4NotEqual(x1, y1)
			|| XMVector4NotEqual(x2, y2)
			|| XMVector4NotEqual(x3, y3)
			|| XMVector4NotEqual(x4, y4)) != 0;
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SMatrix::SMatrix(const XMFLOAT3X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
	}

	SMatrix::SMatrix(const XMFLOAT4X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
	}

	SMatrix& SMatrix::operator= (const XMFLOAT3X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
		return *this;
	}

	SMatrix& SMatrix::operator= (const XMFLOAT4X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
		return *this;
	}

	SMatrix& SMatrix::operator+= (const SMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	SMatrix& SMatrix::operator-= (const SMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	SMatrix& SMatrix::operator*= (const SMatrix& M)
	{
		using namespace DirectX;
		XMMATRIX M1 = XMLoadFloat4x4(this);
		XMMATRIX M2 = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMMATRIX X = XMMatrixMultiply(M1, M2);
		XMStoreFloat4x4(this, X);
		return *this;
	}

	SMatrix& SMatrix::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	SMatrix& SMatrix::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.f);
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		float rs = 1.f / S;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	SMatrix& SMatrix::operator/= (const SMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	SMatrix SMatrix::operator- () const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		v1 = XMVectorNegate(v1);
		v2 = XMVectorNegate(v2);
		v3 = XMVectorNegate(v3);
		v4 = XMVectorNegate(v4);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	SMatrix operator+ (const SMatrix& M1, const SMatrix& M2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	SMatrix operator- (const SMatrix& M1, const SMatrix& M2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	SMatrix operator* (const SMatrix& M1, const SMatrix& M2)
	{
		using namespace DirectX;
		XMMATRIX m1 = XMLoadFloat4x4(&M1);
		XMMATRIX m2 = XMLoadFloat4x4((XMFLOAT4X4*)&M2);
		XMMATRIX X = XMMatrixMultiply(m1, m2);

		SMatrix R;
		XMStoreFloat4x4(&R, X);
		return R;
	}

	SMatrix operator* (const SMatrix& M, float S)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	SMatrix operator/ (const SMatrix& M, float S)
	{
		using namespace DirectX;
		assert(S != 0.f);

		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		float rs = 1.f / S;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	SMatrix operator/ (const SMatrix& M1, const SMatrix& M2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	SMatrix operator* (float S, const SMatrix& M)
	{
		using namespace DirectX;

		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		SMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	//------------------------------------------------------------------------------
	// SMatrix operations
	//------------------------------------------------------------------------------

	bool SMatrix::Decompose(SVector3& scale, SQuaternion& rotation, SVector3& translation)
	{
		using namespace DirectX;

		XMVECTOR s, r, t;

		if (!XMMatrixDecompose(&s, &r, &t, *(XMMATRIX*)this))
			return false;

		XMStoreFloat3(&scale, s);
		XMStoreFloat4(&rotation, r);
		XMStoreFloat3(&translation, t);

		return true;
	}

	SMatrix SMatrix::Transpose() const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixTranspose(M));
		return R;
	}

	void SMatrix::Transpose(SMatrix& result) const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		XMStoreFloat4x4(&result, XMMatrixTranspose(M));
	}

	SMatrix SMatrix::Invert() const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		SMatrix R;
		XMVECTOR det;
		XMStoreFloat4x4(&R, XMMatrixInverse(&det, M));
		return R;
	}

	void SMatrix::Invert(SMatrix& result) const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		XMVECTOR det;
		XMStoreFloat4x4(&result, XMMatrixInverse(&det, M));
	}

	float SMatrix::Determinant() const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		return XMVectorGetX(XMMatrixDeterminant(M));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	_Use_decl_annotations_
		SMatrix SMatrix::CreateBillboard(const SVector3& object, const SVector3& cameraPosition, const SVector3& cameraUp, const SVector3* cameraForward)
	{
		using namespace DirectX;
		XMVECTOR O = XMLoadFloat3(&object);
		XMVECTOR C = XMLoadFloat3(&cameraPosition);
		XMVECTOR Z = XMVectorSubtract(O, C);

		XMVECTOR N = XMVector3LengthSq(Z);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			if (cameraForward)
			{
				XMVECTOR F = XMLoadFloat3(cameraForward);
				Z = XMVectorNegate(F);
			}
			else
				Z = g_XMNegIdentityR2;
		}
		else
		{
			Z = XMVector3Normalize(Z);
		}

		XMVECTOR up = XMLoadFloat3(&cameraUp);
		XMVECTOR X = XMVector3Cross(up, Z);
		X = XMVector3Normalize(X);

		XMVECTOR Y = XMVector3Cross(Z, X);

		XMMATRIX M;
		M.r[0] = X;
		M.r[1] = Y;
		M.r[2] = Z;
		M.r[3] = XMVectorSetW(O, 1.f);

		SMatrix R;
		XMStoreFloat4x4(&R, M);
		return R;
	}

	_Use_decl_annotations_
		SMatrix SMatrix::CreateConstrainedBillboard(const SVector3& object, const SVector3& cameraPosition, const SVector3& rotateAxis,
			const SVector3* cameraForward, const SVector3* objectForward)
	{
		using namespace DirectX;

		static const XMVECTORF32 s_minAngle = { { { 0.99825467075f, 0.99825467075f, 0.99825467075f, 0.99825467075f } } }; // 1.0 - XMConvertToRadians( 0.1f );

		XMVECTOR O = XMLoadFloat3(&object);
		XMVECTOR C = XMLoadFloat3(&cameraPosition);
		XMVECTOR faceDir = XMVectorSubtract(O, C);

		XMVECTOR N = XMVector3LengthSq(faceDir);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			if (cameraForward)
			{
				XMVECTOR F = XMLoadFloat3(cameraForward);
				faceDir = XMVectorNegate(F);
			}
			else
				faceDir = g_XMNegIdentityR2;
		}
		else
		{
			faceDir = XMVector3Normalize(faceDir);
		}

		XMVECTOR Y = XMLoadFloat3(&rotateAxis);
		XMVECTOR X, Z;

		XMVECTOR dot = XMVectorAbs(XMVector3Dot(Y, faceDir));
		if (XMVector3Greater(dot, s_minAngle))
		{
			if (objectForward)
			{
				Z = XMLoadFloat3(objectForward);
				dot = XMVectorAbs(XMVector3Dot(Y, Z));
				if (XMVector3Greater(dot, s_minAngle))
				{
					dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
					Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
				}
			}
			else
			{
				dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
				Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
			}

			X = XMVector3Cross(Y, Z);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}
		else
		{
			X = XMVector3Cross(Y, faceDir);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}

		XMMATRIX M;
		M.r[0] = X;
		M.r[1] = Y;
		M.r[2] = Z;
		M.r[3] = XMVectorSetW(O, 1.f);

		SMatrix R;
		XMStoreFloat4x4(&R, M);
		return R;
	}

	SMatrix SMatrix::CreateTranslation(const SVector3& position)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixTranslation(position.x, position.y, position.z));
		return R;
	}

	SMatrix SMatrix::CreateTranslation(float x, float y, float z)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixTranslation(x, y, z));
		return R;
	}

	SMatrix SMatrix::CreateScale(const SVector3& scales)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixScaling(scales.x, scales.y, scales.z));
		return R;
	}

	SMatrix SMatrix::CreateScale(float xs, float ys, float zs)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixScaling(xs, ys, zs));
		return R;
	}

	SMatrix SMatrix::CreateScale(float scale)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixScaling(scale, scale, scale));
		return R;
	}

	SMatrix SMatrix::CreateRotationX(float radians)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationX(radians));
		return R;
	}

	SMatrix SMatrix::CreateRotationY(float radians)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationY(radians));
		return R;
	}

	SMatrix SMatrix::CreateRotationZ(float radians)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationZ(radians));
		return R;
	}

	SMatrix SMatrix::CreateFromAxisAngle(const SVector3& axis, float angle)
	{
		using namespace DirectX;
		SMatrix R;
		XMVECTOR a = XMLoadFloat3(&axis);
		XMStoreFloat4x4(&R, XMMatrixRotationAxis(a, angle));
		return R;
	}

	SMatrix SMatrix::CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane));
		return R;
	}

	SMatrix SMatrix::CreatePerspective(float width, float height, float nearPlane, float farPlane)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixPerspectiveLH(width, height, nearPlane, farPlane));
		return R;
	}

	SMatrix SMatrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixPerspectiveOffCenterLH(left, right, bottom, top, nearPlane, farPlane));
		return R;
	}

	SMatrix SMatrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixOrthographicLH(width, height, zNearPlane, zFarPlane));
		return R;
	}

	SMatrix SMatrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixOrthographicOffCenterLH(left, right, bottom, top, zNearPlane, zFarPlane));
		return R;
	}

	SMatrix SMatrix::CreateLookAt(const SVector3& eye, const SVector3& target, const SVector3& up)
	{
		using namespace DirectX;
		SMatrix R;
		XMVECTOR eyev = XMLoadFloat3(&eye);
		XMVECTOR targetv = XMLoadFloat3(&target);
		XMVECTOR upv = XMLoadFloat3(&up);
		XMStoreFloat4x4(&R, XMMatrixLookAtLH(eyev, targetv, upv));
		return R;
	}

	SMatrix SMatrix::CreateWorld(const SVector3& position, const SVector3& forward, const SVector3& up)
	{
		using namespace DirectX;
		XMVECTOR zaxis = XMVector3Normalize(XMVectorNegate(XMLoadFloat3(&forward)));
		XMVECTOR yaxis = XMLoadFloat3(&up);
		XMVECTOR xaxis = XMVector3Normalize(XMVector3Cross(yaxis, zaxis));
		yaxis = XMVector3Cross(zaxis, xaxis);

		SMatrix R;
		XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._11), xaxis);
		XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._21), yaxis);
		XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._31), zaxis);
		R._14 = R._24 = R._34 = 0.f;
		R._41 = position.x; R._42 = position.y; R._43 = position.z;
		R._44 = 1.f;
		return R;
	}

	SMatrix SMatrix::CreateFromQuaternion(const SQuaternion& rotation)
	{
		using namespace DirectX;
		SMatrix R;
		XMVECTOR quatv = XMLoadFloat4(&rotation);
		XMStoreFloat4x4(&R, XMMatrixRotationQuaternion(quatv));
		return R;
	}

	SMatrix SMatrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		using namespace DirectX;
		SMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
		return R;
	}

	SMatrix SMatrix::CreateShadow(const SVector3& lightDir, const SPlane& plane)
	{
		using namespace DirectX;
		SMatrix R;
		XMVECTOR light = XMLoadFloat3(&lightDir);
		XMVECTOR planev = XMLoadFloat4(&plane);
		XMStoreFloat4x4(&R, XMMatrixShadow(planev, light));
		return R;
	}

	SMatrix SMatrix::CreateReflection(const SPlane& plane)
	{
		using namespace DirectX;
		SMatrix R;
		XMVECTOR planev = XMLoadFloat4(&plane);
		XMStoreFloat4x4(&R, XMMatrixReflect(planev));
		return R;
	}

	void SMatrix::Lerp(const SMatrix& M1, const SMatrix& M2, float t, SMatrix& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorLerp(x1, y1, t);
		x2 = XMVectorLerp(x2, y2, t);
		x3 = XMVectorLerp(x3, y3, t);
		x4 = XMVectorLerp(x4, y4, t);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
	}

	SMatrix SMatrix::Lerp(const SMatrix& M1, const SMatrix& M2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorLerp(x1, y1, t);
		x2 = XMVectorLerp(x2, y2, t);
		x3 = XMVectorLerp(x3, y3, t);
		x4 = XMVectorLerp(x4, y4, t);

		SMatrix result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	void SMatrix::Transform(const SMatrix& M, const SQuaternion& rotation, SMatrix& result)
	{
		using namespace DirectX;
		XMVECTOR quatv = XMLoadFloat4(&rotation);

		XMMATRIX M0 = XMLoadFloat4x4(&M);
		XMMATRIX M1 = XMMatrixRotationQuaternion(quatv);

		XMStoreFloat4x4(&result, XMMatrixMultiply(M0, M1));
	}

	SMatrix SMatrix::Transform(const SMatrix& M, const SQuaternion& rotation)
	{
		using namespace DirectX;
		XMVECTOR quatv = XMLoadFloat4(&rotation);

		XMMATRIX M0 = XMLoadFloat4x4(&M);
		XMMATRIX M1 = XMMatrixRotationQuaternion(quatv);

		SMatrix result;
		XMStoreFloat4x4(&result, XMMatrixMultiply(M0, M1));
		return result;
	}


	/****************************************************************************
	*
	* SPlane
	*
	****************************************************************************/

	SPlane::SPlane(const SVector3& point1, const SVector3& point2, const SVector3& point3)
	{
		using namespace DirectX;
		XMVECTOR P0 = XMLoadFloat3(&point1);
		XMVECTOR P1 = XMLoadFloat3(&point2);
		XMVECTOR P2 = XMLoadFloat3(&point3);
		XMStoreFloat4(this, XMPlaneFromPoints(P0, P1, P2));
	}

	SPlane::SPlane(const SVector3& point, const SVector3& normal)
	{
		using namespace DirectX;
		XMVECTOR P = XMLoadFloat3(&point);
		XMVECTOR N = XMLoadFloat3(&normal);
		XMStoreFloat4(this, XMPlaneFromPointNormal(P, N));
	}

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool SPlane::operator == (const SPlane& p) const
	{
		using namespace DirectX;
		XMVECTOR p1 = XMLoadFloat4(this);
		XMVECTOR p2 = XMLoadFloat4(&p);
		return XMPlaneEqual(p1, p2);
	}

	bool SPlane::operator != (const SPlane& p) const
	{
		using namespace DirectX;
		XMVECTOR p1 = XMLoadFloat4(this);
		XMVECTOR p2 = XMLoadFloat4(&p);
		return XMPlaneNotEqual(p1, p2);
	}

	//------------------------------------------------------------------------------
	// SPlane operations
	//------------------------------------------------------------------------------

	void SPlane::Normalize()
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMStoreFloat4(this, XMPlaneNormalize(p));
	}

	void SPlane::Normalize(SPlane& result) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMPlaneNormalize(p));
	}

	float SPlane::Dot(const SVector4& v) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMVECTOR v0 = XMLoadFloat4(&v);
		return XMVectorGetX(XMPlaneDot(p, v0));
	}

	float SPlane::DotCoordinate(const SVector3& position) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMVECTOR v0 = XMLoadFloat3(&position);
		return XMVectorGetX(XMPlaneDotCoord(p, v0));
	}

	float SPlane::DotNormal(const SVector3& normal) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMVECTOR n0 = XMLoadFloat3(&normal);
		return XMVectorGetX(XMPlaneDotNormal(p, n0));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	void SPlane::Transform(const SPlane& plane, const SMatrix& M, SPlane& result)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMMATRIX m0 = XMLoadFloat4x4(&M);
		XMStoreFloat4(&result, XMPlaneTransform(p, m0));
	}

	SPlane SPlane::Transform(const SPlane& plane, const SMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMMATRIX m0 = XMLoadFloat4x4(&M);

		SPlane result;
		XMStoreFloat4(&result, XMPlaneTransform(p, m0));
		return result;
	}

	void SPlane::Transform(const SPlane& plane, const SQuaternion& rotation, SPlane& result)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMVECTOR q = XMLoadFloat4(&rotation);
		XMVECTOR X = XMVector3Rotate(p, q);
		X = XMVectorSelect(p, X, g_XMSelect1110); // result.d = plane.d
		XMStoreFloat4(&result, X);
	}

	SPlane SPlane::Transform(const SPlane& plane, const SQuaternion& rotation)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMVECTOR q = XMLoadFloat4(&rotation);
		XMVECTOR X = XMVector3Rotate(p, q);
		X = XMVectorSelect(p, X, g_XMSelect1110); // result.d = plane.d

		SPlane result;
		XMStoreFloat4(&result, X);
		return result;
	}


	/****************************************************************************
	*
	* SQuaternion
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool SQuaternion::operator == (const SQuaternion& q) const
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		return XMQuaternionEqual(q1, q2);
	}

	bool SQuaternion::operator != (const SQuaternion& q) const
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		return XMQuaternionNotEqual(q1, q2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SQuaternion& SQuaternion::operator+= (const SQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMVectorAdd(q1, q2));
		return *this;
	}

	SQuaternion& SQuaternion::operator-= (const SQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMVectorSubtract(q1, q2));
		return *this;
	}

	SQuaternion& SQuaternion::operator*= (const SQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
		return *this;
	}

	SQuaternion& SQuaternion::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(q, S));
		return *this;
	}

	SQuaternion& SQuaternion::operator/= (const SQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		q2 = XMQuaternionInverse(q2);
		XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	SQuaternion SQuaternion::operator- () const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);

		SQuaternion R;
		XMStoreFloat4(&R, XMVectorNegate(q));
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	SQuaternion operator+ (const SQuaternion& Q1, const SQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);

		SQuaternion R;
		XMStoreFloat4(&R, XMVectorAdd(q1, q2));
		return R;
	}

	SQuaternion operator- (const SQuaternion& Q1, const SQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);

		SQuaternion R;
		XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
		return R;
	}

	SQuaternion operator* (const SQuaternion& Q1, const SQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);

		SQuaternion R;
		XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
		return R;
	}

	SQuaternion operator* (const SQuaternion& Q, float S)
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(&Q);

		SQuaternion R;
		XMStoreFloat4(&R, XMVectorScale(q, S));
		return R;
	}

	SQuaternion operator/ (const SQuaternion& Q1, const SQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);
		q2 = XMQuaternionInverse(q2);

		SQuaternion R;
		XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
		return R;
	}

	SQuaternion operator* (float S, const SQuaternion& Q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q);

		SQuaternion R;
		XMStoreFloat4(&R, XMVectorScale(q1, S));
		return R;
	}

	//------------------------------------------------------------------------------
	// SQuaternion operations
	//------------------------------------------------------------------------------

	float SQuaternion::Length() const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		return XMVectorGetX(XMQuaternionLength(q));
	}

	float SQuaternion::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		return XMVectorGetX(XMQuaternionLengthSq(q));
	}

	void SQuaternion::Normalize()
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMQuaternionNormalize(q));
	}

	void SQuaternion::Normalize(SQuaternion& result) const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionNormalize(q));
	}

	void SQuaternion::Conjugate()
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMQuaternionConjugate(q));
	}

	void SQuaternion::Conjugate(SQuaternion& result) const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionConjugate(q));
	}

	void SQuaternion::Inverse(SQuaternion& result) const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionInverse(q));
	}

	float SQuaternion::Dot(const SQuaternion& q) const
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		return XMVectorGetX(XMQuaternionDot(q1, q2));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	SQuaternion SQuaternion::CreateFromAxisAngle(const SVector3& axis, float angle)
	{
		using namespace DirectX;
		XMVECTOR a = XMLoadFloat3(&axis);

		SQuaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationAxis(a, angle));
		return R;
	}

	SQuaternion SQuaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		using namespace DirectX;
		SQuaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
		return R;
	}

	SQuaternion SQuaternion::CreateFromRotationMatrix(const SMatrix& M)
	{
		using namespace DirectX;
		XMMATRIX M0 = XMLoadFloat4x4(&M);

		SQuaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationMatrix(M0));
		return R;
	}

	void SQuaternion::Lerp(const SQuaternion& q1, const SQuaternion& q2, float t, SQuaternion& result)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		XMVECTOR dot = XMVector4Dot(Q0, Q1);

		XMVECTOR R;
		if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
		{
			R = XMVectorLerp(Q0, Q1, t);
		}
		else
		{
			XMVECTOR tv = XMVectorReplicate(t);
			XMVECTOR t1v = XMVectorReplicate(1.f - t);
			XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
			XMVECTOR X1 = XMVectorMultiply(Q1, tv);
			R = XMVectorSubtract(X0, X1);
		}

		XMStoreFloat4(&result, XMQuaternionNormalize(R));
	}

	SQuaternion SQuaternion::Lerp(const SQuaternion& q1, const SQuaternion& q2, float t)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		XMVECTOR dot = XMVector4Dot(Q0, Q1);

		XMVECTOR R;
		if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
		{
			R = XMVectorLerp(Q0, Q1, t);
		}
		else
		{
			XMVECTOR tv = XMVectorReplicate(t);
			XMVECTOR t1v = XMVectorReplicate(1.f - t);
			XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
			XMVECTOR X1 = XMVectorMultiply(Q1, tv);
			R = XMVectorSubtract(X0, X1);
		}

		SQuaternion result;
		XMStoreFloat4(&result, XMQuaternionNormalize(R));
		return result;
	}

	void SQuaternion::Slerp(const SQuaternion& q1, const SQuaternion& q2, float t, SQuaternion& result)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);
		XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
	}

	SQuaternion SQuaternion::Slerp(const SQuaternion& q1, const SQuaternion& q2, float t)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		SQuaternion result;
		XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
		return result;
	}

	void SQuaternion::Concatenate(const SQuaternion& q1, const SQuaternion& q2, SQuaternion& result)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);
		XMStoreFloat4(&result, XMQuaternionMultiply(Q1, Q0));
	}

	SQuaternion SQuaternion::Concatenate(const SQuaternion& q1, const SQuaternion& q2)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		SQuaternion result;
		XMStoreFloat4(&result, XMQuaternionMultiply(Q1, Q0));
		return result;
	}


	/****************************************************************************
	*
	* SColor
	*
	****************************************************************************/

	SColor::SColor(const DirectX::PackedVector::XMCOLOR& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadColor(&Packed));
	}

	SColor::SColor(const DirectX::PackedVector::XMUBYTEN4& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadUByteN4(&Packed));
	}

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------
	bool SColor::operator == (const SColor& c) const
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorEqual(c1, c2);
	}

	bool SColor::operator != (const SColor& c) const
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorNotEqual(c1, c2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SColor& SColor::operator= (const DirectX::PackedVector::XMCOLOR& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadColor(&Packed));
		return *this;
	}

	SColor& SColor::operator= (const DirectX::PackedVector::XMUBYTEN4& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadUByteN4(&Packed));
		return *this;
	}

	SColor& SColor::operator+= (const SColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorAdd(c1, c2));
		return *this;
	}

	SColor& SColor::operator-= (const SColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorSubtract(c1, c2));
		return *this;
	}

	SColor& SColor::operator*= (const SColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorMultiply(c1, c2));
		return *this;
	}

	SColor& SColor::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(c, S));
		return *this;
	}

	SColor& SColor::operator/= (const SColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorDivide(c1, c2));
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	SColor SColor::operator- () const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		SColor R;
		XMStoreFloat4(&R, XMVectorNegate(c));
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	SColor operator+ (const SColor& C1, const SColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		SColor R;
		XMStoreFloat4(&R, XMVectorAdd(c1, c2));
		return R;
	}

	SColor operator- (const SColor& C1, const SColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		SColor R;
		XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
		return R;
	}

	SColor operator* (const SColor& C1, const SColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		SColor R;
		XMStoreFloat4(&R, XMVectorMultiply(c1, c2));
		return R;
	}

	SColor operator* (const SColor& C, float S)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(&C);
		SColor R;
		XMStoreFloat4(&R, XMVectorScale(c, S));
		return R;
	}

	SColor operator/ (const SColor& C1, const SColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		SColor R;
		XMStoreFloat4(&R, XMVectorDivide(c1, c2));
		return R;
	}

	SColor operator* (float S, const SColor& C)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C);
		SColor R;
		XMStoreFloat4(&R, XMVectorScale(c1, S));
		return R;
	}

	//------------------------------------------------------------------------------
	// SColor operations
	//------------------------------------------------------------------------------

	DirectX::PackedVector::XMCOLOR SColor::BGRA() const
	{
		using namespace DirectX;
		XMVECTOR clr = XMLoadFloat4(this);
		PackedVector::XMCOLOR Packed;
		PackedVector::XMStoreColor(&Packed, clr);
		return Packed;
	}

	DirectX::PackedVector::XMUBYTEN4 SColor::RGBA() const
	{
		using namespace DirectX;
		XMVECTOR clr = XMLoadFloat4(this);
		PackedVector::XMUBYTEN4 Packed;
		PackedVector::XMStoreUByteN4(&Packed, clr);
		return Packed;
	}

	SVector3 SColor::ToVector3() const
	{
		return SVector3(x, y, z);
	}

	SVector4 SColor::ToVector4() const
	{
		return SVector4(x, y, z, w);
	}

	void SColor::Negate()
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMColorNegative(c));
	}

	void SColor::Negate(SColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMColorNegative(c));
	}

	void SColor::Saturate()
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorSaturate(c));
	}

	void SColor::Saturate(SColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMVectorSaturate(c));
	}

	void SColor::Premultiply()
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMVECTOR a = XMVectorSplatW(c);
		a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
		XMStoreFloat4(this, XMVectorMultiply(c, a));
	}

	void SColor::Premultiply(SColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMVECTOR a = XMVectorSplatW(c);
		a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
		XMStoreFloat4(&result, XMVectorMultiply(c, a));
	}

	void SColor::AdjustSaturation(float sat)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMColorAdjustSaturation(c, sat));
	}

	void SColor::AdjustSaturation(float sat, SColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMColorAdjustSaturation(c, sat));
	}

	void SColor::AdjustContrast(float contrast)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMColorAdjustContrast(c, contrast));
	}

	void SColor::AdjustContrast(float contrast, SColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMColorAdjustContrast(c, contrast));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	void SColor::Modulate(const SColor& c1, const SColor& c2, SColor& result)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);
		XMStoreFloat4(&result, XMColorModulate(C0, C1));
	}

	SColor SColor::Modulate(const SColor& c1, const SColor& c2)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);

		SColor result;
		XMStoreFloat4(&result, XMColorModulate(C0, C1));
		return result;
	}

	void SColor::Lerp(const SColor& c1, const SColor& c2, float t, SColor& result)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);
		XMStoreFloat4(&result, XMVectorLerp(C0, C1, t));
	}

	SColor SColor::Lerp(const SColor& c1, const SColor& c2, float t)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);

		SColor result;
		XMStoreFloat4(&result, XMVectorLerp(C0, C1, t));
		return result;
	}


	/****************************************************************************
	*
	* SRay
	*
	****************************************************************************/

	//-----------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------
	bool SRay::operator == (const SRay& r) const
	{
		using namespace DirectX;
		XMVECTOR r1p = XMLoadFloat3(&position);
		XMVECTOR r2p = XMLoadFloat3(&r.position);
		XMVECTOR r1d = XMLoadFloat3(&direction);
		XMVECTOR r2d = XMLoadFloat3(&r.direction);
		return XMVector3Equal(r1p, r2p) && XMVector3Equal(r1d, r2d);
	}

	bool SRay::operator != (const SRay& r) const
	{
		using namespace DirectX;
		XMVECTOR r1p = XMLoadFloat3(&position);
		XMVECTOR r2p = XMLoadFloat3(&r.position);
		XMVECTOR r1d = XMLoadFloat3(&direction);
		XMVECTOR r2d = XMLoadFloat3(&r.direction);
		return XMVector3NotEqual(r1p, r2p) && XMVector3NotEqual(r1d, r2d);
	}

	//-----------------------------------------------------------------------------
	// SRay operators
	//------------------------------------------------------------------------------

	bool SRay::Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const
	{
		return sphere.Intersects(position, direction, Dist);
	}

	bool SRay::Intersects(const BoundingBox& box, _Out_ float& Dist) const
	{
		return box.Intersects(position, direction, Dist);
	}

	bool SRay::Intersects(const SVector3& tri0, const SVector3& tri1, const SVector3& tri2, _Out_ float& Dist) const
	{
		return DirectX::TriangleTests::Intersects(position, direction, tri0, tri1, tri2, Dist);
	}

	bool SRay::Intersects(const SPlane& plane, _Out_ float& Dist) const
	{
		using namespace DirectX;

		XMVECTOR p = XMLoadFloat4(&plane);
		XMVECTOR dir = XMLoadFloat3(&direction);

		XMVECTOR nd = XMPlaneDotNormal(p, dir);

		if (XMVector3LessOrEqual(XMVectorAbs(nd), g_RayEpsilon))
		{
			Dist = 0.f;
			return false;
		}
		else
		{
			// t = -(dot(n,origin) + D) / dot(n,dir)
			XMVECTOR pos = XMLoadFloat3(&position);
			XMVECTOR v = XMPlaneDotNormal(p, pos);
			v = XMVectorAdd(v, XMVectorSplatW(p));
			v = XMVectorDivide(v, nd);
			float dist = -XMVectorGetX(v);
			if (dist < 0)
			{
				Dist = 0.f;
				return false;
			}
			else
			{
				Dist = dist;
				return true;
			}
		}
	}


	/****************************************************************************
	*
	* SViewport
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool SViewport::operator == (const SViewport& vp) const
	{
		return (x == vp.x && y == vp.y
			&& width == vp.width && height == vp.height
			&& minDepth == vp.minDepth && maxDepth == vp.maxDepth);
	}

	bool SViewport::operator != (const SViewport& vp) const
	{
		return (x != vp.x || y != vp.y
			|| width != vp.width || height != vp.height
			|| minDepth != vp.minDepth || maxDepth != vp.maxDepth);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	SViewport& SViewport::operator= (const RECT& rct)
	{
		x = float(rct.left); y = float(rct.top);
		width = float(rct.right - rct.left);
		height = float(rct.bottom - rct.top);
		minDepth = 0.f; maxDepth = 1.f;
		return *this;
	}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
	SViewport& SViewport::operator= (const D3D11_VIEWPORT& vp)
	{
		x = vp.TopLeftX; y = vp.TopLeftY;
		width = vp.Width; height = vp.Height;
		minDepth = vp.MinDepth; maxDepth = vp.MaxDepth;
		return *this;
	}
#endif

#if defined(__d3d12_h__) || defined(__d3d12_x_h__)
	SViewport& SViewport::operator= (const D3D12_VIEWPORT& vp)
	{
		x = vp.TopLeftX; y = vp.TopLeftY;
		width = vp.Width; height = vp.Height;
		minDepth = vp.MinDepth; maxDepth = vp.MaxDepth;
		return *this;
	}
#endif

	//------------------------------------------------------------------------------
	// SViewport operations
	//------------------------------------------------------------------------------

	float SViewport::AspectRatio() const
	{
		if (width == 0.f || height == 0.f)
			return 0.f;

		return (width / height);
	}

	SVector3 SViewport::Project(const SVector3& p, const SMatrix& proj, const SMatrix& view, const SMatrix& world) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Project(v, x, y, width, height, minDepth, maxDepth, projection,
			(CXMMATRIX)view, (CXMMATRIX)world);
		SVector3 result;
		XMStoreFloat3(&result, v);
		return result;
	}

	void SViewport::Project(const SVector3& p, const SMatrix& proj, const SMatrix& view, const SMatrix& world, SVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Project(v, x, y, width, height, minDepth, maxDepth, projection, (CXMMATRIX)view, (CXMMATRIX)world);
		XMStoreFloat3(&result, v);
	}

	SVector3 SViewport::Unproject(const SVector3& p, const SMatrix& proj, const SMatrix& view, const SMatrix& world) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Unproject(v, x, y, width, height, minDepth, maxDepth, projection, (CXMMATRIX)view, (CXMMATRIX)world);
		SVector3 result;
		XMStoreFloat3(&result, v);
		return result;
	}

	void SViewport::Unproject(const SVector3& p, const SMatrix& proj, const SMatrix& view, const SMatrix& world, SVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Unproject(v, x, y, width, height, minDepth, maxDepth, projection, (CXMMATRIX)view, (CXMMATRIX)world);
		XMStoreFloat3(&result, v);
	}
}
