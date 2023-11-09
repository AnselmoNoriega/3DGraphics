#pragma once

#include "MathHelper.h"
#include <vector>

class MatrixStack
{
public:
	static MatrixStack* Get();

	void OnNewFrame();

	void PushTranslation(const Vec3& d);
	void PushRotationX(float rad);
	void PushRotationY(float rad);
	void PushRotationZ(float rad);
	void PushScaling(const Vec3& s);
	void PopMatrix();
	const Matrix4& GetTransform() const { return mCombinedTransform;  }

private:
	MatrixStack();

	std::vector<Matrix4> mMatrices;
	Matrix4 mCombinedTransform;

};

