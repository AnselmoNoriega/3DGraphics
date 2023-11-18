#include "DepthBuffer.h"

DepthBuffer* DepthBuffer::Get()
{
	static DepthBuffer sInstanse;
	return &sInstanse;
}

void DepthBuffer::OnNewFrame()
{
	mEnabled = false;
	for (size_t i = 0; i < mWidth * mHeight; ++i)
	{
		mDepthBuffer[i] = 1.0f;
	}
}

void DepthBuffer::Initialize(int width, int height)
{
	if (width != mWidth && height != mHeight)
	{
		mDepthBuffer = std::make_unique<float[]>(width * height);
		mWidth = width;
		mHeight = height;
		OnNewFrame();
	}
}

void DepthBuffer::SetEnabled(bool enable)
{
	mEnabled = enable;
}

bool DepthBuffer::CheckDepthBuffer(int x, int y, float depth)
{
	if (!mEnabled)
	{
		return true;
	}

	if (x >= 0 && x < mWidth && y >= 0 && y <= mHeight)
	{
		const int index = x + (y * mWidth);
		if (depth <= mDepthBuffer[index])
		{
			mDepthBuffer[index] = depth;
			return true;
		}
	}

	return false;
}
